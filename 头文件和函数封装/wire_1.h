#ifndef __1_WIRE_H__
#define __1_WIRE_H__

//初始化，无论读写操作都应该先初始化一下，返回1为初始化失败，返回0为初始化成功
bit init_1_wire();
//写一个字节
void write_Byte_1_wire(unsigned char Byte);
//读一个字节
unsigned char  read_Byte_1_wire();
	
#endif