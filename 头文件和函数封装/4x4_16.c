#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

#include <delay.h>


char button(){
	char KeyNumber=0;
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){delay(2);while(P1_7==0);delay(2);KeyNumber=1;}
	if(P1_6==0){delay(2);while(P1_6==0);delay(2);KeyNumber=5;}
	if(P1_5==0){delay(2);while(P1_5==0);delay(2);KeyNumber=9;}
	if(P1_4==0){delay(2);while(P1_4==0);delay(2);KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){delay(2);while(P1_7==0);delay(2);KeyNumber=2;}
	if(P1_6==0){delay(2);while(P1_6==0);delay(2);KeyNumber=6;}
	if(P1_5==0){delay(2);while(P1_5==0);delay(2);KeyNumber=10;}
	if(P1_4==0){delay(2);while(P1_4==0);delay(2);KeyNumber=14;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){delay(2);while(P1_7==0);delay(2);KeyNumber=3;}
	if(P1_6==0){delay(2);while(P1_6==0);delay(2);KeyNumber=7;}
	if(P1_5==0){delay(2);while(P1_5==0);delay(2);KeyNumber=11;}
	if(P1_4==0){delay(2);while(P1_4==0);delay(2);KeyNumber=15;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){delay(2);while(P1_7==0);delay(2);KeyNumber=4;}
	if(P1_6==0){delay(2);while(P1_6==0);delay(2);KeyNumber=8;}
	if(P1_5==0){delay(2);while(P1_5==0);delay(2);KeyNumber=12;}
	if(P1_4==0){delay(2);while(P1_4==0);delay(2);KeyNumber=16;}
	
	return KeyNumber;
}