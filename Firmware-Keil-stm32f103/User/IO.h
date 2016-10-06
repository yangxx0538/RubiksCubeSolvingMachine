#ifndef _IO_H
#define _IO_H

#include "stm32f10x.h"

#define nil 0
#define U1 	1
#define U2  2
#define D1  3
#define D2  4
#define L1  5
#define L2  6 
#define R1  7
#define R2  8

#define CW  1  //clockwise
#define ACW  2  //anticlockwise
#define UP  3
#define DOWN  4
#define LEFT  5
#define RIGHT  6


#define D2_IO_STEP GPIOC
#define D2_STEP GPIO_Pin_9
#define D2_IO_DIR GPIOA
#define D2_DIR GPIO_Pin_8

#define U2_IO_STEP GPIOE
#define U2_STEP GPIO_Pin_12
#define U2_IO_DIR GPIOE
#define U2_DIR GPIO_Pin_11

#define L2_IO_STEP GPIOD
#define L2_STEP GPIO_Pin_14
#define L2_IO_DIR GPIOD
#define L2_DIR GPIO_Pin_15

#define R2_IO_STEP GPIOB
#define R2_STEP GPIO_Pin_2
#define R2_IO_DIR GPIOE
#define R2_DIR GPIO_Pin_7

/*
	 -----------------------------
	|							  |
	|			  U2              |
	|                             |
	|		      U1              |
	|                             |
	|	L2   L1        R1   R2	  |
	|                             |
	|			  D1              |
	|                             |
	|		      D2              | 
	|			                  |
	|			                  |
	 -----------------------------
*/



#define D1_IO_STEP GPIOB
#define D1_IO_DIR GPIOB
#define D1_STEP GPIO_Pin_12
#define D1_DIR GPIO_Pin_13
#define D1_nextMoveUp   GPIO_ResetBits( D2_IO_DIR , D2_DIR )
#define D1_nextMoveDown GPIO_SetBits( D2_IO_DIR , D2_DIR )



#define U1_IO_DIR GPIOD
#define U1_DIR GPIO_Pin_10
#define U1_IO_STEP GPIOD
#define U1_STEP GPIO_Pin_9
#define U1_nextMoveUp   GPIO_ResetBits( U2_IO_DIR , U2_DIR )
#define U1_nextMoveDown GPIO_SetBits( U2_IO_DIR , U2_DIR )


#define L1_IO_STEP GPIOD
#define L1_STEP GPIO_Pin_4
#define L1_IO_DIR GPIOD
#define L1_DIR GPIO_Pin_3
#define L1_nextMoveRight   GPIO_ResetBits( L2_IO_DIR , L2_DIR )
#define L1_nextMoveLeft GPIO_SetBits( L2_IO_DIR , L2_DIR )


#define R1_IO_STEP GPIOB
#define R1_IO_DIR GPIOB
#define R1_STEP GPIO_Pin_10
#define R1_DIR GPIO_Pin_11
#define R1_nextMoveRight   GPIO_SetBits( R2_IO_DIR , R2_DIR )
#define R1_nextMoveLeft GPIO_ResetBits( R2_IO_DIR , R2_DIR )




#endif





