#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <DELAY.H>

#include <DS1302_time.H>


void  main(){
	unsigned char time;
	init_DS1302();
	write_DS1302();
	LCD_Init();
	while(1){
		time=read_DS1302(0x83);
		LCD_ShowNum(1,9,(time/16*10+time%16),2); //bcd代码转10进制输出
	}
}



//50=0101 0000