#include <REGX52.H>

sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;
sbit DS1302_SCLK=P3^6;


//初始化复位寄存器函数
void init_DS1302(){
	DS1302_CE=0;DS1302_IO=0;DS1302_SCLK=0;
}

//写入时间
void write_DS1302(unsigned char Byte,unsigned char time){
	unsigned char i,time_bcd;
	time_bcd=(time/10*16)+time%10;//转化bcd格式
	init_DS1302();//初始化复位寄存器
	
	//向ds1302发送一段数据表明要写在哪里
	DS1302_CE=1;
	for(i=0;i<8;i++){
		DS1302_IO=Byte&(0x01<<i);
		DS1302_SCLK=0;DS1302_SCLK=1;
	}
	//开始写入
	for(i=0;i<8;i++){
		DS1302_IO=time_bcd&(0x01<<i);
		DS1302_SCLK=0;DS1302_SCLK=1;
	}
	
	init_DS1302();//初始化复位寄存器
}


//读出时间
unsigned char read_DS1302(unsigned char Byte){
	unsigned char i,time=0;
	init_DS1302();//初始化复位寄存器
	
	//向ds1302发送一段数据表明要读取哪些
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
	
	init_DS1302();//初始化复位寄存器
	return time;
}





//	DS1302_CE=0;DS1302_IO=0;DS1302_SCLK=0;
//	
//	DS1302_CE=1;
//	
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //8
//	DS1302_IO=1;DS1302_SCLK=0;DS1302_SCLK=1; //7
//	DS1302_IO=1;DS1302_SCLK=0;DS1302_SCLK=1; //6
//	DS1302_IO=1;DS1302_SCLK=0;DS1302_SCLK=1; //5
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //4
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //3
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //2
//	DS1302_IO=1;DS1302_SCLK=0;DS1302_SCLK=1; //1
//	
//	
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //8
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //7
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //6
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //5
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //4
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //3
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //2
//	DS1302_IO=0;DS1302_SCLK=0;DS1302_SCLK=1; //1
//	