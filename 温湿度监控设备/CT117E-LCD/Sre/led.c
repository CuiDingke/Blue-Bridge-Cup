#include "led.h"
u16 a=0xffff;
void LED_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

 void SCQ_Init(int x )
{
	DATE(x);
	GPIOD->ODR|=(1<<2);
	GPIOD->ODR&=~(1<<2);
}


void LED_Control(u8 LED,u8 LED_Status)
{
	if(LED_Status == 0)
	{
		u16 table[8]={0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};
		a|=table[LED-1];
		SCQ_Init(a);
	}        
	else
	{
		u16 table[8]={0xfeff,0xfdff,0xfbff,0xf7ff,0xefff,0xdfff,0xbfff,0x7fff};
		a&=table[LED-1];
		SCQ_Init(a);
	}
}
