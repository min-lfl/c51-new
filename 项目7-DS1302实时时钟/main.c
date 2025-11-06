#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <DELAY.H>

#include <DS1302_time.H>


void  main(){
	unsigned char time;
	LCD_Init();
	LCD_ShowString(1,3,"-  -");
	LCD_ShowString(2,3,":  :");
	
	
	write_and_read_DS1302(0,1);
	write_and_read_DS1302(1,1);
	write_and_read_DS1302(2,1);
	while(1){
		time=write_and_read_DS1302(6,0xff);//年
		LCD_ShowNum(1,1,time,2);
		time=write_and_read_DS1302(4,0xff);//月
		LCD_ShowNum(1,4,time,2);
		time=write_and_read_DS1302(3,0xff);//日
		LCD_ShowNum(1,7,time,2);
		time=write_and_read_DS1302(2,0xff);//时
		LCD_ShowNum(2,1,time,2);
		time=write_and_read_DS1302(1,0xff);//分
		LCD_ShowNum(2,4,time,2);
		time=write_and_read_DS1302(0,0xff);//秒
		LCD_ShowNum(2,7,time,2);
	}
}

