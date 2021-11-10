#include "stm32f10x.h"
#include "lcd.h"
#include "tim3.h"
#include "tim2.h"

u32 TimingDelay = 0;
void Delay_Ms(u32 nTime);
extern __IO uint32_t TIM3Freq1;
extern __IO uint32_t TIM3Freq;
extern int m,n;
uint8_t A[50],B[50];


int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	Delay_Ms(200);
	

	
	STM3210B_LCD_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	tim2_huo();
	tim3_chu();
	led_Init();
	
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	Delay_Ms(1000);

	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
			m = m+30;
			if(m>=999) m=999;
			if(m<=1)  m=1;
		}
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0);
			n = n+30;
			if(n>=999) n=999;
			if(n<=1)  n=1;
		}
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
			m = m-30;
			if(m>=999) m=999;
			if(m<=1)  m=1;	
		}
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
			n = n-30;
			if(n>=999) n=999;
			if(n<=1)  n=1;
		}
		tim3_chu();
		sprintf((char*)A,"T1:%d          ",TIM3Freq1);
    LCD_DisplayStringLine(Line3,(unsigned char *)A);
		
		sprintf((char*)B,"T2:%d          ",TIM3Freq);
		LCD_DisplayStringLine(Line4,(unsigned char *)B);
	
	}
}


void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
