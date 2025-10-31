#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库

#include <4x4_16.H>

//标准的循环延迟（精确1ms）
void delay(unsigned char xms){
	unsigned char i, j;
	i = 2;
	j = 239;
	do{
	do{
		while (--j);
	} while (--i);
	} while (--xms);
}

//左闪
void ubit1(){
	P2_0=0;
	delay(3);
	P2_0=1;
	delay(3);
}
//右闪
void ubit2(){
	P2_1=0;
	delay(3);
	P2_1=1;
	delay(3);
}
//双闪
void ubit3(){
	P2_0=0;P2_1=0;
	delay(3);
	P2_0=1;P2_1=1;
	delay(3);
}

char num,ubit=0;
void main()
{
	while(1){
		num=button();
		
		//检测赋值系统
		if(num!=0){
			switch(num)
			{
				case 1: 
					if(ubit==1){ubit=0;break;}
					ubit=1; 
				break;
				case 2:
					if(ubit==2){ubit=0;break;}
					ubit=2; 
				break;
				case 3:
					if(ubit==3){ubit=0;break;}
					ubit=3;
				break;
			}
		}
		//判断赋值执行函数系统
		if(ubit==1){
			ubit1();
		}
		else{
		if(ubit==2){
			ubit2();
		}
		else{
		if(ubit==3){
			ubit3();
			}
		}
		}
	}
}

