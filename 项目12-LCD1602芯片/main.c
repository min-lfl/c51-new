#include <REGX52.H>
#include <INTRINS.H>

#include <DELAY.H>
#include <LCD1602.H>

#include <SWITCH0000.H>
#include <TIMER0.H>


#define PWM P1 

unsigned char Speed;
	
void main(){
	unsigned char Code,i;
	LCD_Init();
	LCD_ShowString(1,1,"Speed:");
	PWM=0x00;
	Timer0Init();
	while(1){
		Code=switch0000();
		if(Code!=0){
			if(Code==1){
				Speed=0;
				LCD_ShowNum(1,7,0,1);
			}
			if(Code==2){
				Speed=40;
				LCD_ShowNum(1,7,1,1);
			}
			if(Code==3){
				Speed=90;
				LCD_ShowNum(1,7,2,1);
			}
			if(Code==4){
				Speed=1000;
				LCD_ShowNum(1,7,3,1);
			}
		}
		if(Speed!=0){
			PWM=0xff;
			for(i=0;i<Speed;i++){
				_nop_();
				_nop_();
				_nop_();
			}
			PWM=0x00;
			for(i=0;i<100;i++){
				_nop_();
				_nop_();
				_nop_();
			}
		}else{
			PWM=0x00;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=20)  //20毫秒
	{
		T0Count=0;
		Scan_key();
	}
}