#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

void Interrupt_init(){
	IT0=1;			//设置为下降沿触发
	IE0=0;     //中断标志位
	EX0=1;			//打开EX0中断
	EA=1;				//打开总中断
	PX0=1;      //设置优先级高
}

//void Interrupt_Routine() interrupt 0
//{
//	num++;
//}