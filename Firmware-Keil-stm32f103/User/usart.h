#ifndef _USART_H
#define _USART_H


#include "stm32f10x.h"


void RCC_Configuration(void);   //??RCC?????
void UART_GPIO_Configuration(void);   //??GPIO?????
void NVIC_Configuration(void);   //??NVIC?????
void USART_Configuration(void);   //?????????
void Time_Init(void);     //??????????
void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data) ;
unsigned short CRC16(unsigned char* puchMsg, unsigned short usDataLen);
 
 
#endif


