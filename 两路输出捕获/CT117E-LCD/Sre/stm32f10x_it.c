#include "stm32f10x_it.h"

extern u32 TimingDelay;

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
      TIM3Freq = (uint32_t) SystemCoreClock / Capture;
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
      TIM3Freq1 = (uint32_t) SystemCoreClock / Capture1;
      CaptureNumber1 = 0;
    }
  }
}

void SysTick_Handler(void)
{
	TimingDelay--;
}

