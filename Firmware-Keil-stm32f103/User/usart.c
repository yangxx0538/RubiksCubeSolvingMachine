#include "stm32f10x.h"
#include "usart.h"


void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;      //枚举变量，定义高速时钟的启动状态
	RCC_DeInit();                   //RCC系统重置，用于Debug目的
	RCC_HSEConfig(RCC_HSE_ON);                 //使能高速时钟源HSE  
	HSEStartUpStatus = RCC_WaitForHSEStartUp();    //等待HSE稳定
	if(HSEStartUpStatus == SUCCESS)
	{
		FLASH_SetLatency(FLASH_Latency_2);     
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);     

		RCC_HCLKConfig(RCC_SYSCLK_Div1);         // HCLK = SYSCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);          // PCLK2 = HCLK
		RCC_PCLK1Config(RCC_HCLK_Div2);         ///PCLK1 = HCLK/2

		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08){}
	}
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO |RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}


void UART_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;     //GPIO初始化结构体声明


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          //USART1 TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);      //A端口

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          //USART1 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //复用浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);           //A端口

}
//------------------------------------------------------------------
//函数名：void NVIC_Configuration()
//输入参数：null
//返回参数：null
//说明：NVIC初始化函数
//------------------------------------------------------------------
void NVIC_Configuration(void)
{              
	NVIC_InitTypeDef NVIC_InitStructure;       //NVIC初始化结构体声明

	#ifdef VECT_TAB_RAM       
 
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); //如果程序在RAM中调试那么定义中断向量表在RAM中否则在Flash中
	#else 

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
	#endif

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         //设置串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;         //抢占优先级 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //子优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           //设置定时器3全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //子优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能
	NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------------------------------------
//函数名：void USART_Configuration()
//输入参数：null
//返回参数：null
//说明:串口初始化函数
//------------------------------------------------------------------
void USART_Configuration(void)
{
	
	
	USART_InitTypeDef USART_InitStructure;                   //串口初始化结构体声明
	USART_ClockInitTypeDef USART_ClockInitStruct;
	USART_InitStructure.USART_BaudRate = 9600;      //设置波特率为115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;    //无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;     //接受和发送模式都打开
	USART_ClockInitStruct.USART_Clock=USART_Clock_Disable;      //串口时钟禁止
	USART_ClockInitStruct.USART_CPOL=USART_CPOL_Low;        //数据低电平有效
	USART_ClockInitStruct.USART_CPHA=USART_CPHA_2Edge;    //配置CPHA使数据在第2个边沿的时候被捕获
	USART_ClockInitStruct.USART_LastBit=USART_LastBit_Disable;  // 禁用最后一位,使对应的时钟脉冲不会再输出到SCLK引脚
	USART_ClockInit(USART1, &USART_ClockInitStruct);      //配置USART与时钟相关的设置
	USART_Init(USART1, &USART_InitStructure);       //配置串口参数函数
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);       //使能接收中断
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    //使能发送缓冲空中断
	//USART_ITConfig(USART1, USART_IT_TC, ENABLE);    //使能发送完成中断
	USART_ClearFlag(USART1,USART_FLAG_TC);         //清除发送完成标志位
	USART_GetFlagStatus(USART1, USART_FLAG_TC);
	USART_Cmd(USART1, ENABLE);         //使能串口1
  
  
}



void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data)  
{
    USART_SendData(USARTx, Data);  
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}  
}
void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str)    
{    
    while (0 != *str)    
    {    
        UART_PutChar(USARTx, *str);    
        str++;    
    }    
}   




