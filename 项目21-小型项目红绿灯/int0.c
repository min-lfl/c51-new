#include <REGX52.H>

void Int0_Init()
{
    IT0 = 1;   // 设置为边沿触发方式
    EX0 = 1;   // 使能外部中断0
    EA  = 1;   // 全局中断使能
}
