#include <REGX52.H> //c52库
#include <DELAY.H>

sbit SER=P3^4; //数据暂放区
sbit SCK=P3^6;  //上升沿移位
sbit RCK=P3^5;  //上升沿输出

/**
	* @brief		74HC595芯片驱动程序，输入一个字节，会把字节输出到纵坐标上，类比P0=0xaa;语句的作用
	* @param		要输出到纵坐标上的字节
	* @retval		无
	*/
void _74HC595_WriteByte(unsigned char Byte){
	unsigned char i;
	for(i=0;i<8;i++){
		SER=Byte&(0x80>>i);
		SCK=0;SCK=1;//控制SCK输出一个信号上升沿
	}
	RCK=0;RCK=1;	//控制RCK输出一个信号上升沿
}

/**
	* @brief		接受第几列和一个字节，会在那一列上显示字节图像1为亮0为灭，此函数要在主函数内快速扫描
	* @param1		第几列
	* @param2		要显示的字节
	* @retval		无返回值
	*/
void MatrixLED_ShowColumn(unsigned char num,unsigned char date){

	_74HC595_WriteByte(date);//给纵坐标一个输入，当列被选中，横坐标位置为1时，灯亮起
	P0=~(0x80>>num); //给横坐标一个输入选中哪一列
	delay(1);
	P0=0xff; //消除残影
}


/**
	* @brief		这个是一个快速实现8x8动态显示的封装函数
	* @param1		接受一个数组变量，数组内容可以用取模器直接生成，列扫描
	* @param2		接受一个数组长度，必须诚实填写数组的长度
  * @param3	  接受一个1~500的参数，控制字幕速度，速度值越小越快,小于<50>时为流动显示，大于<50>时为翻页逐帧显示，等于<0>时为静态显示，8个数组为1帧
	* @retval		无返回值
	*/
void MatrixLED_Roll(unsigned char arr[],unsigned int len,unsigned char speed){
	unsigned char i, add;           // 普通局部变量
  static unsigned char a = 0;      // 静态变量：保持滚动位置
  static unsigned char num = 0;    // 静态变量：保持计数状态
	if(speed>=50){add=8;}else{if(speed==0){add=0;}else{add=1;}} //判断要滚动还是翻页还是静态
	for(i=0;i<8;i++){  //刷新一次屏幕
		MatrixLED_ShowColumn(i,arr[(a+i)%len]);
	}
	num++;
	if(num>=speed){
		a+=add;
		num=0;
		if(a>=(len)){
			a=0;
		}
	}
}
	



