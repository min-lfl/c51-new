#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库


#include <WIRE_1.H>

/**
	* @brief		发送温度变化指令，让传感器把现在温度写入寄存器，每次读取前要执行一次更新数据
	* @param		无
	* @retval		无
	*/
void Start_DS18C02(){
	init_1_wire();
	write_Byte_1_wire(0xCC);								//跳过ROM
	write_Byte_1_wire(0x44);		//发送开启温度变化指令
}

/**
	* @brief		发送读取温度指令并返回int数值，从低到高1-4位为小数，4-11位为整数部分，12-16为为无数据
	* @param		无
	* @retval		返回的数据，一共16位2进制，数据格式为@brief内的说明
	*/
unsigned int Read_DS18C02(){
	unsigned int date,Middle;
	Start_DS18C02();
	init_1_wire();
	write_Byte_1_wire(0xCC);								//跳过ROM
	write_Byte_1_wire(0xBE);   	//发送开始读取指令
	date = read_Byte_1_wire();
  Middle = read_Byte_1_wire();
	date|=Middle<<8;
	return date;
}

///**
//	* @brief		把4位浮点二进制（后4位补0）转化为4位整型，如1101 0000转化为8125
//	* @param		后4位补0的二进制数小数，比如0.75的小数部分是1100 0000
//	* @retval		输出整数，1100 0000->7500，1101 0000->8125
//	*/

unsigned int Floatchar_to_Decimalint(unsigned char binary) {
  unsigned long temp = (unsigned long)binary * 10000;
  return temp / 256;  
}

void DS18C02_Handledate_read(unsigned char *numint,unsigned int *numfloat){
	unsigned int Temperature;//定义变量保存温度
	Temperature = Read_DS18C02();
	*numint = Temperature >> 4;
	*numfloat = Floatchar_to_Decimalint((Temperature<<12)>>8);
}




