#include <REGX52.H>

//标准延迟函数，参数为毫秒数
void Delay1ms(unsigned char xms)		//@12.000MHz
{
	unsigned char i, j;
	
	while(xms)
	{
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	xms--;
	}
}


void main()
{
	int tmp=0x01;
	while(1)
	{
		if(P3_0==0)
		{
			//按键检测（含过滤抖动）
			Delay1ms(20);
			while(P3_0==0);
			Delay1ms(20);
			tmp=tmp<<1;
		}
		if(P3_1==0)
		{
			//按键检测（含过滤抖动）
			Delay1ms(20);
			while(P3_1==0);
			Delay1ms(20);
			tmp=tmp>>1;
		}
		//检测是否超出灯带，超出就把灯回到灯带区域
		if(tmp<=0){
			tmp=0x80;
		}
		if(tmp>=256){
			tmp=0x01;
		}
		P2=~tmp;
	}
}