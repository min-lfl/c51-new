#include <REGX52.H> 
#include <INTRINS.H> 

#include <DELAY.H>
#include <TIMER0.H>

#include <LCD1602.H>
#include <DS18B20.H>


unsigned char Temp_Int; //温度的整数部分
unsigned int 	Temp_Float;//温度的小数部分


void main(){
	LCD_Init();
	
	
	while(1){

		DS18C02_Handledate_read(&Temp_Int,&Temp_Float);
		
		LCD_ShowString(1,1,"Celsius:");
		LCD_ShowNum(2,1,Temp_Int,2);
		LCD_ShowString(2,3,".");
		LCD_ShowNum(2,4,Temp_Float,4);
		LCD_ShowString(2,8,"C");
		
		

	}
}
