#include <REGX52.H>
#include <INTRINS.H>

#include <LCD1602.H>
#include "IRremote.h" 
#include <DELAY.H>

unsigned char key;
unsigned char last_key = 0;

void main(){
	LCD_Init();
	IR_Init();

	while(1) {
        key = IR_GetKey();

        if(key != 0 && key != last_key) { // 检测到新按键按下 (非重复)
            LCD_ShowHexNum(2,1,key,2); // 显示按键值 (如果用了LCD)
        }
        last_key = key; // 更新上一次按键值

        Delay_ms(20); // 主循环可以适当延时
    }
}