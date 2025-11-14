#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <DELAY.H>
#include <TIMER0.H>
#include <SWITCH0000.H>

unsigned char Actual,Compar; //实际值和比较值
unsigned char Code;
void main(){
	LCD_Init();
	Timer0Init();
	LCD_ShowString(1,1,"Speed:");
	LCD_ShowNum(1,7,0,1);
	while(1){
		Code=switch0000();

		if(Code!=0){
			if(Code==1){
				Compar=0;
				LCD_ShowNum(1,7,0,1);
			}
			if(Code==2){
				Compar=20;
				LCD_ShowNum(1,7,1,1);
			}
			if(Code==3){
				Compar=50;
				LCD_ShowNum(1,7,2,1);
			}
			if(Code==4){
				Compar=100;
				LCD_ShowNum(1,7,3,1);
			}
		}
	}
}


void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count;
	TL0 = 0x9c;		//设置定时初值
	TH0 = 0xFf;		//设置定时初值
	Actual=(Actual+1)%100;  //循环自加
	T0Count++;
	if(T0Count>=200)  //20毫秒
	{
		T0Count=0;
		Scan_key();
	}

	if(Actual>=Compar){
		P1_0=0;
	}else{
		P1_0=1;
	}
}