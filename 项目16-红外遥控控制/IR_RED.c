/**
  ******************************************************************************
  * @file    IRremote.c
  * @brief   红外遥控接收模块源文件 (基于HS0038, INT1, Timer1 for AT89C52)
  *          实现NEC协议解码 (适用于 11.0592MHz 晶振)
  ******************************************************************************
  */

#include <reg52.h>  // <<<--- 必须包含这个！
#include "IRremote.h" // <<<--- 必须包含这个，且大小写匹配！

// --- 私有宏定义 (针对NEC协议和 11.0592MHz 晶振) ---
// 机器周期 = 12 / 晶振频率 = 12 / 11.0592MHz ≈ 1.088 us
// 定时器1 每个计数值 = 1.088 us (在 11.0592MHz 下)
// 为了简化，我们仍然以 1us 为单位计算 ticks，但增加容忍度

// NEC协议时间基准 (us) - 容忍一定误差
#define IR_TIME_TOL_PERCENT 40 // <<<--- 因为周期略大于1us，增大容忍度到40%

#define IR_HEAD_MARK_US     9000U
#define IR_HEAD_SPACE_US    4500U
#define IR_REPEAT_HEAD_SPACE_US 2250U
#define IR_BIT_MARK_US      560U
#define IR_ONE_SPACE_US     1690U // 560 + 1125
#define IR_ZERO_SPACE_US    560U  // 560 + 560

// 计算计数值 (仍按1us/tick估算，靠容差补偿)
#define CALC_TICKS(us) ((us) / 1) // 1MHz计数估算，1us=1tick
#define TOLERANCE(ticks) ((ticks) * IR_TIME_TOL_PERCENT / 100)

#define IR_HEAD_MARK_TICKS          CALC_TICKS(IR_HEAD_MARK_US)
#define IR_HEAD_SPACE_TICKS         CALC_TICKS(IR_HEAD_SPACE_US)
#define IR_REPEAT_HEAD_SPACE_TICKS  CALC_TICKS(IR_REPEAT_HEAD_SPACE_US)
#define IR_BIT_MARK_TICKS           CALC_TICKS(IR_BIT_MARK_US)
#define IR_ONE_SPACE_TICKS          CALC_TICKS(IR_ONE_SPACE_US)
#define IR_ZERO_SPACE_TICKS         CALC_TICKS(IR_ZERO_SPACE_US)

#define IR_HEAD_MARK_MAX_TICKS      (IR_HEAD_MARK_TICKS + TOLERANCE(IR_HEAD_MARK_TICKS))
#define IR_HEAD_MARK_MIN_TICKS      (IR_HEAD_MARK_TICKS - TOLERANCE(IR_HEAD_MARK_TICKS))
#define IR_HEAD_SPACE_MAX_TICKS     (IR_HEAD_SPACE_TICKS + TOLERANCE(IR_HEAD_SPACE_TICKS))
#define IR_HEAD_SPACE_MIN_TICKS     (IR_HEAD_SPACE_TICKS - TOLERANCE(IR_HEAD_SPACE_TICKS))
#define IR_REPEAT_HEAD_SPACE_MAX_TICKS (IR_REPEAT_HEAD_SPACE_TICKS + TOLERANCE(IR_REPEAT_HEAD_SPACE_TICKS))
#define IR_REPEAT_HEAD_SPACE_MIN_TICKS (IR_REPEAT_HEAD_SPACE_TICKS - TOLERANCE(IR_REPEAT_HEAD_SPACE_TICKS))
#define IR_BIT_MARK_MAX_TICKS       (IR_BIT_MARK_TICKS + TOLERANCE(IR_BIT_MARK_TICKS))
#define IR_BIT_MARK_MIN_TICKS       (IR_BIT_MARK_TICKS - TOLERANCE(IR_BIT_MARK_TICKS))
#define IR_ONE_SPACE_MAX_TICKS      (IR_ONE_SPACE_TICKS + TOLERANCE(IR_ONE_SPACE_TICKS))
#define IR_ONE_SPACE_MIN_TICKS      (IR_ONE_SPACE_TICKS - TOLERANCE(IR_ONE_SPACE_TICKS))
#define IR_ZERO_SPACE_MAX_TICKS     (IR_ZERO_SPACE_TICKS + TOLERANCE(IR_ZERO_SPACE_TICKS))
#define IR_ZERO_SPACE_MIN_TICKS     (IR_ZERO_SPACE_TICKS - TOLERANCE(IR_ZERO_SPACE_TICKS))

#define IR_END_TIMEOUT_TICKS        CALC_TICKS(20000U) // 20ms超时，判断结束

// 状态机定义
typedef enum {
    IR_STATE_IDLE = 0,           // 空闲状态，等待引导码下降沿 (9ms Mark结束)
    IR_STATE_WAIT_START_SPACE,   // 等待引导码或重复码的 Space 结束
    IR_STATE_RECEIVING_BITS,     // 接收数据位状态
    IR_STATE_RECEIVED_COMPLETE   // 数据接收完成状态
} IR_State_t;

// --- 私有变量 ---
static volatile IR_State_t ir_state = IR_STATE_IDLE; // 当前解码状态
static volatile unsigned char ir_data_index = 0;     // 正在接收的数据位索引 (0-31)
static volatile unsigned long ir_raw_data = 0;       // 存储接收到的32位原始数据 (地址+~地址+命令+~命令)
static volatile unsigned char ir_addr = 0;           // 解析出的地址码
static volatile unsigned char ir_cmd = 0;            // 解析出的命令码
static volatile unsigned char ir_last_cmd = 0;       // 上一次解析出的有效命令码 (用于重复码)
static volatile bit ir_data_valid = 0;               // 数据有效标志
static volatile bit ir_repeat_flag = 0;              // 重复码标志 (本次接收是否为重复码)
static volatile unsigned int ir_tick_count = 0;      // 定时器计数值缓存
// static volatile bit ir_timer_overflow = 0;        // <<<--- 移除这个全局 bit 变量

// --- 新增：用于传递定时器溢出状态的全局静态变量 (避免 bit 指针) ---
static volatile bit g_timer_overflow_flag = 0;

// --- 定时器1相关私有函数 ---

/**
 * @brief  启动定时器1计数 (模式1)
 */
static void IR_Timer_Start(void) {
    TH1 = 0;
    TL1 = 0;
    TF1 = 0; // 清除溢出标志
    TR1 = 1; // 启动定时器1
}

/**
 * @brief  停止定时器1计数并读取当前计数值
 * @return unsigned int 当前计数值 (TH1:TL1)
 *         溢出状态通过全局静态变量 g_timer_overflow_flag 返回
 */
static unsigned int IR_Timer_Stop_Read(void) {
    TR1 = 0; // 停止定时器1
    g_timer_overflow_flag = TF1; // <<<--- 读取溢出标志到全局静态变量
    TF1 = 0; // 清除溢出标志 (重要!)
    return (TH1 << 8) | TL1; // 返回当前计数值
}


// --- 外部中断1 (INT1) 服务程序 ---
/**
 * @brief  外部中断1服务程序 (INT1 - P3.3 下降沿触发)
 *         用于捕获红外信号的下降沿，启动/停止定时器进行脉宽测量
 */
void ExInt1_ISR(void) interrupt 2 {
    // static unsigned int last_tick_count = 0; // 如果需要可以保留
    // static bit last_timer_overflow = 0;      // 如果需要可以保留

    // 读取并停止定时器，获取上次下降沿以来的时间
    ir_tick_count = IR_Timer_Stop_Read(); // <<<--- 调用修改后的函数
    // ir_timer_overflow = g_timer_overflow_flag; // <<<--- 从全局静态变量获取溢出标志
    IR_Timer_Start(); // 立即重启定时器，为下次测量做准备

    // 状态机处理
    switch (ir_state) {
        case IR_STATE_IDLE:
            // 等待 9ms Mark 结束的下降沿
            TR1 = 0; // 确保定时器停止
            TH1 = 0;
            TL1 = 0;
            TF1 = 0;
            IR_Timer_Start(); // 启动定时器测量接下来的 Space
            ir_state = IR_STATE_WAIT_START_SPACE; // 转移到等待Space状态
            break;

        case IR_STATE_WAIT_START_SPACE:
            // 测量的是 9ms Mark 的高电平时间
            if (!g_timer_overflow_flag && // <<<--- 使用全局静态变量
                (ir_tick_count >= IR_HEAD_MARK_MIN_TICKS) &&
                (ir_tick_count <= IR_HEAD_MARK_MAX_TICKS)) {
                // 检测到 9ms Mark，现在等待 Space 结束 (4.5ms or 2.25ms)
                // 定时器已在 IR_Timer_Start 重启，现在是测量 Space 时间
                // 状态不变，继续等待下一个下降沿来判断是首次还是重复
            } else {
                // 不符合 9ms Mark，噪声或错误，回到空闲
                ir_state = IR_STATE_IDLE;
                TR1 = 0;
            }
            break;

        case IR_STATE_RECEIVING_BITS:
            // 测量的是 Bit Time (Mark + Space)
            if (g_timer_overflow_flag) { // <<<--- 使用全局静态变量
                 // 时间过长，可能是结束信号或错误
                 // 检查是否接收完32位
                 if (ir_data_index == 32) {
                      // 可能是结束，进行校验
                       // 提取地址和命令
                        ir_addr = (ir_raw_data >> 24) & 0xFF;
                        // <<<--- 在 if 块内声明局部变量 ---
                        unsigned char addr_inv = (ir_raw_data >> 16) & 0xFF;
                        ir_cmd = (ir_raw_data >> 8) & 0xFF;
                        unsigned char cmd_inv = ir_raw_data & 0xFF;
                        // <<<--- ---


                        if (((ir_addr ^ addr_inv) == 0xFF) && ((ir_cmd ^ cmd_inv) == 0xFF)) {
                            // 校验成功
                            ir_data_valid = 1;
                            ir_repeat_flag = 0;
                            ir_last_cmd = ir_cmd; // 更新最后命令
                            ir_state = IR_STATE_RECEIVED_COMPLETE;
                        } else {
                            // 地址/命令校验失败
                            ir_state = IR_STATE_IDLE;
                        }
                 } else {
                     // 未接收完就超时，错误
                     ir_state = IR_STATE_IDLE;
                 }
                 TR1 = 0; // 停止定时器
                 break;
            }

            if ((ir_tick_count >= IR_ZERO_SPACE_MIN_TICKS) && (ir_tick_count <= IR_ZERO_SPACE_MAX_TICKS)) {
                // 逻辑 '0'
                ir_data_index++;
            } else if ((ir_tick_count >= IR_ONE_SPACE_MIN_TICKS) && (ir_tick_count <= IR_ONE_SPACE_MAX_TICKS)) {
                // 逻辑 '1'
                ir_raw_data |= ((unsigned long)1 << (31 - ir_data_index)); // MSB First
                ir_data_index++;
            } else {
                // 时间不符合 0 或 1 的特征，解码错误
                ir_state = IR_STATE_IDLE;
                TR1 = 0;
                break;
            }

            if (ir_data_index >= 32) {
                // 32 bits received, validation happens on timeout or next edge
                 // Keep timer running.
            }
            break;

        case IR_STATE_RECEIVED_COMPLETE:
            // 已经接收完成，这个下降沿可能是重复码的开始 (2.25ms Space 结束)
            // 或者是新一帧的开始 (4.5ms Space 结束)
            // 或者是结束后的噪声
            if (!g_timer_overflow_flag && // <<<--- 使用全局静态变量
                (ir_tick_count >= IR_REPEAT_HEAD_SPACE_MIN_TICKS) &&
                (ir_tick_count <= IR_REPEAT_HEAD_SPACE_MAX_TICKS)) {
                // 检测到重复码的 Space 时间 (2.25ms)
                ir_repeat_flag = 1;
                ir_data_valid = 1; // 使用上次的命令
                // 保持在 COMPLETE 状态
            } else if (!g_timer_overflow_flag && // <<<--- 使用全局静态变量
                       (ir_tick_count >= IR_HEAD_SPACE_MIN_TICKS) &&
                       (ir_tick_count <= IR_HEAD_SPACE_MAX_TICKS)) {
                 // 检测到新帧引导码的 Space 时间 (4.5ms)
                 // 准备接收新数据
                 ir_state = IR_STATE_RECEIVING_BITS;
                 ir_data_index = 0;
                 ir_raw_data = 0;
                 ir_data_valid = 0;
                 ir_repeat_flag = 0;
                 // Timer is already restarted
            } else {
                 // 时间不符合，可能是结束或噪声，回到空闲
                  ir_state = IR_STATE_IDLE;
                  TR1 = 0;
            }
             break;


        default:
            // 不应到达这里，重置状态
            ir_state = IR_STATE_IDLE;
            TR1 = 0;
            break;
    }

    // last_tick_count = ir_tick_count; // 如果需要可以保留
    // last_timer_overflow = g_timer_overflow_flag; // 如果需要可以保留
}


// --- 公共函数实现 ---

/**
 * @brief  红外遥控初始化函数
 *         配置外部中断1 (INT1/P3.3) 和 定时器1 (Timer1 Mode 1)
 */
void IR_Init(void) {
    // --- 定时器1 初始化 (16位定时器模式 Mode 1) ---
    TMOD &= 0x0F;  // 清除T1的模式位
    TMOD |= 0x10;  // 设置T1为模式1 (16位定时器)
    TH1 = 0x00;
    TL1 = 0x00;
    TF1 = 0;       // 清除TF1
    TR1 = 0;       // 停止T1
    ET1 = 0;       // 禁用T1中断 (本例使用查询方式)

    // --- 外部中断1 (INT1 - P3.3) 初始化 ---
    IT1 = 1;  // 设置INT1为下降沿触发
    // IE1 = 0;  // IE1是中断标志位，由硬件管理，软件通常不需要清零
    PX1 = 1;  // 设置INT1为高优先级 (推荐)
    EX1 = 1;  // 使能INT1中断

    EA = 1;   // 使能全局中断

    // 初始化状态机变量
    ir_state = IR_STATE_IDLE;
    ir_data_index = 0;
    ir_raw_data = 0;
    ir_addr = 0;
    ir_cmd = 0;
    ir_last_cmd = 0;
    ir_data_valid = 0;
    ir_repeat_flag = 0;
    ir_tick_count = 0;
    // ir_timer_overflow = 0; // <<<--- 移除了这个变量的初始化
    g_timer_overflow_flag = 0; // <<<--- 初始化新增的全局静态变量
}


/**
 * @brief  获取红外遥控按键键值
 * @retval unsigned char 键值 (0x00-0xFF), 无按键时返回 0x00
 *         返回值为解码得到的命令码(Command Code)。
 *         如果是重复码，返回上一次的命令码。
 */
unsigned char IR_GetKey(void) {
    unsigned char key = 0x00;

    // 检查是否有有效的数据
    if (ir_data_valid) {
        if (ir_repeat_flag) {
            // 如果是重复码，则返回上次的有效命令
            key = ir_last_cmd;
        } else {
            // 如果是新数据，则返回当前命令
            key = ir_cmd;
        }
        // 注意：当前实现下，一旦数据有效，GetKey会持续返回该值，
        // 直到状态机因超时或新帧而重置 ir_data_valid。
        // 如果需要“按下一次只返回一次”的效果，
        // 可以在这里读取后清零 ir_data_valid，
        // 或者由主循环在处理完按键后等待 key 变回 0。
        // 例如：
        // ir_data_valid = 0; // 读取一次后清掉 (单次触发)
        // 但这样会影响重复码的连续获取。
        // 更好的方式是在状态机中处理超时后自动清掉 ir_data_valid。
    }

    return key;
}