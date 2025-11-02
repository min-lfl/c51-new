#include <REGX52.H>

sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;
sbit DS1302_SCLK=P3^6;




//读出时间
unsigned char read_DS1302(unsigned char Byte){
	unsigned char i,time=0;
	DS1302_IO=0;DS1302_SCLK=0;  //初始化I/O口，避免前面程序对读取函数的影响
	
	//像ds1302发送一段数据表明要读取哪些
	DS1302_CE=1;
	for(i=0;i<8;i++){
		DS1302_IO=Byte&(0x01<<i);
		DS1302_SCLK=0;DS1302_SCLK=1;
	}
	
	//开始读取
	for(i=0;i<8;i++){
		DS1302_SCLK=1;DS1302_SCLK=0;
		if(DS1302_IO){time|=0x01<<i;}
	}
	
	DS1302_CE=0;DS1302_IO=0;//完成一次读取循环后把用到的接口复位
	return time;
}