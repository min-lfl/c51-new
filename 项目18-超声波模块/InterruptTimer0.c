#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

void InterruptTimer2_init(){
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TH1 = 0x00;		//设置定时初值
	TL1 = 0x00;		//设置定时初值
	TF1 = 0;		//清除TF0标志
	TR1 = 0;		//定时器0停止计时
//	ET1=1;    //允许定时器0中断
}



void set_InterruptTimer(unsigned int Time){
	TH1=Time/256;
	TL1=Time%256;
}

void run_InterruptTimer(unsigned char Code){
	if(Code==1){
		TR1 = 1;
	}else{
		TR1 = 0;
	}
}

unsigned int read_InterruptTimer(){
	unsigned int Num=0;
	Num=TH1<<8|TL1;
	return (Num/92)*100;
}



//void function_name() interrupt 1
//{
////	P2=~P2;
//	TF1=0;
//}