/**
  ******************************************************************************
  * @file    main.c 
  * @author  yangxx
  * @date    8/14/2016
  ******************************************************************************
  */
#include "stm32f10x.h"
#include "delay.h"
#include "math.h"
#include "usart.h"
#include "stm32_iic.h"
#include "delay.h"
#include "IO.h"
#include "Control.h"
#include "usart.h"


int i,x,test,start_Solving_flag;

int main(void)
{  
	SystemInit();
	
	RCC_Configuration();
	NVIC_Configuration();
	
	UART_GPIO_Configuration();
	USART_Configuration();
	
	Motor_Config(); 

	delay_ms(10) ;
	
	Basic_Move(ALL_Calib);			//回到行程开关零起点位置


	while(1)	
	{
		
		if(start_Solving_flag)
		{
			
			for(x = 0 ; x< 100 ; x += 2)
			{
				if(result_buffer[x] == 'F' && result_buffer[x+1] == '1') F;
				else if(result_buffer[x] == 'F' && result_buffer[x+1] == '2') Fd;
				else if(result_buffer[x] == 'F' && result_buffer[x+1] == '3') Fv;
				else if(result_buffer[x] == 'U' && result_buffer[x+1] == '1') U;
				else if(result_buffer[x] == 'U' && result_buffer[x+1] == '2') Ud;
				else if(result_buffer[x] == 'U' && result_buffer[x+1] == '3') Uv;
				else if(result_buffer[x] == 'D' && result_buffer[x+1] == '1') D;
				else if(result_buffer[x] == 'D' && result_buffer[x+1] == '2') Dd;
				else if(result_buffer[x] == 'D' && result_buffer[x+1] == '3') Dv;
				else if(result_buffer[x] == 'B' && result_buffer[x+1] == '1') B;
				else if(result_buffer[x] == 'B' && result_buffer[x+1] == '2') Bd;
				else if(result_buffer[x] == 'B' && result_buffer[x+1] == '3') Bv;
				else if(result_buffer[x] == 'L' && result_buffer[x+1] == '1') L;
				else if(result_buffer[x] == 'L' && result_buffer[x+1] == '2') Ld;
				else if(result_buffer[x] == 'L' && result_buffer[x+1] == '3') Lv;
				else if(result_buffer[x] == 'R' && result_buffer[x+1] == '1') R;
				else if(result_buffer[x] == 'R' && result_buffer[x+1] == '2') Rd;
				else if(result_buffer[x] == 'R' && result_buffer[x+1] == '3') Rv;
				
				else if(result_buffer[x] == 0x8A) 			// start signal
				{
					Basic_Move(ALL_Calib); 
					UART_PutChar(USART1,0xFE);
					UART_PutChar(USART1,0xAA);
					break;
				}
				
			}
			start_Solving_flag = 0;
			
		}
		
		
		
		if(testCommand == 0xA1)			//将第一面对准摄像头
		{
			Basic_Move(ALL_Calib_IN);
			rotateFace1_front;			
			testCommand = 0x00;
			delay_ms(20);
			UART_PutChar(USART1,0xFE);
			UART_PutChar(USART1,0xA1);
		}
		else if(testCommand == 0xA2 ||  testCommand == 0xA3 || testCommand == 0xA4 )
		{
			rotateFace2_4_front;
			delay_ms(20);
			UART_PutChar(USART1,0xFE);
			UART_PutChar(USART1,testCommand);
			testCommand = 0x00;
		}
		else if(testCommand == 0xA5)
		{
			rotateFace5_side;
			testCommand = 0x00;
			delay_ms(1000);
			UART_PutChar(USART1,0xFE);
			UART_PutChar(USART1,0xA5);
		}
		else if(testCommand == 0xA6)
		{
			rotateFace6_side;
			testCommand = 0x00;
			delay_ms(1000);
			UART_PutChar(USART1,0xFE);
			UART_PutChar(USART1,0xA6);
		}
		else if(testCommand == 0xA7)		//最后一面对准摄像头
		{
			rotateOver;
			testCommand = 0x00;
			delay_ms(20);
			UART_PutChar(USART1,0xFE);
			UART_PutChar(USART1,0xA7);
		}	
		

	}
	
}

