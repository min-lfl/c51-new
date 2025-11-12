#include <REGX52.H>
#include <INTRINS.H>

#include <DELAY.H>
#include <LCD1602.H>

char str[] = "Hello, world!Hello, world!";
	
void main(){
	LCD_Init();
	LCD_ShowChar(1,2,str);
	while(1){
		delay(600);
		LCD_zuo();
	}
}