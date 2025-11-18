#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库


#include <DELAY.H>
#include <LCD1602.H>
//#include <InterruptTimer0.H>
//#include <Interrupt.H>
#include <RedWAI.H>


//void Delay10ms()		//@11.0592MHz
//{
//	unsigned char i, j;

//	i = 99;
//	j = 154;
//	do
//	{
//		while (--j);
//	} while (--i);
//}

char num=1;
unsigned char Red,run=0x00;


void main(){
	LCD_Init();
	RedWAI_init();

	LCD_ShowString(1,1,"Shoop:");
	while(1){
		Red=get_Red_Data();
		if(Red){
			LCD_ShowHexNum(2,1,Red,2);
		}
	}
}