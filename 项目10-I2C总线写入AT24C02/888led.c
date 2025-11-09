#include <REGX52.H> //c52库

//全局变量存储八个数码管的状态，主函数里改变全局变量，扫描函数里读取全局变量刷新到数码管
unsigned char code_888led[]={10,10,10,10,10,10,10,10};


/**
	* @brief		传入位置和数字，在位置上显示数字//0~9每个码代表一个数字,10代表空白
	* @param		要显示的位置，1~8
	* @param		要显示的数字0~9，10为空白
	* @retval		无
	*/
unsigned char code leddata[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40};
void Nixie(unsigned char Location,Number){
	
	switch(Location)
	{
		case 1: P2_2=1; P2_3=1; P2_4=1; break;
    case 2: P2_2=0; P2_3=1; P2_4=1; break;
    case 3: P2_2=1; P2_3=0; P2_4=1; break;
    case 4: P2_2=0; P2_3=0; P2_4=1; break;
    case 5: P2_2=1; P2_3=1; P2_4=0; break;
    case 6: P2_2=0; P2_3=1; P2_4=0; break;
    case 7: P2_2=1; P2_3=0; P2_4=0; break;
    case 8: P2_2=0; P2_3=0; P2_4=0; break;
	}
	P0=leddata[Number];
}


/**
 * @brief  数码管扫描显示函数
 * @param  无
 * @retval 无
 * @note   定时器每2ms调用一次，实现多位数码管的动态显示
 *         自动跳过值为10的位置（不显示），避免显示亮度不均
 *         显示密度自适应：数字多时整体偏暗，数字少时整体偏亮，但亮度均匀
 */
void Scan_888led(){
	static unsigned char number=0,i=0;//number为自加值，i为超时判定
	P0=0x00;//消除残影（虽然不太理解）
	
	// 跳过不显示的位置（值为10），最多查找8次避免死循环
	while(code_888led[number]==10 && i<8){
		number = (number + 1) % 8;
		i++;
	}i=0;//把i归0
	
	
	Nixie((number+1),code_888led[number]);//在对应位置显示对应数据
  number = (number + 1) % 8; //更新到下一个位置，让number循环在0~7
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