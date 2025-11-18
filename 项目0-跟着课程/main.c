#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库
#include <TIMER0.H>

void main(){
	Timer0Init();
	while(1){
	}
}


void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count,T1Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	T1Count++;
	if(T0Count>=100)  //100毫秒
	{
		T0Count=0;
		P2_0=~P2_0;
	}
	if(T1Count>=300)  //300毫秒
	{
		T1Count=0;
		P2_7=~P2_7;
	}
}

