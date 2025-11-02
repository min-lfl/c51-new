#ifndef __8X8_H__
#define __8X8_H__

/*
MatrixLED_ShowColumn(1,0xfe); //显示在第几列，那一列显示哪个字节
MatrixLED_Roll(arr,48,50);  //<数组名字>，<数组长度>，<0为静态，1~50为滚动，50~500为翻页>
*/

void MatrixLED_ShowColumn(unsigned char num,date);  //精细自定义显示，输入接受第几列和一个字节，会在那一列上显示字节图像1为亮0为灭，此函数要在主函数内快速扫描
void MatrixLED_Roll(unsigned char arr[],unsigned int len,unsigned char speed); //这个是一个快速实现8x8动态显示的封装函数
	
#endif