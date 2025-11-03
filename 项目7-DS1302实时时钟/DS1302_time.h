#ifndef __DS1302_time_H__
#define __DS1302_time_H__

unsigned char read_DS1302(unsigned char Byte);
void write_DS1302(unsigned char Byte,unsigned char time);
void init_DS1302();
#endif