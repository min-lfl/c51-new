#include <REGX52.H> //c52库
#include <delay.h>

//全局变量存储2个数码管的状态，主函数里改变全局变量，扫描函数里读取全局变量刷新到数码管
unsigned char code_888led[]={10,10};

//共阴极数码管段码表，0~9为数字，10为空白，11为"-"
unsigned char code leddata[]={
0xc0,//0
0xf9,//1
0xa4,//2
0xb0,//3
0x99,//4
0x92,//5
0x82,//6
0xf8,//7
0x80,//8
0x90,//9
0xff, //空
~0x40};

/**
	* @brief		传入位置和数字，在位置上显示数字//0~9每个码代表一个数字,10代表空白
	* @param		要显示的位置，1~2
	* @param		要显示的数字0~9，10为空白
	* @retval		无
	*/
void Nixie(unsigned char Location,unsigned char Number){
	P0=0xff;//消除残影
	switch(Location)
	{
		case 1: P2_0=1; P2_1=0;  break;
    	case 2: P2_0=0; P2_1=1;  break;
	}
	
	P0=leddata[Number];
}


/**
 * @brief  数码管扫描显示函数
 * @param  无
 * @retval 无
 * @note   定时器每2ms调用一次，实现多位数码管的动态显示
 *         支持1~2位数码管显示
 */
void Scan_888led(void){
	static unsigned char number=0;//number为自加值，i为超时判定
	P0=0xff;//消除残影
	
	Nixie((number+1),code_888led[number]);//在对应位置显示对应数据

  	number = (number + 1) % 2; //更新到下一个位置，让number循环在0~1
}


/**
	* @brief		改变某个位置的数字
	* @param		要改变的位置
	* @param		要改成的数字
	* @retval		无
	*/
void Set_888led(unsigned char Location,Number){
	code_888led[(Location-1)]=Number;
}