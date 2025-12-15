#include <REGX52.H>
#include <SWITCH0000.H>
#include <DELAY.H>
#include <TIMER0.H>
#include <888LED.H>
#include <RGB_LED.H>

unsigned char Time=0;//时间计数变量
unsigned char Code=0;//红绿灯显示状态变量
unsigned char Pulse=0;//脉冲信号变量
unsigned char Emergency=0;//紧急状态标志位

unsigned char keynum=0;//按键变量


void main() {
    //定时器初始化
    Timer0Init();
    //初始化外部中断0和1
    Int0_Init();
    Int1_Init();

    while (1)
    {
        //显示紧急状态
        if(Emergency){
            Set_888led(1,11); // 第一个数码管显示"-"
            Set_888led(2,11); // 第二个数码管显示"-"
        }
        else{
            Set_888led(1,Time / 10); // 第一个数码管显示十位
            Set_888led(2,Time % 10); // 第二个数码管显示个位
        }

        //红绿灯状态控制
        Red_Green_Light_State_Machine(Time);
        //红绿灯状态刷新LED
        Red_Green_Light_State(Code);

        //按键扫描
        keynum = switch0000();
        //按键按下时状态置为8，紧急状态置为1，再次按下恢复正常状态，紧急状态置0
        if(keynum){
            if(Code == 8){
                Emergency = 0;
                Red_Green_Light_State_Machine(Time);
            }else{
                Emergency = 1;
                Code = 8;
            }
        }

    }
}


//外部中断0函数，控制状态为6,紧急状态置为1，再次按下恢复正常状态，紧急状态置0
void Int0_Routine() interrupt 0
{
    if(Code == 6){
        Emergency = 0;
        Red_Green_Light_State_Machine(Time);
    }else{
        Emergency = 1;
        Code = 6;
    }
}

//外部中断1函数，控制状态为7,紧急状态置为1，再次按下恢复正常状态，紧急状态置0
void Int1_Routine() interrupt 2
{
    if(Code == 7){
        Emergency = 0;
        Red_Green_Light_State_Machine(Time);
    }else{
        Emergency = 1;
        Code = 7;
    }
}


void Timer0_Routine() interrupt 1
{
    //一个定时器复用4次
	static  unsigned int T0Count,T0Count1,T0Count2,T0Count3;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
    T0Count1++;
    T0Count2++;
    T0Count3++;
	if(T0Count>=20)  //20毫秒
	{
		T0Count=0;
		Scan_key();
	}
    if(T0Count1>=2)  //2毫秒显示一个数字，在下一个两毫秒显示下一个数字
    {
        T0Count1=0;
        Scan_888led();
    }
    if(T0Count2>=780)//修正后的1秒计时，时间自加
    {
        T0Count2=0;
        if(!Emergency){//非紧急状态下时间自加
            Time++;
        }
        if(Time>=30){//达到30秒归零
            Time=0;
        }
    }
    if(T0Count3>=290)//修正后的300ms，脉冲信号翻转一次
    {
        T0Count3=0;
        Pulse = ~Pulse;
    }
}


