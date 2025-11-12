#ifndef __DS18B20_H__
#define __DS18B20_H_

//实时读取温度，最小刻度0.0625，前一个指针返回温度整数部分，后一个指针返回温度小数部分，小数部分格式为4位整数如0.8125为8125，0.75为0075
void DS18C02_Handledate_read(unsigned char *numint,unsigned int *numfloat);

#endif