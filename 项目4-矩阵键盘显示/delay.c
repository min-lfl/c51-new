#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

//标准的循环延迟
void delay(unsigned char xms){
	unsigned char i, j;
	i = 2;
	j = 239;
	do{
	do{
		while (--j);
	} while (--i);
	} while (--xms);
}