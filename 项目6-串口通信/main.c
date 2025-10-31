#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

#include <DELAY.H>
#include <Uart.H>

unsigned char sec=0;

void main(){
	Uart_Init();

	while(1){
//		Uart_senbyte(sec);
//		sec++;
//		delay(1000);
	}
}

void UAET_Routine() interrupt 4
{
	if(RI==1){
		
		RI=0;	
	}
}