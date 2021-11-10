#include "stm32f10x_it.h"
#include "lcd.h"
#include "led.h"
void LCD_DisplayStringLine1(u8 Line, u8 *ptr);
void LCD_DisplayStringLine(u8 Line, u8 *ptr);
void SCQ_Init(int x );
extern u32 TimingDelay;
extern char aa[50];
extern int i,n,a,mm,c;
int qq=0,b;
int q=0,p=0;
void TIM2_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{	
		
		if(a==2)
		{
			b++;
			if(b==100) 
			{
				GPIOC->ODR&=~(1<<12);
			}
			if(b==200) 
			{
				GPIOC->ODR|=(1<<12);
			}
			if(b==300) 
			{
				GPIOC->ODR&=~(1<<13);
			}
			if(b==400) 
			{
				GPIOC->ODR|=(1<<13);
			}
			if(b==500) 
			{
				GPIOC->ODR&=~(1<<14);
			}
			if(b==600) 
			{
				GPIOC->ODR|=(1<<14);
			}
			if(b==700) 
			{
				GPIOC->ODR&=~(1<<15);
			}
			if(b==800) 
			{
				GPIOC->ODR|=(1<<15);
				
			}
			if(b==900) b = 0;

		}
			if(a==3)
		{
			c++;
			if(c==700) 
			{
				GPIOC->ODR&=~(1<<12);
			}
			if(c==800) 
			{
				GPIOC->ODR|=(1<<12);
			}
			if(c==500) 
			{
				GPIOC->ODR&=~(1<<13);
			}
			if(c==600) 
			{
				GPIOC->ODR|=(1<<13);
			}
			if(c==300) 
			{
				GPIOC->ODR&=~(1<<14);
			}
			if(c==400) 
			{
				GPIOC->ODR|=(1<<14);
			}
			if(c==100) 
			{
				GPIOC->ODR&=~(1<<15);
			}
			if(c==200) 
			{
				GPIOC->ODR|=(1<<15);
				
			}
			if(c==900) c = 0;

		}
		
			GPIOD->ODR|=(1<<2);
	    GPIOD->ODR&=~(1<<2);
		if(a==1)
		{
			q++;
			if(q/25==0||q/25==2)
			{
				mm = GPIO_ReadOutputData(GPIOC);
				sprintf((char*)aa,"         %d        ",i);
				LCD_DisplayStringLine1(Line4,(unsigned char *)aa);
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
		 	TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update); 	 
	}		 	
} 

void SysTick_Handler(void)
{
	TimingDelay--;
}

