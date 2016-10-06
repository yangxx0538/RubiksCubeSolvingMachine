#include "delay.h"

u8 fac_us=0;//us延时倍乘数
 
 
void Delay(u32 time)
{
    while(time--);
  
}


//软件精准延时1ms
void Delay1ms(void)
{
    u32 a=8000;
    while(a--);
    
}

void delay_ms(u32 n)
{
    u32 i=0;
    
    for(i=0;i<n;i++)    
    { 
        Delay1ms();
    }
}


 
//IIC专用延时函数
void delay_init(void)	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us = SystemCoreClock/8000000;	//为系统时钟的1/8  
}	


//非常准确的us级延时
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 

}
 


