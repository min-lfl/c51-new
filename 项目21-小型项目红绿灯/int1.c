#include <REGX52.H>

void Int1_Init()
{
    IT1 = 1;   // 设置为边沿触发方式
    EX1 = 1;   // 使能外部中断1
    EA  = 1;   // 全局中断使能
}
