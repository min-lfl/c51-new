#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

//这是一个电子时钟的案例

#include <TIMER0.H>
#include <LCD1602.H>
#include <DELAY.H>

//定义时分秒的变量
unsigned char h=19,m=21,s,ms;

void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=91) //这里应该设置100毫秒的，但是考虑到中断函数执行时间，所以定为91毫秒，加上程序执行时间正好100毫秒
	{
		ms++;
		if(ms>=10){s++;ms=0;}
		if(s>=60){m++;s=0;}
		if(m>=60){h++;m=0;}
		if(h>=24){h=0;}
		
		T0Count=0;
	}
	
}


void main(){
	Timer0Init();
	LCD_Init();
	
	LCD_ShowString(1,1,"Time-c       ^_^");
	LCD_ShowString(2,1,"  :  :  .");
	while(1){
		LCD_ShowNum(2,1,h,2);
		LCD_ShowNum(2,4,m,2);
		LCD_ShowNum(2,7,s,2);
		LCD_ShowNum(2,10,ms,1);
	}
}



