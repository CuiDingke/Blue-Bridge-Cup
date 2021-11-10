#include "stm32f10x_it.h"
#include "led.h"
extern u32 TimingDelay;
extern int a,b,c;
__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
__IO uint32_t TIM3Freq = 0;

int i=0;
extern uint32_t j;
uint16_t capture1 = 0;
extern __IO uint16_t CCR1_Val;
int mm=0;
extern float Vim,Vavg,S;
extern int m;
int n=0;
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
      TIM3Freq = (uint32_t) 18000000 / (Capture*1000);
      CaptureNumber = 0;
    }
		n++;
		Vim = 2*TIM3Freq*3.6;
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
	    TIM_SetCompare1(TIM3, capture1 + j/2 );	
		}
		else
		{
			i=0;
	    TIM_SetCompare1(TIM3, capture1 + j/2 );
		}
  }
}

void SysTick_Handler(void)
{
	TimingDelay--;
	if(c==1)
	{
		mm++;
		if(mm/300==0)
		{
			SCQ_Init(0xfe00);
		}
		if(mm/300==1)
		{
			SCQ_Init(0xff00);
		}
	if(mm==600)mm=0;
	}
}

