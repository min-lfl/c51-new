#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

#include <DELAY.H>

unsigned char switch0000()
{
	unsigned char KeyNumber=0;
	
	if(P3_1==0){delay(2);while(P2_1==0);delay(2);KeyNumber=1;}
	if(P3_0==0){delay(2);while(P2_0==0);delay(2);KeyNumber=2;}//这里其实是电路板上把k1和k2接反了
	if(P3_2==0){delay(2);while(P2_2==0);delay(2);KeyNumber=3;}
	if(P3_3==0){delay(2);while(P2_3==0);delay(2);KeyNumber=4;}
	
	return KeyNumber;
}