#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <AT24C02.H>
#include <DELAY.H>
#include <TIMER0.H>
#include <SWITCH0000.H>
#include <888led.H>


unsigned char key,i;
unsigned char h=7,m=23,date=55;
unsigned int T0Count2;


void main(){
	Timer0Init();

	while(1){
		key=switch0000();
		if(key!=0){
			if(key==1){
				date+=1;
				T0Count2=0;
			}
			if(key==2){
				date-=1;
				T0Count2=0;
			}
			if(key==3){
				date=3;
			}
			if(key==4){
				date=4;
			}
		}
		
		
		if(date>=60){
			date=0;
			m++;
			if(m>=60){
				m=0;
				h++;
				if(h>=24){
					h=0;
				}
			}
		}
		Set_888led(1,h/10);
		Set_888led(2,h%10);
		
		Set_888led(3,11);
		
		Set_888led(4,m/10);
		Set_888led(5,m%10);
		
		Set_888led(6,11);
		
		Set_888led(7,date/10);
		Set_888led(8,date%10);
		
	}
}



void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count,T0Count1;

	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	T0Count1++;
	T0Count2++;
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
	if(T0Count2>=1000)  //1000毫秒秒表加1
	{
		T0Count2=0;
		date++;
	}
}