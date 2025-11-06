#include <REGX52.H> 
#include <INTRINS.H> 

#include <DELAY.H>
#include <TIMER0.H>

//这个参数调整播放速度
#define sheep  250

//定义宏，方便后续写谱
#define P    0
#define L1   1
#define L1_  2
#define L2   3
#define L2_  4
#define L3   5
#define L4   6
#define L4_  7
#define L5   8
#define L5_  9
#define L6  10
#define L6_ 11
#define L7  12
#define M1  13
#define M1_ 14
#define M2  15
#define M2_ 16
#define M3  17
#define M4  18
#define M4_ 19
#define M5  20
#define M5_ 21
#define M6  22
#define M6_ 23
#define M7  24
#define H1  25
#define H1_ 26
#define H2  27
#define H2_ 28
#define H3  29
#define H4  30
#define H4_ 31
#define H5  32
#define H5_ 33
#define H6  34
#define H6_ 35
#define H7  36

//每次取反的时间
unsigned int music_HZ_time=0;
//蜂鸣器的引脚
sbit music_BZ=P2^5;
//用来存储不同音符的数组
unsigned int HZ_music_Array[]={
	0,  //无声音符
	63627,63730,63834,63927,64020,64102,64184,64259,64330,64399,64462,64523,  //低音12=L1+L1_+L2+L2_+L3+L4+L4_+L5+L5_+L6+L6_+L7
	64579,64632,64683,64731,64776,64819,64859,64897,64933,64967,64999,65029,  //中音12
	65057,65084,65109,65133,65156,65177,65197,65216,65234,65251,65267,65282,  //高音12
};
//数组索引号（全局）
unsigned char music_Index=0;

//乐谱数组，奇数位是音符，偶数位是时长，记得用0xff结尾
unsigned char code Sheet_music[]={
	P,4,
	P,4,
	P,4,
	M6,2,
	M7,2,
	
	H1,4+2,
	M7,2,
	H1,4,
	H3,4,
	
	M7,4+4+4,
	M3,2,
	M3,2,
	
	M6,4+2,
	M5,2,
	M6,4,
	H1,4,
	M5,4+4+4,
	M3,4,
	
	M4,6+2,
	M3,2,
	M4,4,
	H1,4,
	
	M3,4+4,
	P,2,
	H1,2,
	H1,2,
	H1,2,
	
	M7,4+2,
	M4_,2,
	M4_,4,
	M7,4,
	
	M7,4+4,
	P,4,
	M6,2,
	M7,2,
	
	H1,4+2,
	M7,2,
	H1,4,
	H3,4,
	
	M7,4+4+4,
	M3,2,
	M3,2,
	
	M6,4+2,
	M5,2,
	M6,4,
	H1,4,
	
	M5,4+4+4,
	M2,2,
	M3,2,
	
	M4,4,
	H1,2,
	M7,2+2,
	H1,2+2,

	H2,2,
	H2,2,
	H3,2,
	H1,2+2+4,
	
	H1,2,
	M7,2,
	M6,2,
	M6,2,
	M7,4,
	M5,4,
	
	M6,4+4+4,
	H1,2,
	H2,2,
	
	H3,4+2,
	H2,2,
	H3,4,
	H5,4,
	
	H2,4+4+4,
	M5,2,
	M5,2,
	
	H1,4+2,
	M7,2,
	H1,4,
	H3,4,
	H3,4+4+4+4,
	
	M6,2,
	M7,2,
	H1,4,
	M7,4,
	H2,2,
	H2,2,
	
	H1,4+2,
	M5,2+4+4,
	
	H4,4,
	H3,4,
	H2,4,
	H1,4,
	
	H3,4+4+4,
	H3,4,
	
	H6,4+4,
	H5,4,
	H5,4,
	
	H3,2,
	H2,2,
	H1,4+4,
	P,2,
	H1,2,
	
	H2,4,
	H1,2,
	H2,2,
	H2,4,
	H5,4,
	
	H3,4+4+4,
	H3,4,
	
	H6,4+4,
	H5,4+4,
	
	H3,2,
	H2,2,
	H1,4+4,
	P,2,
	H1,2,
	
	H2,4,
	H1,2,
	H2,2+4,
	M7,4,
	
	M6,4+4+4,
	M6,2,
	M7,2,
	
	0xff
};


void main(){
	Timer0Init();//中断初始化
	while(1){
		if(Sheet_music[music_Index]!=0xff){
			music_HZ_time=HZ_music_Array[Sheet_music[music_Index]];
			music_Index++;
			delay(sheep*Sheet_music[music_Index]);
			music_Index++;
			TR0 = 0;
			delay(7);
			TR0 = 1;
		}
		else{
			music_Index=0;
			TR0 = 0;
			delay(7);
			TR0 = 1;
		}
	}
}


//中断函数，读取通断蜂鸣器时间来控制频率
void Timer0_Routine() interrupt 1
{
	TH0=music_HZ_time/256;  //取64535高八位
	TL0=music_HZ_time%256;  //取64535低八位
	if(music_HZ_time){
		music_BZ=~music_BZ;
	}
	else{
		music_BZ=0;
	}
}