#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <DELAY.H>
#include <HCSR04.H>
#include <InterruptTimer0.H>



unsigned int num,a;
void main(){
	LCD_Init();
	InterruptTimer2_init();
	
	
	while(1){
		num=Get_HCSR04_Data();
		num*=1.085*0.017;
		
		if(num<=40){
			P2_0=0x00;
			P2_1=0x00;
			P2_2=0x00;
			P2_3=0x00;
			P2_4=0x00;
		}else{
			P2_0=0xff;
			P2_1=0xff;
			P2_2=0xff;
			P2_3=0xff;
			P2_4=0xff;
		}
//		delay(1);

		LCD_ShowNum(1,1,num,3);

	}
}

//void HCSR04_init();
//	
//void HCSR04_shoot();
//	
//unsigned int Get_HCSR04_Data();