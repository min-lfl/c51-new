#include <REGX52.H>

sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;
sbit DS1302_SCLK=P3^6;


//初始化复位寄存器函数
void init_DS1302(){
	DS1302_CE=0;DS1302_IO=0;DS1302_SCLK=0;
}

//写入数据（初步封装）
void write_DS1302(unsigned char Byte,unsigned char time){
	unsigned char i,time_bcd;
	//转化bcd格式
	switch(Byte){
		case 0x81:  //秒
        time_bcd=(time/10*16)+time%10;
        break;
		case 0x83:  //分
        time_bcd=(time/10*16)+time%10;
        break;
		case 0x85:  //时
        time=time;
        break;
		case 0x87:  //天
        time_bcd=(time/10*16)+time%10;
        break;
		case 0x89:  //月
        time_bcd=(time/10*16)+time%10;
        break;
		case 0x8b:  //星期
        time=time;
        break;
		case 0x8d:  //年
        time_bcd=(time/10*16)+time%10;
        break;
	}
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


//读出数据（初步封装）
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
	switch(Byte){
		case 0x81:  //秒
        return time=time/16*10+time%16;
        break;
		case 0x83:  //分
        return time=time/16*10+time%16;
        break;
		case 0x85:  //时
        return time=time%32;
        break;
		case 0x87:  //天
        return time=time/16*10+time%16;
        break;
		case 0x89:  //月
        return time=time/16*10+time%16;
        break;
		case 0x8b:  //星期
        return time=time%8;
        break;
		case 0x8d:  //年
        return time=time/16*10+time%16;
        break;
	}
}


//写入时间和读出时间一个函数搞定
unsigned char write_and_read_DS1302(unsigned char code1,unsigned char num){
	unsigned char where;
	
	//判断是不是写保护,需不需要关闭写保护
	if(read_DS1302(0x8f)){write_DS1302(0x8e,0x00);}
	
	if(code1>6){return 66;}
	
	if(num<=99){//判断是要读还是写，小于等于99是写，大于99是读
		where=0x80+(code1*2);
		write_DS1302(where,num);
		return 1;
	}
	else{
		where=0x80+(code1*2)+1;
		return read_DS1302(where);
	}
	return 0;
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