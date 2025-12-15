#include <REGX52.H>

//引用主函数变量
extern unsigned char Time;//时间计数变量
extern unsigned char Code;//红绿灯显示状态变量
extern unsigned char Pulse;//脉冲信号变量
extern unsigned char Emergency;//紧急状态标志位

sbit South_Green_Led=P1^0;//南北绿灯
sbit South_Yellow_Led=P1^1;//南北黄灯
sbit South_Red_Led=P1^2;//南北红灯
sbit East_Green_Led=P1^3;//东西绿灯
sbit East_Yellow_Led=P1^4;//东西黄灯
sbit East_Red_Led=P1^5;//东西红灯

//红绿灯的六种状态框架
//0-5秒南北绿灯亮,其他不亮
//5-10秒南北黄灯闪烁,其他不亮
//10-15秒南北红灯亮,其他不亮
//15-20秒东西绿灯亮,其他不亮
//20-25秒东西黄灯闪烁,其他不亮
//25-30秒东西红灯亮,其他不亮
//闪烁由周期脉冲变量Pulse控制
//状态为6时，南北红灯亮，东西红灯亮，其他不亮
//状态为7时，南北绿灯亮，东西绿灯亮，其他不亮
//状态为8时，南北黄灯亮，东西黄灯亮，其他不亮
//红绿灯状态刷新函数
void Red_Green_Light_State(unsigned char state){
    switch(state){
        case 0:
            South_Green_Led=0;
            South_Yellow_Led=1;
            South_Red_Led=1;
            East_Green_Led=1;
            East_Yellow_Led=1;
            East_Red_Led=1;
            break;
        case 1:
            South_Green_Led=1;
            South_Yellow_Led=Pulse;
            South_Red_Led=1;
            East_Green_Led=1;
            East_Yellow_Led=1;
            East_Red_Led=1;
            break;
        case 2:
            South_Green_Led=1;
            South_Yellow_Led=1;
            South_Red_Led=0;
            East_Green_Led=1;
            East_Yellow_Led=1;
            East_Red_Led=1;
            break;
        case 3:
            South_Green_Led=1;
            South_Yellow_Led=1;
            South_Red_Led=1;
            East_Green_Led=0;
            East_Yellow_Led=1;
            East_Red_Led=1;
            break;
        case 4:
            South_Green_Led=1;
            South_Yellow_Led=1;
            South_Red_Led=1;
            East_Green_Led=1;
            East_Yellow_Led=Pulse;
            East_Red_Led=1;
            break;
        case 5:
            South_Green_Led=1;
            South_Yellow_Led=1;
            South_Red_Led=1;
            East_Green_Led=1;
            East_Yellow_Led=1;
            East_Red_Led=0;
            break;
        case 6:
            South_Green_Led=1;
            South_Yellow_Led=1;
            South_Red_Led=0;
            East_Green_Led=1;
            East_Yellow_Led=1;
            East_Red_Led=0;
            break;
        case 7:
            South_Green_Led=0;
            South_Yellow_Led=1;
            South_Red_Led=1;
            East_Green_Led=0;
            East_Yellow_Led=1;
            East_Red_Led=1;
            break;
        case 8:
            South_Green_Led=1;
            South_Yellow_Led=0;
            South_Red_Led=1;
            East_Green_Led=1;
            East_Yellow_Led=0;
            East_Red_Led=1;
    }
}


//红绿灯状态机，判断当前时间处于哪个区间，设置对应状态,紧急状态除外
void Red_Green_Light_State_Machine(unsigned char Time){
    if(!Emergency){
        if(Time<5){
            Code=0;
        }
        else if(Time<10){
            Code=1;
        }
        else if(Time<15){
            Code=2;
        }
        else if(Time<20){
            Code=3;
        }
        else if(Time<25){
            Code=4;
        }
        else if(Time<30){
            Code=5;
        }
        else{
            Time=0;//时间归零重新计时
        }
    }
}
