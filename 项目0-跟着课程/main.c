#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

//定义全局变量用来存储流水灯状态
unsigned char status=0xfe;

//标准的循环延迟（精确1ms）
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

//流水灯，函数被执行就会正流一次
void up_down(){
	P2=status;
	status=_crol_(status,1);
	delay(3);
}

//倒序流水灯，函数被执行就会倒流8次
void down_up(){
	int i;
	for(i=0;i<8;i++){
		P2=status;
		status=_cror_(status,1);
		delay(3);
	}
}

//集体亮灭，函数被执行就会亮灭5次
void Twinkle(){
	int i;
	for(i=0;i<5;i++){
		P2=0x00;
		delay(3);
		P2=0xff;
		delay(3);
	}
}


void main()
{
	EA=1;EX0=1;IT0=1;PX0=0;//中断器0的初始化，PX0=0;为优先级0
	EA=1;EX1=1;IT1=1;PX1=1;//中断器1的初始化，PX1=1;为优先级1
	
	while(1){up_down();}//主循环
}

//中断0
void int0() interrupt 0
{
	Twinkle();
}

//中断1
void int1() interrupt 2
{
	down_up();
}
