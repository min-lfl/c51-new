#include <REGX52.H> //c52库
#include <INTRINS.H> //标准变量库
#include <string.h>//字符串链接库

#include <delay.h>
#include <888led.h>
#include <LCD1602.H>
#include <4x4_16.h>


char keynum,num[7]="";
char password[]="197811",i;
void main(){
	LCD_Init();//初始化
	
	while(1){
		LCD_ShowString(1,1,"PassWord:");
		keynum=button();
		//检测是否有输入
		if(keynum!=0){
			//当输入的是密码时
			if(keynum<=10){
				int len = strlen(num);
				if(len<6){
					num[len] = keynum + '0'; 
					num[len+1] = '\0';
				}
				LCD_ShowString(2,1,"                   ");
				LCD_ShowString(2,1,num);
			}
			//按取消键时
			if(keynum==11){
				LCD_ShowString(2,1,"                   ");
				num[0] = '\0';
			}
			//按确认键时，输出结果
			if(keynum==12){
				if(strcmp(password,num) == 0){
					LCD_ShowString(2,1,"True passwd ^_^");
					num[0] = '\0';
				}
				else{
					LCD_ShowString(2,1,"False passwd X");
					num[0] = '\0';
				}
			}
		}
	}
}