#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

void SCQ_Init(int x );
void LED_Config(void);
void LED_Control(u8 LED,u8 LED_Status);

#define DATE(x)  GPIO_Write(GPIOC,x);
#endif 
