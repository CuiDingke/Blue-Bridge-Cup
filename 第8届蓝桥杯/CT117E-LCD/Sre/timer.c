#include "timer.h"

void TIM3_Int_Init()
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	  NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
    
    TIM_TimeBaseStructure.TIM_Period=100-1;		 								
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    
    TIM_TimeBaseStructure.TIM_ClockDivision=0; 		
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);							    		
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	  //ʹ��TIMx����
							 
}

