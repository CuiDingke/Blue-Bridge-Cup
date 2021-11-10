#include "stm32f10x.h"
#include "delay.h"
#include "key.h"
#include "usart1.h"
#include "misc.h"
int count = 0;
int i = 0;
int main(void)
{
   delay_init();
	 Key_Init();
	 USART1_Config();
    while (1)
    {
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
				delay_ms(500);
				for(i=0;i<500;i++)
				{
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
						delay_ms(500);
						for(i=0;i<500;i++)
						{
							if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
							{
								while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
								count = 3;
								break;
							}
							else
							{
								count = 2;
							}
						}
						break;
					}
					else
						count = 1;
				}
				printf("Êý×Ö:%d",count);
			}
			
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);
				delay_ms(500);
				for(i=0;i<500;i++)
				{
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);
						delay_ms(500);
						for(i=0;i<500;i++)
						{
							if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
							{
								while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);
								count = 6;
								break;
							}
							else
							{
								count = 5;
							}
							
						}
						break;
					}
					else
						count = 4;
				}
				printf("Êý×Ö:%d",count);
			}
			
			if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0);
				delay_ms(500);
				for(i=0;i<500;i++)
				{
					if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0);
						delay_ms(500);
						for(i=0;i<500;i++)
						{
							if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0)
							{
								while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0);
								count = 9;
								break;
							}
							else
							{
								count = 8;
							}	
						}
						break;
					}
					else
						count = 7;
				}
				printf("Êý×Ö:%d",count);
			}
    }
		
}
