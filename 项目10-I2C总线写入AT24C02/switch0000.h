#ifndef __SWITCH0000_H__
#define __SWITCH0000_H__

//使用方法:把Scan_key();函数放入定时器中，20ms执行一次，它会不断扫描哪个按键按下把键值存入全局变量
//再到主函数循环中通过switch0000()函数接收键值


/**
	* @brief  获取独立按键键码
	* @param   无
	* @retval  按下的第几个键，范围0~4，无按键按下时返回值为0
	*/
unsigned char switch0000();


/**
	* @brief  放入定时器中不断扫描按键，建议20ms执行一次
	* @param   无
	* @retval  无
	*/
void Scan_key();
#endif