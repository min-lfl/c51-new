//引入reg51库里的大量函数
#include <REGX52.H> //c52库
//引入两个变量类型
#define uchar unsigned char
#define uint unsigned int

char tab[]={0xfe,0xfd,0xfb,0xf7,  0xef,0xdf,0xbf,0x7f};

void delays(char num) {
		//num的值至少取1
    unsigned char i, j, k;
    // 三层循环嵌套，通过调整循环变量初值来逼近1秒
    for(i = 5*num; i > 0; i--)
        for(j = 4; j > 0; j--)
            for(k = 248; k > 0; k--);
}

void main()
{
	int bz;
	while(1)
	{
		for(bz=0;bz<8;bz++)
		{
			P2=0X00;
			delays(20);
		}
	}
}

