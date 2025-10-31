#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

#include <delay.h>
#include <888led.h>
#include <LCD1602.H>


void main()
{
	int num=60,a=300;
	while(1){
		a--;
		Nixie(4,num/10);
		delay(1);
		Nixie(5,num%10);
		delay(1);
		if(a<=0){
			num--;
			a=300;
		}
	}
}