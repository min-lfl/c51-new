#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <AT24C02.H>
#include <DELAY.H>
#include <TIMER0.H>
#include <SWITCH0000.H>

unsigned char date,key;


void main(){
	LCD_Init();
	Timer0Init();
	LCD_ShowString(1,1,"clool");
	
//	write_AT24C02(1,123);
//	date=read_AT24C02(1);
//	LCD_ShowNum(2,1,date,3);
	while(1){
		key=switch0000();
		if(key!=0){
			if(key==1){
				LCD_ShowString(2,1,"1");
			}
			if(key==2){
				LCD_ShowString(2,1,"2");
			}
			if(key==3){
				LCD_ShowString(2,1,"3");
			}
			if(key==4){
				LCD_ShowString(2,1,"4");
			}
		}
//		delay(10);
	}
}



void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=20)  //1000毫秒
	{
		T0Count=0;
		Scan_key();
	}
}