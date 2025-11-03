#ifndef __DS1302_time_H__
#define __DS1302_time_H__

//初始化
void init_DS1302();
//写入函数（初级封装）
void write_DS1302(unsigned char Byte,unsigned char time);
//读取函数（初级封装）
unsigned char read_DS1302(unsigned char Byte);
//读取和写入函数（高级封装）
unsigned char write_and_read_DS1302(unsigned char code1,unsigned char num);
/*
示例
write_and_read_DS1302(2,21);
在小时位写入一个21
write_and_read_DS1302(0,0xff);
在秒钟位读取数据
参数说明：
第一个参数是在哪位读写0秒1分2时3日4月5周6年，不可大于6，0x8e写入写保护，0x8e读取写保护
第二个参数写入什么数据，0~99为写入数据，大于100或0xff为读取数据
*/

#endif