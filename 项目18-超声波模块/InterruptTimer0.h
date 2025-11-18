#ifndef __InterruptTimer0_H__
#define __InterruptTimer0_H__

void InterruptTimer2_init();

void set_InterruptTimer(unsigned int Time);

void run_InterruptTimer(unsigned char Code);

unsigned int read_InterruptTimer();

#endif