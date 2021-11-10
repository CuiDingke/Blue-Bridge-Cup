#include "stm32f10x_it.h"
uint16_t capture1 = 0,capture2 = 0,capture3 = 0,capture4 = 0;
extern __IO uint16_t CCR1_Val,CCR2_Val,CCR3_Val,CCR4_Val;
int i,j,m,n;
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 );
    capture1 = TIM_GetCapture1(TIM3);
		if(i==0)
		{
			i++;
	    TIM_SetCompare1(TIM3, capture1 + 3600-CCR1_Val );	
		}
		else
		{
			i=0;
	    TIM_SetCompare1(TIM3, capture1 + CCR1_Val );
		}
  }
	
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2 );
    capture2 = TIM_GetCapture2(TIM3);
		if(j==0)
		{
			j++;
	    TIM_SetCompare2(TIM3, capture2 + 3600-CCR2_Val );	
		}
		else
		{
			j=0;
	    TIM_SetCompare2(TIM3, capture2 + CCR2_Val );
		}
  }
	
	if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3 );
    capture3 = TIM_GetCapture3(TIM3);
		if(m==0)
		{
			m++;
	    TIM_SetCompare3(TIM3, capture3 + 3600-CCR3_Val );	
		}
		else
		{
			m=0;
	    TIM_SetCompare3(TIM3, capture3 + CCR3_Val );
		}
  }
	
	if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4 );
    capture4 = TIM_GetCapture4(TIM3);
		if(n==0)
		{
			n++;
	    TIM_SetCompare4(TIM3, capture4 + 3600-CCR4_Val );	
		}
		else
		{
			n=0;
	    TIM_SetCompare4(TIM3, capture4 + CCR4_Val );
		}
  }
}
