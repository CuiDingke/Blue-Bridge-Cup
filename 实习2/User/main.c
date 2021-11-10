#include "stm32f10x.h"
#include "pwm_toggle.h"
#include "key.h"
#include "delay.h"
#include "usart1.h"
#include "misc.h"
int ii;
int count;
extern __IO uint16_t CCR1_Val,CCR2_Val,CCR3_Val,CCR4_Val;
int main(void)
{
   toggle_Config();
	 Key_Init();
	delay_init();
	USART1_Config();
    while (1)
    {
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
				delay_ms(500);
				for(ii=0;ii<500;ii++)
				{
//					delay_ms(10);
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
						count = 2;
						break;
					}
					else
						count = 1;
				}
				printf("----%d---",count);
				if(count == 1) 
				{
					if(CCR1_Val>=3600) CCR1_Val=3600;
					if(CCR1_Val<=3600) CCR1_Val=CCR1_Val+72;
					CCR4_Val = 3600-CCR1_Val;
					printf("----%d---",CCR1_Val);
				}
				else
				{
					if(CCR1_Val<=1080) CCR1_Val=1080;
					if(CCR1_Val>=1080) CCR1_Val=CCR1_Val-72;
					CCR4_Val = 3600-CCR1_Val;
					printf("----%d---",CCR1_Val);
				
				}
			}
			
			
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);
				delay_ms(500);
				for(ii=0;ii<500;ii++)
				{
//					delay_ms(10);
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);
						count = 2;
						break;
					}
					else
						count = 1;
				}
				printf("----%d---",count);
				if(count == 1) 
				{
					if(CCR2_Val>=3600) CCR2_Val=3600;
					if(CCR2_Val<=3600) CCR2_Val=CCR2_Val+72;
					printf("----%d---",CCR2_Val);
				}
				else
				{
					if(CCR2_Val<=1080) CCR2_Val=1080;
					if(CCR2_Val>=1080) CCR2_Val=CCR2_Val-72;
					printf("----%d---",CCR2_Val);
				
				}
			}
			
				if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0);
				delay_ms(500);
				for(ii=0;ii<500;ii++)
				{
//					delay_ms(10);
					if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0);
						count = 2;
						break;
					}
					else
						count = 1;
				}
				printf("----%d---",count);
				if(count == 1) 
				{
					if(CCR3_Val>=3600) CCR3_Val=3600;
					if(CCR3_Val<=3600) CCR3_Val=CCR3_Val+72;
					printf("----%d---",CCR3_Val);
				}
				else
				{
					if(CCR3_Val<=1080) CCR3_Val=1080;
					if(CCR3_Val>=1080) CCR3_Val=CCR3_Val-72;
					printf("----%d---",CCR3_Val);
				
				}
			}
    }
}
