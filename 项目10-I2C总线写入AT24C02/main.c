#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include <AT24C02.H>
#include <DELAY.H>
#include <TIMER0.H>
#include <SWITCH0000.H>
#include <888led.H>


unsigned char key;
unsigned char Min,Sec,Minisec;//分，秒，毫秒
unsigned char start;

void main(){
	Timer0Init();

	while(1){
		
		//操作判定函数
		key=switch0000();
		if(key!=0){
			if(key==1){
				start=~start;//取反控制启停
			}
			if(key==2){// 清零
				Min=0;
				Sec=0;
				Minisec=0;
			}
			if(key==3){
				write_AT24C02(1,Min);
				write_AT24C02(2,Sec);
				write_AT24C02(3,Minisec);
			}
			if(key==4){
				Min=read_AT24C02(1);
				Sec=read_AT24C02(2);
				Minisec=read_AT24C02(3);
			}
		}
		
		//显示位
		Set_888led(1,Min/10);
		Set_888led(2,Min%10);
		
		Set_888led(3,11);
		
		Set_888led(4,Sec/10);
		Set_888led(5,Sec%10);
		
		Set_888led(6,11);
		
		Set_888led(7,Minisec/10);
		Set_888led(8,Minisec%10);

	}
}

//秒表自加函数，会自动进位，执行一次自加一次
void sec_add(){
	//停止计时控制
	if(start){
		Minisec++;
		if(Minisec>=100){
			Minisec=0;
			Sec++;
			if(Sec>=60){
				Sec=0;
				Min++;
				if(Min>=60){
					Min=0;
				}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count,T0Count1,T0Count2;

	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	T0Count1++;
	T0Count2++;
	if(T0Count>=20)  //20毫秒
	{
		T0Count=0;
		Scan_key();
	}
	if(T0Count1>=2)  //2毫秒显示一个数字，在下一个两毫秒显示下一个数字
	{
		T0Count1=0;
		Scan_888led();
	}
	if(T0Count2>=10)  //10毫秒秒表加1
	{
		T0Count2=0;
		sec_add();
	}
}