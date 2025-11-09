#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

sbit DS18B20_DQ=P3^7;


//声明一些延迟函数，用来度量时序
void Delay500us();
void Delay120us();
void Delay60us();
void Delay30us();
void Delay10us();

	
bit init_1_wire(){
	DS18B20_DQ=0;
	Delay500us();  	//拉低至少500us
	DS18B20_DQ=1;		//拉高电平
	Delay60us();		
	Delay30us();		//等待90ms从机设备响应后
	if(DS18B20_DQ==0){//读取电平，判断输出
		return 0;
	}
	return 1;
}

void write_Bit_1_wire(bit Bit){
	if(Bit){
		DS18B20_DQ=0;
		Delay10us();//只拉低10微秒表示1
		DS18B20_DQ=1;
		Delay60us();//等待60微妙从机读取完成
	}
	else{
		DS18B20_DQ=0;
		Delay60us();		
		Delay10us();		//拉低70ms表示0
		DS18B20_DQ=1;
		Delay10us();   //因为是弱上拉，我们这里等待10微妙电容充电
	}
}


bit read_Bit_1_wire(){
	bit date;
	
	DS18B20_DQ=0;
	Delay10us();//只拉低10微秒表示读取
	DS18B20_DQ=1;
	
	Delay10us();//等待20ms从机响应
	date=DS18B20_DQ; //读取
	Delay10us();
	Delay30us();//等待完一个周期
	return date;
}

void write_Byte_1_wire(unsigned char Byte){
	unsigned char i;
	Delay120us();
	Delay120us();//等待240us把初始化的影响过滤掉
	for(i=0;i<8;i++){
		write_Bit_1_wire(Byte&(0x01<<i));
	}
}

unsigned char  read_Byte_1_wire(){
	unsigned char date=0,i;
	Delay120us();
	Delay120us();//等待240us把初始化的影响过滤掉
	for(i=0;i<8;i++){
		if(read_Bit_1_wire()){date|=0x01<<i;}
	}
	return date;
}








void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

void Delay120us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 52;
	while (--i);
}


void Delay60us()		//@11.0592MHz
{
	unsigned char i;

	i = 25;
	while (--i);
}


void Delay30us()		//@11.0592MHz
{
	unsigned char i;

	i = 11;
	while (--i);
}


void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}