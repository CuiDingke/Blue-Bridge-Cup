#include "timer.h"

void TIM3_Int_Init()
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	  NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
    
    TIM_TimeBaseStructure.TIM_Period=100-1;		 								
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    
    TIM_TimeBaseStructure.TIM_ClockDivision=0; 		
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);							    		
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	  //使能TIMx外设
							 
}

