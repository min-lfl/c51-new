#include <REGX52.H> 
#include <INTRINS.H> 

#include <DELAY.H>
#include <TIMER0.H>

void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 29;
	while (--i);
}



void main(){
	P3_7=0;
	Delay500us();
	P3_7=1;
//	Delay70us();
	if(P3_7==0){
		P2=0x00;
	}
	while(1){
	}
}
