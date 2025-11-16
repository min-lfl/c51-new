#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <DELAY.H>
#include <XPT2046.H>


unsigned int num;

void main(){
	LCD_Init();
	LCD_ShowString(1,1,"Value:");
	while(1){
		num=XPT2046_Read(1);
		LCD_ShowNum(2,1,num,6);
		delay(10);
	}
}