#include <REGX52.H>
#include <INTRINS.H>

#include <InterruptTimer0.H>

#define Echo P1_1

void Delay12us()		//@11.0592MHz
{
	unsigned char i;

	i = 3;
	while (--i);
}


void HCSR04_init(){
	P1_0=0;
	P1_1=0;
}
	
void HCSR04_shoot(){
	P1_0=0;
	P1_0=1;
	Delay12us();
	P1_0=0;
}

unsigned int Data[10];



unsigned int Get_HCSR04_Data(){
	unsigned int num=0,Data;
	
	HCSR04_init();
	HCSR04_shoot();
	
	while(Echo==0 && num<60000){num++;_nop_();};
	set_InterruptTimer(0x00);
	run_InterruptTimer(1);
	
	num=0;
	while(Echo==1 && num<60000){num++;_nop_();};
	Data=read_InterruptTimer();
	set_InterruptTimer(0x00);
	return Data;
}

//unsigned int PING_Get_HCSR04_Data(){
//	unsigned char i=0;
//	unsigned int PING_Data;
//	for(i=0;i<2;i++){
//		Data[i]=Get_HCSR04_Data();
//	}
//	for(i=0;i<2;i++){
//		PING_Data=(PING_Data+Data[i])/2;
//	}
//	return	PING_Data;
//}


//void InterruptTimer2_init();
//void set_InterruptTimer(unsigned int Time);
//void run_InterruptTimer(unsigned char Code);
//unsigned int read_InterruptTimer();