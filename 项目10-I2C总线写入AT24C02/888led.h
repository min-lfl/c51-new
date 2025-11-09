#ifndef __888led_H__
#define __888led_H__

//扫描函数（放定时器里，2ms执行一次）
void Scan_888led();
//更改数码管要显示的值，第一个参数是位置，第二个参数是值
//值0~9为数字，10为空白，11为"-"
void Set_888led(unsigned char Location,Number);
	
#endif


/*定时器示例，开启定时器后直接复制到主函数，
//使用方法：然后在主函数里用Set_888led函数更改全局变量就好了
void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count1;

	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count1++;
	if(T0Count1>=2)  //2毫秒显示一个数字，在下一个两毫秒显示下一个数字
	{
		T0Count1=0;
		Scan_888led();
	}
}
*/