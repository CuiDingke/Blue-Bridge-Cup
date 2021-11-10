#include "stm32f10x_it.h"

int i,j;
extern u32 TimingDelay;
uint16_t capture1 = 0,capture2 = 0;
extern __IO uint16_t CCR1_Val,CCR2_Val;

u8 USAERT_buffer[20];
u8 Rcount=0,Rover=0;

__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
__IO uint32_t TIM3Freq = 0;

__IO uint16_t IC3ReadValue11 = 0, IC3ReadValue21 = 0;
__IO uint16_t CaptureNumber1 = 0;
__IO uint32_t Capture1 = 0;
__IO uint32_t TIM3Freq1 = 0;

void TIM2_IRQHandler(void)
{ 
  if(TIM_GetITStatus(TIM2, TIM_IT_CC2) == SET) 
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
    if(CaptureNumber == 0)
    {
      IC3ReadValue1 = TIM_GetCapture2(TIM2);
      CaptureNumber = 1;
    }
    else if(CaptureNumber == 1)
    {
      IC3ReadValue2 = TIM_GetCapture2(TIM2); 
      if (IC3ReadValue2 > IC3ReadValue1)
      {
        Capture = (IC3ReadValue2 - IC3ReadValue1); 
      }
      else
      {
        Capture = ((0xFFFF - IC3ReadValue1) + IC3ReadValue2); 
      }
      TIM3Freq = (uint32_t) 2000000 / Capture;
      CaptureNumber = 0;
    }
  }
	
	if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == SET) 
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
    if(CaptureNumber1 == 0)
    {
      IC3ReadValue11 = TIM_GetCapture3(TIM2);
      CaptureNumber1 = 1;
    }
    else if(CaptureNumber1 == 1)
    {
      IC3ReadValue21 = TIM_GetCapture3(TIM2); 
      
      if (IC3ReadValue21 > IC3ReadValue11)
      {
        Capture1 = (IC3ReadValue21 - IC3ReadValue11); 
      }
      else
      {
        Capture1 = ((0xFFFF - IC3ReadValue11) + IC3ReadValue21); 
      }
      TIM3Freq1 = (uint32_t) 2000000 / Capture1;
      CaptureNumber1 = 0;
    }
  }
}


void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 );
    capture1 = TIM_GetCapture1(TIM3);
		if(i==0)
		{
			i++;
	    TIM_SetCompare1(TIM3, capture1 + CCR1_Val/2 );	
		}
		else
		{
			i=0;
	    TIM_SetCompare1(TIM3, capture1 + CCR1_Val/2 );
		}
  }
	
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2 );
    capture2 = TIM_GetCapture2(TIM3);
		if(j==0)
		{
			j++;
	    TIM_SetCompare2(TIM3, capture2 + CCR2_Val/2 );	
		}
		else
		{
			j=0;
	    TIM_SetCompare2(TIM3, capture2 + CCR2_Val/2 );
		}
  }
}

void USART2_IRQHandler(void)
{
	 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	 {
		 USART_ClearITPendingBit( USART2, USART_IT_RXNE);
		 USAERT_buffer[Rcount++]=USART_ReceiveData( USART2);
	   if(Rcount==8)
		 {
			 Rcount=0;
			 Rover=1;
		 }
		 USART_ClearITPendingBit( USART2, USART_IT_RXNE);
	 }
}




void SysTick_Handler(void)
{
	TimingDelay--;

}
