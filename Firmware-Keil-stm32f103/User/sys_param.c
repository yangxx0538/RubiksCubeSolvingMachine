
#include "sys_param.h"


u16 PWM_UP = 0,PWM_DOWN = 0,PWM_LEFT = 0,PWM_RIGHT = 0;

float Kp = 0.02,Kd = 0.02;

float Kp_gryo = 0.4,Kd_gryo = 500;

float PWM_X_Angle = 0,PWM_Y_Angle = 0;
u8 Sys_Mode = No_Action;
int Target_Degree;
float Target_Length;
float Target_SpecAng_Pitch;
float Target_SpecAng_Roll;

float Target_SpecAng_X;
float Target_SpecAng_Y;

float Target_Radius;

float Target_Radius_A;
float Target_Radius_B;
float Actual_Degree;
int Hover_Target_Pitch;
int Hover_Target_Roll;
u8 Calibrate_flag;
u16 task_count = 0;







