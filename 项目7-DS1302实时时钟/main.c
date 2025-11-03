#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <DELAY.H>

#include <DS1302_time.H>


void  main(){
	unsigned char time;
	LCD_Init();
	LCD_ShowString(2,3,":  :");
	
	write_and_read_DS1302(2,0);
	while(1){
		time=write_and_read_DS1302(2,0xff);
		LCD_ShowNum(2,1,time,2);
		time=write_and_read_DS1302(1,0xff);
		LCD_ShowNum(2,4,time,2);
		time=write_and_read_DS1302(0,0xff);
		LCD_ShowNum(2,7,time,2);
	}
}

