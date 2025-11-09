#ifndef __AT24C02_H__
#define __AT24C02_H__

//在哪个位置写什么，返回值表示是否写入超时，1代表超时，0代表正常写入
bit write_AT24C02(unsigned char ADDRESS,Byte);

//在什么地方读取，返回值是读取到的字节
unsigned char  read_AT24C02(unsigned char ADDRESS);


#endif