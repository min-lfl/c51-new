#include <REGX52.H>
#include <SWITCH0000.H>
#include <DELAY.H>
#include <TIMER0.H>
//#include <DELAY.H>

// 共阳极数码管段码表 (0-9)
unsigned char code SEGMENT_CODES[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

void main() {
    unsigned int num = 42;  //目前bug：在num>=30|num<=49时，num会在39-40间反复横跳
	unsigned char key = 0;
	Timer0Init();
	
	
    while(1) {
        key=switch0000();
		if(key!=0){
			if(key==3){if(num!=0){num++;}}
			if(key==4){if(num!=0){num--;}}
		}

    P0=SEGMENT_CODES[num/10];
	P1=SEGMENT_CODES[num%10];
	
//	delay(10);
    }
}

void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=20)  //20毫秒
	{
		T0Count=0;
		Scan_key();
	}
}














//AT89C52引脚    数码管引脚    备注
//P1.0   --->   a段        通过220Ω限流电阻
//P1.1   --->   b段        通过220Ω限流电阻
//P1.2   --->   c段        通过220Ω限流电阻
//P1.3   --->   d段        通过220Ω限流电阻
//P1.4   --->   e段        通过220Ω限流电阻
//P1.5   --->   f段        通过220Ω限流电阻
//P1.6   --->   g段        通过220Ω限流电阻
//P1.7   --->   dp段       小数点，通过220Ω限流电阻
//5V      --->   公共阳极(COM)