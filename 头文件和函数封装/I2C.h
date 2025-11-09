#ifndef __I2C_H__
#define __I2C_H__

void start_I2C();											//数据头
void stop_I2C();											//数据尾	
void write_I2C(unsigned char Byte);		//发送字节
unsigned char read_I2C();							//接收字节
void s_I2c(char Bit);									//发送应答，参数0为应答，参数1为不应答
char r_I2c();													//接收应答

#endif