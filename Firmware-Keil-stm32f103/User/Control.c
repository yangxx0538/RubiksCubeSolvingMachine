/**
  ******************************************************************************
  * @file    Control.c 
  * @author  yangxx
  * @date    8/14/2016
  * @brief   move of stepmotor
  ******************************************************************************
  */
#include "IO.h"
#include "Control.h"
#include "delay.h"

uint8_t move_buffer[100];

void Delay500us(void)
{
    u32 a=4000;
    while(a--);
    
}
void Delay250us(void)
{
    u32 a=2000;
    while(a--);
    
}
void Delay200us(void)
{
    u32 a=1500;
    while(a--);
    
}
void delay_out(void)
{
	Delay500us();
//	Delay200us();
//	Delay200us();
	
//	Delay500us();
    Delay200us();
}
void delay_rotate(void)
{
	Delay500us();
	Delay500us();
//	Delay500us();
//	Delay250us();
    Delay500us();
}

void Motor_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);   

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);   



	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10 |GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);   
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	//限位开关
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//	GPIO_ResetBits(D1_IO, D1_DIR);
//	GPIO_ResetBits(D2_IO, D2_DIR);
//	
//	GPIO_ResetBits(R1_IO, R1_DIR);
//	GPIO_ResetBits(R2_IO, R2_DIR);
//	
//	GPIO_ResetBits(L1_IO, L1_DIR);
//	GPIO_ResetBits(L2_IO, L2_DIR);
//	
//	GPIO_ResetBits(U1_IO, U1_DIR);
//	GPIO_ResetBits(U2_IO, U2_DIR);
//	
//	GPIO_ResetBits(L1_IO, L1_STEP);
//	GPIO_ResetBits(L2_IO, L2_STEP);
//	GPIO_ResetBits(U1_IO, U1_STEP);
//	GPIO_ResetBits(U2_IO, U2_STEP);
//	GPIO_ResetBits(R1_IO, R1_STEP);
//	GPIO_ResetBits(R2_IO, R2_STEP);
//	GPIO_ResetBits(D1_IO, D1_STEP);
//	GPIO_ResetBits(D2_IO, D2_STEP);
	
}



/*

	主电机角度定义：90度：塑料爪小的对着正面 180度：大的面对着正面
	
	默认上电初始状态为四个主电机均为90度

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


void Basic_Move(uint8_t motor_dir)
{
	uint16_t i;
	switch (motor_dir)
	{

		case U1_LEFT:
			GPIO_SetBits( U1_IO_DIR , U1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
				GPIO_SetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
			}
			break;
		case U1_RIGHT:
			GPIO_ResetBits( U1_IO_DIR , U1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
				GPIO_SetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
			}
			break;
		case U1_UP:
			U1_nextMoveUp;
			for( i=0 ; i< 215 ; i++ )
			{
				GPIO_ResetBits( U2_IO_STEP , U2_STEP );
				delay_out();
				GPIO_SetBits( U2_IO_STEP , U2_STEP );
				delay_out();
			}
			
			break;
		case U1_DOWN:
			U1_nextMoveDown;
			for( i=0 ; i< 215 ; i++ )
			{
				GPIO_ResetBits( U2_IO_STEP , U2_STEP );
				delay_out();
				GPIO_SetBits( U2_IO_STEP , U2_STEP );
				delay_out();
			}
			break;

		
		case D1_RIGHT:
			GPIO_ResetBits( D1_IO_DIR , D1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( D1_IO_STEP , D1_STEP );
				delay_rotate();
				GPIO_SetBits( D1_IO_STEP , D1_STEP );
				delay_rotate();
			}
			break;
		case D1_LEFT:
			GPIO_SetBits( D1_IO_DIR , D1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( D1_IO_STEP , D1_STEP );
				delay_rotate();
				GPIO_SetBits( D1_IO_STEP , D1_STEP );
				delay_rotate();
			}
			break;
		case D1_UP:
			D1_nextMoveUp;
			for( i=0 ; i< 215 ; i++ )
			{
				GPIO_ResetBits( D2_IO_STEP , D2_STEP );
				delay_out();
				GPIO_SetBits( D2_IO_STEP , D2_STEP );
				delay_out();
			}
			
			break;
		case D1_DOWN:
			D1_nextMoveDown;
			for( i=0 ; i< 215 ; i++ )
			{
				GPIO_ResetBits( D2_IO_STEP , D2_STEP );
				delay_out();
				GPIO_SetBits( D2_IO_STEP , D2_STEP );
				delay_out();
			}
			break;


		case L1_UP:
			GPIO_ResetBits( L1_IO_DIR , L1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
				GPIO_SetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
			}
			break;
		case L1_DOWN:
			GPIO_SetBits( L1_IO_DIR , L1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
				GPIO_SetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
			}
			break;
		case L1_LEFT:
			L1_nextMoveLeft;
			for( i=0 ; i< 230 ; i++ )
			{
				GPIO_ResetBits( L2_IO_STEP , L2_STEP );
				delay_out();
				GPIO_SetBits( L2_IO_STEP , L2_STEP );
				delay_out();
			}
			break;
		case L1_RIGHT:
			L1_nextMoveRight;
			for( i=0 ; i< 230 ; i++ )
			{
				GPIO_ResetBits( L2_IO_STEP , L2_STEP );
				delay_out();
				GPIO_SetBits( L2_IO_STEP , L2_STEP );
				delay_out();
			}
			break;




		case R1_UP:
			GPIO_ResetBits( R1_IO_DIR , R1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( R1_IO_STEP , R1_STEP );
				delay_rotate();
				GPIO_SetBits( R1_IO_STEP , R1_STEP );
				delay_rotate();
			}
			break;
		case R1_DOWN:
			GPIO_SetBits( R1_IO_DIR , R1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( R1_IO_STEP , R1_STEP );
				delay_rotate();
				GPIO_SetBits( R1_IO_STEP , R1_STEP );
				delay_rotate();
			}
			break;
		case R1_LEFT:
			R1_nextMoveLeft;
			for( i=0 ; i< 230 ; i++ )
			{
				GPIO_ResetBits( R2_IO_STEP , R2_STEP );
				delay_out();
				GPIO_SetBits( R2_IO_STEP , R2_STEP );
				delay_out();
			}
			break;
		case R1_RIGHT:
			R1_nextMoveRight;
			for( i=0 ; i< 230 ; i++ )
			{
				GPIO_ResetBits( R2_IO_STEP , R2_STEP );
				delay_out();
				GPIO_SetBits( R2_IO_STEP , R2_STEP );
				delay_out();
			}
			break;
		case L1R1_UP:
			GPIO_ResetBits( R1_IO_DIR , R1_DIR );
			GPIO_ResetBits( L1_IO_DIR , L1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( R1_IO_STEP , R1_STEP );
				GPIO_ResetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
				GPIO_SetBits( R1_IO_STEP , R1_STEP );
				GPIO_SetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
			}
			break;
		case L1R1_DOWN:
			GPIO_SetBits( R1_IO_DIR , R1_DIR );
			GPIO_SetBits( L1_IO_DIR , L1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( R1_IO_STEP , R1_STEP );
				GPIO_ResetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
				GPIO_SetBits( R1_IO_STEP , R1_STEP );
				GPIO_SetBits( L1_IO_STEP , L1_STEP );
				delay_rotate();
			}
			break;	
		case L1_LEFT_R1_RIGHT:
			L1_nextMoveLeft;
			R1_nextMoveRight;
			for( i=0 ; i< 230 ; i++ )
			{
				GPIO_ResetBits( L2_IO_STEP , L2_STEP );
				GPIO_ResetBits( R2_IO_STEP , R2_STEP );
				delay_out();
				GPIO_SetBits( L2_IO_STEP , L2_STEP );
				GPIO_SetBits( R2_IO_STEP , R2_STEP );
				delay_out();
			}
			break;	
		case L1_RIGHT_R1_LEFT:
			L1_nextMoveRight;
			R1_nextMoveLeft;
			for( i=0 ; i< 230 ; i++ )
			{
				GPIO_ResetBits( L2_IO_STEP , L2_STEP );
				GPIO_ResetBits( R2_IO_STEP , R2_STEP );
				delay_out();
				GPIO_SetBits( L2_IO_STEP , L2_STEP );
				GPIO_SetBits( R2_IO_STEP , R2_STEP );
				delay_out();
			}
			break;	
		case U1D1_LEFT:
			GPIO_SetBits( D1_IO_DIR , D1_DIR );
			GPIO_SetBits( U1_IO_DIR , U1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( D1_IO_STEP , D1_STEP );
				GPIO_ResetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
				GPIO_SetBits( D1_IO_STEP , D1_STEP );
				GPIO_SetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
			}	
			break;	
		case U1D1_RIGHT:
			GPIO_ResetBits( D1_IO_DIR , D1_DIR );
			GPIO_ResetBits( U1_IO_STEP , U1_DIR );
			for( i=0 ; i< 50 ; i++ )
			{
				GPIO_ResetBits( D1_IO_STEP , D1_STEP );
				GPIO_ResetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
				GPIO_SetBits( D1_IO_STEP , D1_STEP );
				GPIO_SetBits( U1_IO_STEP , U1_STEP );
				delay_rotate();
			}	
			break;	
		case U1_UP_D1_DOWN:
			U1_nextMoveUp;
			D1_nextMoveDown;
			for( i=0 ; i< 215 ; i++ )
			{
				GPIO_ResetBits( U2_IO_STEP , U2_STEP );
				GPIO_ResetBits( D2_IO_STEP , D2_STEP );
				delay_out();
				GPIO_SetBits( U2_IO_STEP , U2_STEP );
				GPIO_SetBits( D2_IO_STEP , D2_STEP );
				delay_out();
			}

			break;	
		case U1_DOWN_D1_UP:
			U1_nextMoveDown;
			D1_nextMoveUp;
			for( i=0 ; i< 215; i++ )
			{
				GPIO_ResetBits( U2_IO_STEP , U2_STEP );
				GPIO_ResetBits( D2_IO_STEP , D2_STEP );
				delay_out();
				GPIO_SetBits( U2_IO_STEP , U2_STEP );
				GPIO_SetBits( D2_IO_STEP , D2_STEP );
				delay_out();
			}

			break;	
			
		case ALL_Calib:
			U1_nextMoveUp;
			D1_nextMoveDown;
			L1_nextMoveLeft;
			R1_nextMoveRight;
			for( i=0 ; i< 500 ; i++ )
			{	
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1)	//D2
				{
					GPIO_ResetBits( D2_IO_STEP , D2_STEP );
				}
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1) //L2
				{
					GPIO_ResetBits( L2_IO_STEP , L2_STEP );
				}
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12) == 1)
				{
					GPIO_ResetBits( R2_IO_STEP , R2_STEP );
				}
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) == 1)
				{
					GPIO_ResetBits( U2_IO_STEP , U2_STEP );
				}
				
				
				
				
				delay_out();
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1)	//D2
				{
					GPIO_SetBits( D2_IO_STEP , D2_STEP );
				}
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1) //L2
				{
					GPIO_SetBits( L2_IO_STEP , L2_STEP );
				}
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12) == 1)
				{
					GPIO_SetBits( R2_IO_STEP , R2_STEP );
				}
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) == 1)
				{
					GPIO_SetBits( U2_IO_STEP , U2_STEP );
				}
				delay_out();
			}
			U1_nextMoveDown;
			D1_nextMoveUp;
			L1_nextMoveRight;
			R1_nextMoveLeft;
			for( i=0 ; i< 40 ; i++ )
			{
				GPIO_ResetBits( D2_IO_STEP , D2_STEP );
				GPIO_ResetBits( L2_IO_STEP , L2_STEP );
				GPIO_ResetBits( R2_IO_STEP , R2_STEP );
				GPIO_ResetBits( U2_IO_STEP , U2_STEP );		
				
				delay_out();
				GPIO_SetBits( D2_IO_STEP , D2_STEP );
				GPIO_SetBits( L2_IO_STEP , L2_STEP );
				GPIO_SetBits( R2_IO_STEP , R2_STEP );
				GPIO_SetBits( U2_IO_STEP , U2_STEP );

				delay_out();
			}
			

			break;	
		case ALL_Calib_IN:
			U1_nextMoveDown;
			D1_nextMoveUp;
			L1_nextMoveRight;
			R1_nextMoveLeft;
			for( i=0 ; i< 370 ; i++ )
			{
				GPIO_ResetBits( D2_IO_STEP , D2_STEP ); 
				delay_out();
				GPIO_SetBits( D2_IO_STEP , D2_STEP );
				delay_out();
			}
			for( i=0 ; i< 275 ; i++ )
			{
				GPIO_ResetBits( L2_IO_STEP , L2_STEP );
				
				delay_out();
				GPIO_SetBits( L2_IO_STEP , L2_STEP );
				
				delay_out();
			}
			for( i=0 ; i< 315 ; i++ )
			{
				
				GPIO_ResetBits( R2_IO_STEP , R2_STEP );
				delay_out();
				
				GPIO_SetBits( R2_IO_STEP , R2_STEP );
				delay_out();
			}
			for( i=0 ; i< 216 ; i++ )
			{
				GPIO_ResetBits( U2_IO_STEP , U2_STEP );
				delay_out();
				GPIO_SetBits( U2_IO_STEP , U2_STEP );
				delay_out();
			}
		
			
			
			
			
			break;	
		default:
			break;
	}
}
/*
void TestMotor()
{
	Basic_Move(R1_UP);		
	Basic_Move(R1_UP);
	Basic_Move(R1_UP);
	Basic_Move(R1_UP);
	Basic_Move(R1_UP);
	Basic_Move(R1_DOWN);		
	Basic_Move(R1_DOWN);
	Basic_Move(R1_DOWN);
	Basic_Move(R1_DOWN);
	Basic_Move(R1_DOWN);
	
	Basic_Move(L1_UP);		
	Basic_Move(L1_UP);
	Basic_Move(L1_UP);
	Basic_Move(L1_UP);
	Basic_Move(L1_UP);
	Basic_Move(L1_DOWN);		
	Basic_Move(L1_DOWN);
	Basic_Move(L1_DOWN);
	Basic_Move(L1_DOWN);
	Basic_Move(L1_DOWN);
	
	Basic_Move(U1_LEFT);		
	Basic_Move(U1_LEFT);
	Basic_Move(U1_LEFT);
	Basic_Move(U1_LEFT);
	Basic_Move(U1_LEFT);
	Basic_Move(U1_RIGHT);		
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_RIGHT);
	
	Basic_Move(D1_LEFT);		
	Basic_Move(D1_LEFT);
	Basic_Move(D1_LEFT);
	Basic_Move(D1_LEFT);
	Basic_Move(D1_LEFT);
	Basic_Move(D1_RIGHT);		
	Basic_Move(D1_RIGHT);
	Basic_Move(D1_RIGHT);
	Basic_Move(D1_RIGHT);
	Basic_Move(D1_RIGHT);
}



void PLL_01()
{
	
	//R
	Basic_Move(R1_UP);		
	Basic_Move(R1_RIGHT);	
	Basic_Move(R1_DOWN);
	Basic_Move(R1_LEFT);
	//U
	Basic_Move(U1_LEFT);
	Basic_Move(U1_UP);
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_DOWN);
	//R'
	Basic_Move(R1_DOWN);
	Basic_Move(R1_RIGHT);
	Basic_Move(R1_DOWN);
	Basic_Move(R1_LEFT);
	//U'
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_UP);
	Basic_Move(U1_LEFT);
	Basic_Move(U1_DOWN);
	//R'
	Basic_Move(R1_DOWN);
	Basic_Move(R1_RIGHT);
	Basic_Move(R1_DOWN);
	Basic_Move(R1_LEFT);
	
	//F
	Basic_Move(L1_LEFT_R1_RIGHT);	
	Basic_Move(L1R1_UP);
	Basic_Move(L1_RIGHT_R1_LEFT);	
	Basic_Move(U1_UP_D1_DOWN);
	Basic_Move(L1R1_UP);
	Basic_Move(U1_DOWN_D1_UP);
	Basic_Move(U1_LEFT);
	Basic_Move(U1_UP);
	Basic_Move(U1_RIGHT);
	Basic_Move(L1_LEFT_R1_RIGHT);	
	Basic_Move(L1R1_UP);
	Basic_Move(L1_RIGHT_R1_LEFT);	
	Basic_Move(D1_DOWN);	
	Basic_Move(L1R1_DOWN);
	Basic_Move(U1_DOWN_D1_UP);
	
    //R2
	Basic_Move(R1_UP);		
	Basic_Move(R1_UP);

	//U'
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_UP);
	Basic_Move(U1_LEFT);
	Basic_Move(U1_DOWN);
	
	//R'
	Basic_Move(R1_DOWN);
	Basic_Move(R1_RIGHT);
	Basic_Move(R1_DOWN);
	Basic_Move(R1_LEFT);
	//U'
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_UP);
	Basic_Move(U1_LEFT);
	Basic_Move(U1_DOWN);
	//R
	Basic_Move(R1_UP);		
	Basic_Move(R1_RIGHT);	
	Basic_Move(R1_DOWN);
	Basic_Move(R1_LEFT);
	//U
	Basic_Move(U1_LEFT);
	Basic_Move(U1_UP);
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_DOWN);
	
	//R'
	Basic_Move(R1_DOWN);
	Basic_Move(R1_RIGHT);
	Basic_Move(R1_DOWN);
	Basic_Move(R1_LEFT);
	
	//F'
	Basic_Move(L1_LEFT_R1_RIGHT);	
	Basic_Move(L1R1_UP);
	Basic_Move(L1_RIGHT_R1_LEFT);	
	Basic_Move(U1_UP_D1_DOWN);
	Basic_Move(L1R1_UP);
	Basic_Move(U1_DOWN_D1_UP);
	Basic_Move(U1_RIGHT);
	Basic_Move(U1_UP);
	Basic_Move(U1_LEFT);
	Basic_Move(L1_LEFT_R1_RIGHT);	
	Basic_Move(L1R1_UP);
	Basic_Move(L1_RIGHT_R1_LEFT);	
	Basic_Move(D1_DOWN);	
	Basic_Move(L1R1_DOWN);
	Basic_Move(U1_DOWN_D1_UP);

	

}
*/



