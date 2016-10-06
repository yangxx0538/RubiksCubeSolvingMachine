#ifndef _DELAY__H_
#define _DELAY__H_

#include "stm32f10x.h"


void Delay1ms(void);

void delay_ms(u32 n);

void Delay(u32 time);

void delay_init(void);

void delay_us(u32 nus);


#endif
