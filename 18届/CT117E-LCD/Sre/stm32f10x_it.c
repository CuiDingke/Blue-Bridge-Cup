#include "stm32f10x_it.h"
#include "lcd.h"
#include "led.h"
extern u32 TimingDelay;
extern int m;
int q,mm,a=0,b,c,p;
uint8_t bb[50];
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
 {	
	 TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update); 
	if(a==2)
		{
			b++;
			if(b==200)SCQ_Init(~(0x8000>>0)&mm);
			if(b==300)SCQ_Init(0xff00&mm);
			if(b==400)SCQ_Init(~(0x8000>>1)&mm);
			if(b==500)SCQ_Init(0xff00&mm);
			if(b==600)SCQ_Init(~(0x8000>>2)&mm);
			if(b==700)SCQ_Init(0xff00&mm);
			if(b==800)SCQ_Init(~(0x8000>>3)&mm);
			if(b==900)SCQ_Init(0xff00&mm);
			if(b==1000)b=100;
		}
	if(a==3)
		{
			b++;
			if(b==200)SCQ_Init(~(0x8000>>3)&mm);
			if(b==300)SCQ_Init(0xff00&mm);
			if(b==400)SCQ_Init(~(0x8000>>2)&mm);
			if(b==500)SCQ_Init(0xff00&mm);
			if(b==600)SCQ_Init(~(0x8000>>1)&mm);
			if(b==700)SCQ_Init(0xff00&mm);
			if(b==800)SCQ_Init(~(0x8000>>0)&mm);
			if(b==900)SCQ_Init(0xff00&mm);
			if(b==1000)b=100;
		}		
  if(a==1)
		{
			q++;
			if(q/25==0||q/25==2)
			{
				mm = GPIO_ReadOutputData(GPIOC);
				sprintf((char*)bb,"         %d        ",m);
				LCD_DisplayStringLine1(Line4,(unsigned char *)bb);
				SCQ_Init(mm);	
			}
			if(q/25==1||q/25==3)
			{
				mm = GPIO_ReadOutputData(GPIOC);
				LCD_DisplayStringLine(Line4,(unsigned char *)"                        ");
				SCQ_Init(mm);
			}
			if(q>=100) q=0; 	
	  }		
 }
}

void SysTick_Handler(void)
{
	TimingDelay--;
}
