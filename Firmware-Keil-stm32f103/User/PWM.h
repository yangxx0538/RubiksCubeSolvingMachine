#include <stm32f10x.h>
#ifndef _PWM_H
#define _PWM_H

extern u32 PWM1_Time,PWM2_Time,PWM3_Time,PWM4_Time,
			PWM5_Time,PWM6_Time,PWM7_Time,PWM8_Time;
void Motor_Init(void);
void Motor_Set(u16,u16,u16,u16);
void Motor_Set1(u16);
void Motor_Set2(u16);
void Motor_Set3(u16);
void Motor_Set4(u16);
void PWMOUT1_Init(void);
void PWMIN1_Init(void);
void PWMIN2_Init(void);

void Motor_Set_X(u16 m1,u16 m2);
void Motor_Set_Y(u16 m1,u16 m2);
#endif
