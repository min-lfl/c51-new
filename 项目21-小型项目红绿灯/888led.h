#ifndef __888led_H__
#define __888led_H__

//扫描函数（放定时器里，2ms执行一次）
void Scan_888led(void);

//更改数码管要显示的值，第一个参数是位置，第二个参数是值//值0~9为数字，10为空白，11为"-"
void Set_888led(unsigned char Location,unsigned char Number);
	
#endif

