#include <REGX52.H> 
#include <INTRINS.H> 

#include <DELAY.H>
#include <TIMER0.H>

#include <LCD1602.H>
#include <DS18B20.H>

unsigned int Time;//原始数据
unsigned char Temp_Int,Temp_Float; //温度的整数部分和小数部分

unsigned char reverse_low_4bits(unsigned char byte) {
    unsigned char high = byte & 0xF0;    // 保存高4位
    unsigned char low = byte & 0x0F;     // 取低4位
    
    // 反转低4位：00001011 -> 低4位1011 -> 1101
    low = ((low & 0x1) << 3) | 
          ((low & 0x2) << 1) | 
          ((low & 0x4) >> 1) | 
          ((low & 0x8) >> 3);
    
    return high | low;  // 0000 | 1101 = 00001101
}


void main(){
	LCD_Init();
	
	
	while(1){
		Start_DS18C02();
		Time=Read_DS18C02();
		Temp_Int = Time >> 4;
		Temp_Float= reverse_low_4bits((Time << 12) >> 12);
		LCD_ShowString(1,1,"Celsius:");
		LCD_ShowNum(2,1,Temp_Int,2);
		LCD_ShowString(2,3,".");
		LCD_ShowNum(2,4,Temp_Float,2);
		LCD_ShowString(2,6,"C");
	}
}
