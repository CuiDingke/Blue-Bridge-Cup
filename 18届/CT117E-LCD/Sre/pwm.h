#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"


void PwmOut_Init(uint16_t arr,uint16_t psc,uint16_t CCR1_Val,uint16_t CCR2_Val);

#endif
