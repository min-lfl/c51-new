#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

//XPT2046引脚定义
sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;

#define Precision 0x00
//#define Precision 0x08 //精度开关，取消这行注释精度变为8位，值为0-255，默认为12位精度，0-4096

#define AIN0 0x94|Precision //引脚0，默认精度12位
#define AIN1 0xD4|Precision	//引脚1，默认精度12位
#define AIN2 0xA4|Precision	//引脚2，默认精度12位
#define AIN3 0xE4|Precision	//引脚3，默认精度12位

unsigned int XPT2046_Read(unsigned char Byte){
	unsigned int num_int=0; //定义返回值
	unsigned char i,Code; //定义i和引脚选中
	
	switch (Byte) {
    case 1:           //选中引脚1
        Code=AIN0;
        break;
    case 2:           //选中引脚2
        Code=AIN1;
        break;
    case 3:           //选中引脚3
        Code=AIN2;
        break;
		case 4:           //选中引脚4
        Code=AIN3;
        break;
    default:
        return 1;
        break;
}
	XPT2046_DCLK=0;
	XPT2046_CS=0;
	
	for(i=0;i<8;i++){
		XPT2046_DIN = (Code & (0x80 >> i)) ? 1 : 0; 
		XPT2046_DCLK = 1; // 上升沿锁存数据
    _nop_();
    XPT2046_DCLK = 0;
    _nop_();
	}
//	XPT2046_DCLK=0; //拉低，准备给下降沿时接收
//	XPT2046_DIN=0;
//	XPT2046_DIN=0;
	
//	for(i=6; i>0; i--); 	//延时等待转换结果
//	XPT2046_DCLK = 1;	  //发送一个时钟周期，清除BUSY
//	_nop_();
//	_nop_();
//	XPT2046_DCLK = 0;
//	_nop_();
//	_nop_();
//	XPT2046_DCLK = 0;
	// 延时等待转换完成
	for(i = 6; i > 0; i--); 

	// 清除BUSY标志并准备读取
	XPT2046_DCLK = 1;
	_nop_();
	_nop_();
	_nop_();
	XPT2046_DCLK = 0;
	_nop_();
	_nop_();
	_nop_();
	// 正确读取12位数据（高位在先）
	num_int = 0;
	for(i=0;i<12;i++){
//		num_int <<= 1;
//		XPT2046_DCLK=1;
//		XPT2046_DCLK=0;
////		if(XPT2046_DOUT){num_int=num_int|(0x8000>>i);}
//		num_int|= XPT2046_DOUT;
		num_int <<= 1;         // 先将已读取的数据左移一位
    XPT2046_DCLK = 1;
    XPT2046_DCLK = 0;      // 下降沿后数据有效
    if(XPT2046_DOUT) {
        num_int |= 0x01;   // 将最低位置1
    }
	}
	XPT2046_CS = 1; // 关闭芯片

	// 根据精度选择返回值
	if(Precision & 0x08) { // 8位精度
    return num_int+1024;     // 12位数据右移4位后得到8位数据
	} else {               // 12位精度
    return num_int+1024;
	}
}


//////---包含头文件---//
////#include<reg52.h>
////#include<intrins.h>
//////---重定义关键词---//
////#ifndef uchar
////#define uchar unsigned char
////#endif

////#ifndef uint
////#define uint  unsigned int
////#endif

////#ifndef ulong
////#define ulong  unsigned long
////#endif
//////---定义使用的IO口---//
////sbit DOUT = P3^7;	  //输出
////sbit CLK  = P3^6;	  //时钟
////sbit DIN  = P3^4;	  //输入
////sbit CS   = P3^5;	  //片选

/////****************************************************************************
////*函数名：SPI_Write
////*输  入：dat：写入数据
////*输  出：无
////*功  能：使用SPI写入数据
////****************************************************************************/

////void SPI_Write(uchar dat)
////{
////	uchar i;
////	CLK = 0;
////	for(i=0; i<8; i++)
////	{
////		DIN = dat >> 7;  	//放置最高位
////		dat <<= 1;
////		CLK = 0;			//上升沿放置数据

////		CLK = 1;

////	}
////}
/////****************************************************************************
////*函数名：SPI_Read
////*输  入：无
////*输  出：dat：读取 到的数据
////*功  能：使用SPI读取数据
////****************************************************************************/

////uint SPI_Read(void)
////{
////	uint i, dat=0;
////	CLK = 0;
////	for(i=0; i<12; i++)		//接收12位数据
////	{
////		dat <<= 1;

////		CLK = 1;
////		CLK = 0;

////		dat |= DOUT;

////	}
////	return dat;	
////}

/////****************************************************************************
////*函数名：Read_AD_Data
////*输  入：cmd：读取的X或者Y
////*输  出：endValue：最终信号处理后返回的值
////*功  能：读取触摸数据
////****************************************************************************/
////unsigned int Read_AD_Data(unsigned  char cmd)
////{
////	uchar i;
////	uint AD_Value;
////	CLK = 0;
////	CS  = 0;
////	SPI_Write(cmd);
////	for(i=6; i>0; i--); 	//延时等待转换结果
////	CLK = 1;	  //发送一个时钟周期，清除BUSY
////	_nop_();
////	_nop_();
////	CLK = 0;
////	_nop_();
////	_nop_();
////	AD_Value=SPI_Read();
////	CS = 1;
////	return AD_Value;	
////}


//#include <REGX52.H>
//#include <INTRINS.H>

//sbit XPT2046_CS = P3^5;
//sbit XPT2046_DCLK = P3^6;
//sbit XPT2046_DIN = P3^4;
//sbit XPT2046_DOUT = P3^7;

//#define Precision 0x00

//#define AIN0 0x94 | Precision
//#define AIN1 0xD4 | Precision
//#define AIN2 0xA4 | Precision
//#define AIN3 0xE4 | Precision

//// 首先，优化SPI写入函数，用于发送命令字
//void XPT2046_SPIWrite(unsigned char dat) {
//    unsigned char i;
//    XPT2046_DCLK = 0;
//    for(i = 0; i < 8; i++) {
//        XPT2046_DIN = dat & 0x80; // 取最高位
//        dat <<= 1;                // 左移，准备发送下一位
//        XPT2046_DCLK = 1;         // 上升沿发送数据
//        XPT2046_DCLK = 0;
//    }
//}

//// 其次，优化SPI读取函数，专门读取12位数据
//unsigned int XPT2046_SPIRead(void) {
//    unsigned int i, dat = 0;
//    XPT2046_DCLK = 0;
//    for(i = 0; i < 12; i++) { // 循环12次，读取12位有效数据
//        dat <<= 1;            // 数据左移，为新位腾出空间
//        XPT2046_DCLK = 1;
//        XPT2046_DCLK = 0;     // 下降沿读取数据
//        if(XPT2046_DOUT) {
//            dat |= 0x01;      // 如果DOUT为高，则将最低位置1
//        }
//    }
//    return dat;
//}

//// 主读取函数
//unsigned int XPT2046_Read(unsigned char Byte) {
//    unsigned int AD_Value = 0;
//    unsigned char Code;

//    switch (Byte) {
//        case 1: Code = AIN0; break;
//        case 2: Code = AIN1; break;
//        case 3: Code = AIN2; break;
//        case 4: Code = AIN3; break;
//        default: return 0xFFFF; // 错误通道处理
//    }

//    XPT2046_DCLK = 0;
//    XPT2046_CS = 0;  // 使能芯片

//    XPT2046_SPIWrite(Code); // 发送控制命令

//    // 增加的关键步骤：延时并清除BUSY状态[4](@ref)
//    {
//        unsigned char i;
//        for(i=6; i>0; i--);  // 短暂延时，等待转换完成
//        XPT2046_DCLK = 1;    // 产生一个时钟周期，清除BUSY
//        _nop_();
//        _nop_();
//        XPT2046_DCLK = 0;
//        _nop_();
//        _nop_();
//    }

//    AD_Value = XPT2046_SPIRead(); // 读取12位AD值

//    XPT2046_CS = 1; // 禁用芯片

//    // 根据精度选择返回值
//    if(Precision & 0x08) { // 8位模式
//        return AD_Value >> 4; // 12位数据右移4位得到8位
//    } else {                // 12位模式
//        return AD_Value;     // 直接返回12位数据
//    }
//}
