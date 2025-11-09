#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

#include <WIRE_1.H>

void Start_DS18C02(){
	init_1_wire();
	write_Byte_1_wire(0xCC);								//跳过ROM
	write_Byte_1_wire(0x44);		//发送开启温度变化指令
}


unsigned int Read_DS18C02(){
	unsigned int date,Middle;
	init_1_wire();
	write_Byte_1_wire(0xCC);								//跳过ROM
	write_Byte_1_wire(0xBE);   	//发送开始读取指令
	date = read_Byte_1_wire();
  Middle = read_Byte_1_wire();
	date|=Middle<<8;
	return date;
}