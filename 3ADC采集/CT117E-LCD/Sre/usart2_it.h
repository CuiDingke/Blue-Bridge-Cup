#ifndef __USART2_IT_H
#define	__USART2_IT_H

#include "stm32f10x.h"
#include <stdio.h>

void USART2_Config(void);
int fputc(int ch, FILE *f);
#endif 
