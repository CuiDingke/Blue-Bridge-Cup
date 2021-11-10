#include "stm32f10x.h"
#include "lcd.h"
#include "key.h"
#include "led.h"
u32 TimingDelay = 0;
void Delay_Ms(u32 nTime);
int count,Count,i,j;
uint8_t A[50],B[50];
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	Key_Config();
	LED_Config();
	
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	Delay_Ms(1000);
  SCQ_Init(0x00ff);
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
			Delay_Ms(300);
			for(i=0;i<500;i++)
			{
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
					count = 2;
					break;
				}
				else
					count = 1;
			}
			if(count==1) SCQ_Init(0x0000);
			if(count==2) SCQ_Init(0xffff);
			sprintf((char*) A,"%d",count);
			LCD_DisplayStringLine(Line4 ,(unsigned char *)A);
	  }
			
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0);
			Delay_Ms(500);
			for(i=0;i<500;i++)
			{
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0);
					Count = 2;
					break;
				}
				else
					Count = 1;
			}
			if(Count==1) 
			{
				for(j=0;j<=8;j++)
				{
					if(j==8)j=0;
					Delay_Ms(500);
					SCQ_Init(~(0x8000>>j));
					sprintf((char*) B,"%d",j);
			    LCD_DisplayStringLine(Line5 ,(unsigned char *)B);
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
				}	
			}
			if(Count==2) 
			{
				for(j=0;j<=8;j++)
				{
					if(j==8)j=0;
					Delay_Ms(500);
					SCQ_Init(~(0x0100<<j));
					sprintf((char*) B,"%d",j);
			    LCD_DisplayStringLine(Line5 ,(unsigned char *)B);
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
			  }
			}
			sprintf((char*) A,"%d",count);
			LCD_DisplayStringLine(Line4 ,(unsigned char *)A);
	  }
	}

}
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

