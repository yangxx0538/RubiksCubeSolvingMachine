#ifndef _CTRL_H_
#define _CTRL_H_

#include "stm32f10x.h"

void Motor_Config(void);
void Basic_Move(uint8_t motor_dir);
void PLL_01(void);
void TestMotor(void);
void delay_out(void);
extern u8 frameHead;
extern uint8_t move_buffer[100];
extern u8 testCommand;
extern int start_Solving_flag;
extern char result_buffer[200];

//R1
#define R1_UP  0x01
#define R1_DOWN  0x02
#define R1_LEFT  0x03
#define R1_RIGHT  0x04

//L1
#define L1_DOWN  0x05
#define L1_UP  0x06
#define L1_LEFT  0x07
#define L1_RIGHT  0x08

//U1
#define U1_UP  0x09
#define U1_DOWN  0x0A
#define U1_RIGHT  0x0B
#define U1_LEFT  0x0C

//D1
#define D1_UP  0x0D
#define D1_DOWN  0x0E
#define D1_LEFT  0x0F
#define D1_RIGHT  0x10
		
//L1R1 together
#define L1R1_UP  0x12
#define L1R1_DOWN  0x11

#define L1_LEFT_R1_RIGHT  0x013
#define L1_RIGHT_R1_LEFT 0x14

//U1D1 together

#define U1D1_LEFT  0x16
#define U1D1_RIGHT  0x15

#define U1_UP_D1_DOWN  0x17
#define U1_DOWN_D1_UP 0x18
//Calibrate
#define ALL_Calib 0x19
#define ALL_Calib_IN 0x1A


//R
#define R do{	Basic_Move(R1_UP);		\
				Basic_Move(R1_RIGHT);	\
				Basic_Move(R1_DOWN);    \
				Basic_Move(R1_LEFT);}while(0)
//Rv means R'
#define Rv do{	Basic_Move(R1_DOWN);	\
				Basic_Move(R1_RIGHT);	\
				Basic_Move(R1_DOWN);    \
				Basic_Move(R1_LEFT);}while(0)
//R2
#define Rd do{	Basic_Move(R1_DOWN);	\
				Basic_Move(R1_DOWN);}while(0)
//U
#define U do{	Basic_Move(U1_LEFT);	\
				Basic_Move(U1_UP);		\
				Basic_Move(U1_RIGHT);	\
				Basic_Move(U1_DOWN);}while(0)

#define Uv do{	Basic_Move(U1_RIGHT);	\
				Basic_Move(U1_UP);		\
				Basic_Move(U1_LEFT);    \
				Basic_Move(U1_DOWN);}while(0)

#define Ud do{	Basic_Move(U1_RIGHT);	\
				Basic_Move(U1_RIGHT);}while(0)	
//F
#define F do{	Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_UP);			\
				Basic_Move(U1_DOWN_D1_UP);		\
				Basic_Move(U1_LEFT);			\
				Basic_Move(U1_UP);				\
				Basic_Move(U1_RIGHT);			\
				Basic_Move(U1_DOWN);			\
				Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_DOWN);			\
				Basic_Move(U1_DOWN_D1_UP);}while(0)			

				//C#

#define Fv do{	Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_UP);			\
				Basic_Move(U1_DOWN_D1_UP);		\
				Basic_Move(U1_RIGHT);			\
				Basic_Move(U1_UP);				\
				Basic_Move(U1_RIGHT);			\
				Basic_Move(U1_DOWN);			\
				Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);			\
				Basic_Move(L1R1_DOWN);			\
				Basic_Move(U1_DOWN_D1_UP);}while(0)	
	
#define Fd do{	Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_UP);			\
				Basic_Move(U1_DOWN_D1_UP);		\
				Basic_Move(U1_LEFT);			\
				Basic_Move(U1_LEFT);			\
												\
				Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);			\
				Basic_Move(L1R1_DOWN);			\
				Basic_Move(U1_DOWN_D1_UP);}while(0)					
//D
#define D do{	Basic_Move(D1_RIGHT);			\
				Basic_Move(D1_DOWN);			\
				Basic_Move(D1_RIGHT);			\
				Basic_Move(D1_UP);				\
										}while(0)

//Dv
#define Dv do{	Basic_Move(D1_LEFT);			\
				Basic_Move(D1_DOWN);			\
				Basic_Move(D1_LEFT);			\
				Basic_Move(D1_UP);				\
				}while(0)

//D2
				
#define Dd do{	Basic_Move(D1_RIGHT);			\
				Basic_Move(D1_RIGHT);			}while(0)

//L
#define L do{	Basic_Move(L1_DOWN);			\
				Basic_Move(L1_LEFT);			\
				Basic_Move(L1_UP);              \
				Basic_Move(L1_RIGHT);}while(0)
//L'
#define Lv do{	Basic_Move(L1_UP);				\
				Basic_Move(L1_LEFT);			\
				Basic_Move(L1_DOWN);            \
				Basic_Move(L1_RIGHT);}while(0)
//L2
#define Ld do{	Basic_Move(L1_UP);				\
				Basic_Move(L1_UP);}while(0)
								

#define B do{	Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_DOWN);			\
				Basic_Move(U1_DOWN_D1_UP);		\
				Basic_Move(U1_LEFT);			\
				Basic_Move(U1_UP);				\
				Basic_Move(U1_RIGHT);			\
				Basic_Move(U1_DOWN);			\
				Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_UP);			\
				Basic_Move(U1_DOWN_D1_UP);}while(0)	

				
#define Bv do{	Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_DOWN);			\
				Basic_Move(U1_DOWN_D1_UP);		\
												\
				Basic_Move(U1_RIGHT);			\
				Basic_Move(U1_UP);				\
				Basic_Move(U1_LEFT);			\
				Basic_Move(U1_DOWN);			\
				Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_UP);			\
				Basic_Move(U1_DOWN_D1_UP);}while(0)	

#define Bd do{	Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_DOWN);			\
				Basic_Move(U1_DOWN_D1_UP);		\
												\
				Basic_Move(U1_RIGHT);			\
				Basic_Move(U1_RIGHT);			\
												\
				Basic_Move(L1_LEFT_R1_RIGHT);	\
				Basic_Move(L1R1_UP);			\
				Basic_Move(L1_RIGHT_R1_LEFT);	\
				Basic_Move(U1_UP_D1_DOWN);		\
				Basic_Move(L1R1_UP);			\
				Basic_Move(U1_DOWN_D1_UP);}while(0)	

#define rotateFace1_front 							\
				do{									\
					Basic_Move(L1_LEFT_R1_RIGHT);	\
					Basic_Move(L1R1_UP);			\
					Basic_Move(L1_RIGHT_R1_LEFT);	\
					Basic_Move(U1_UP_D1_DOWN);		\
				  }while(0)	
#define rotateFace2_4_front 						\
				do{									\
					Basic_Move(L1R1_UP);			\
					Basic_Move(U1_DOWN_D1_UP);		\
					Basic_Move(L1_LEFT_R1_RIGHT);	\
					Basic_Move(L1R1_DOWN);			\
					Basic_Move(L1_RIGHT_R1_LEFT);	\
					Basic_Move(U1_UP_D1_DOWN);		\
				  }while(0)	

#define rotateFace5_side 						    \
				do{									\
					Basic_Move(L1R1_UP);			\
					Basic_Move(U1_DOWN_D1_UP);		\
					Basic_Move(L1_LEFT_R1_RIGHT);	\
					Basic_Move(U1D1_RIGHT);			\
				  }while(0)					  
#define rotateFace6_side 						    \
				do{									\
					Basic_Move(U1D1_LEFT);			\
					Basic_Move(U1D1_LEFT);			\
				  }while(0)					  
#define rotateOver 						    		\
				do{									\
					Basic_Move(U1D1_RIGHT);			\
					Basic_Move(L1_RIGHT_R1_LEFT);	\
				  }while(0)				  
#endif



