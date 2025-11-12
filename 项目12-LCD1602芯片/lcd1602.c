#include <REGX52.H>
#include <INTRINS.H>
#include <DELAY.H>

sbit LCD1602_RD=P2^6;
sbit LCD1602_RW=P2^5;
sbit CE=P2^7;

#define LCD_DATE P0

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


void Read_LCD1602_RS(unsigned char Byte){
	LCD1602_RD=0;
	LCD1602_RW=0;
	Delay1ms();
	LCD_DATE=Byte;
	CE=1;
	Delay1ms();
	CE=0;
}


void Read_LCD1602_Date(unsigned char Byte){
	LCD1602_RD=1;
	LCD1602_RW=0;
	Delay1ms();
	LCD_DATE=Byte;
	CE=1;
	Delay1ms();
	CE=0;
}

void LCD_Init(){
	Read_LCD1602_RS(0x38);
	Read_LCD1602_RS(0x0c);
	Read_LCD1602_RS(0x06);
	Read_LCD1602_RS(0x01);
}

void LCD_ShowChar(unsigned char Line,unsigned char Column,char *Char){
	char i;
	Read_LCD1602_RS(0x80|(Line-1)+(Column-1));
	for(i=0;Char[i]!='\0';i++){
		Read_LCD1602_Date(Char[i]);
	}
}

void LCD_zuo(){
	Read_LCD1602_RS(0x08);
	delay(400);
	Read_LCD1602_RS(0x18);
	Read_LCD1602_RS(0x0c);

}