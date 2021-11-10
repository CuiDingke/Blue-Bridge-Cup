#include "stm32f10x_it.h"
#include "adc.h"
#include "led.h"
__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
__IO uint32_t TIM3Freq = 0;
uint16_t capture2 = 0;
extern __IO uint16_t CCR2_Val;
int j;
int Ci;
u32 BIAN;
u32 baibai;
extern int Up,Down;
extern int Jian;
extern u32 TimingDelay;
u8 USAERT_buffer;
int JL;
int shuzu;
extern float T,H;
extern uint32_t THH, TMM, TSS;
extern u16 DZT;
vu32 kk[60][5];

void TIM3_IRQHandler(void)
{ 
  if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET) 
  { 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
    if(CaptureNumber == 0)
    {
      IC3ReadValue1 = TIM_GetCapture2(TIM3);
      CaptureNumber = 1;
    }
    else if(CaptureNumber == 1)
    {
      IC3ReadValue2 = TIM_GetCapture2(TIM3);
      if (IC3ReadValue2 > IC3ReadValue1)
      {
        Capture = (IC3ReadValue2 - IC3ReadValue1); 
      }
      else
      {
        Capture = ((0xFFFF - IC3ReadValue1) + IC3ReadValue2); 
      }
      TIM3Freq = (uint32_t) 18000000 / Capture;
      CaptureNumber = 0;
    }
  }
}


void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2 );
    capture2 = TIM_GetCapture2(TIM2);
		if(j==0)
		{
			j++;
	    TIM_SetCompare2(TIM2, capture2 + CCR2_Val/2 );	
		}
		else
		{
			j=0;
	    TIM_SetCompare2(TIM2, capture2 + CCR2_Val/2 );
		}
  }
	
}

void SysTick_Handler(void)
{
	TimingDelay--;
	
	if(--baibai==0)
	{
		baibai=Jian*900;
		
		BIAN++;
		if(BIAN>=400) BIAN=0;
		if(BIAN%2==0)
		{
			DMA_Cmd (DMA1_Channel1,DISABLE);
			DMA1_Channel4->CNDTR=60;
			DMA_Cmd(DMA1_Channel1, ENABLE);
			Ci++;
			if(shuzu==60)shuzu=0;
			kk[shuzu][0]=T;
			kk[shuzu][1]=H;
			kk[shuzu][2]=THH;
			kk[shuzu][3]=TMM;
			kk[shuzu][4]=TSS;
			shuzu++;
			LED_Control(3,0);
		}
		if(BIAN%2==1)
		{
			DMA_Cmd (DMA1_Channel1,DISABLE);
			LED_Control(3,1);
		}
	}

}

void USART2_IRQHandler(void)
{
	 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	 {
		 USART_ClearITPendingBit( USART2, USART_IT_RXNE);
		 USAERT_buffer=USART_ReceiveData( USART2);
		 USART2->DR=USAERT_buffer;
	     if((USAERT_buffer=='C'))
			 {
				 JL=1;
//				 USART_ITConfig(USART2, USART_IT_RXNE,DISABLE);
			 }
			 if((USAERT_buffer=='T'))
			 {
				 JL=2;
//				 USART_ITConfig(USART2, USART_IT_RXNE,DISABLE);
			 }
	 }
}