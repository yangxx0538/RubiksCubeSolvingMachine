#ifndef __SYS_PARAM_H
#define __SYS_PARAM_H

#include "stm32f10x.h"
extern u16 PWM_UP,PWM_DOWN,PWM_LEFT,PWM_RIGHT;
extern float Kp,Kd;
extern float Kp_gryo,Kd_gryo;
extern u8 Sys_Mode;
extern float Target_Length;
extern int Target_Degree;
extern u16 task_count;
extern int Hover_Target_Pitch;
extern int Hover_Target_Roll;
extern float PWM_X_Angle ,PWM_Y_Angle;
extern u8 Calibrate_flag;
extern float Target_SpecAng_Pitch;
extern float Target_SpecAng_Roll;
extern u8 Posi_count;
extern float Actual_Degree;
extern float Target_Radius_A;
extern float Target_Radius_B;
extern float Target_SpecAng_X;
extern float Target_SpecAng_Y;
extern u8 Posi_flag;
extern float Target_Radius;


extern u8 Posi_flag_Y_Pre ;

extern u8 Posi_flag_X_Pre ;
#define  led1_on    GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define  led1_off   GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define  led2_on    GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define  led2_off   GPIO_SetBits(GPIOB, GPIO_Pin_14)
 
 
#define PI 3.141592653589
typedef enum
{
	No_Action = 0,
	Free_fall = 1,		//松手后保持静止
	DrawLine_no_Degree = 2,
	DrawLine_with_Degree = 3,
	Draw_Circle = 4,
	Hover = 5,
	Free_Swing = 6,

	
}Mode_e;




#endif










