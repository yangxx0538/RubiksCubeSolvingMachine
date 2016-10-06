#ifndef _TIME_H_
#define _TIME_H_

#include "stm32f10x.h"


void TIM2_IRQ(void);
void SYSTICK_INIT(void);

uint32_t GET_NOWTIME(uint32_t * lasttime);
void get_ms(unsigned long  *time);



#endif

