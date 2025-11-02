#include <REGX52.H> //c52库

/**
	* @brief		串口通信中断初始化
	* @param		无
	* @retval		无
	*/
void Uart_Init(void)		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
//	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}

/**
	* @brief		发送函数，发送一个字节
	* @param		要发送的字节
	* @retval		无
	*/
void Uart_senbyte(unsigned char Byte){
	SBUF=Byte;
	while(TI==0);
	TI=0;
}


/*串口中断函数模板
void UAET_Routine() interrupt 4
{
	if(RI==1){
	《接收变量》=SBUF;
		RI=0;	
	}
}
*/
