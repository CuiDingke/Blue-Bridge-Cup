#include "stm32f10x.h"
#include "lcd.h"
#include "adc.h"
#include "usart2_it.h"
extern float TO1;
extern uint16_t ADC_Conf[30];
u32 TimingDelay = 0;
void Delay_Ms(u32 nTime);
int j;
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	Delay_Ms(200);
	STM3210B_LCD_Init();
	
	Adc_Init();
	USART2_Config();
	
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	Delay_Ms(1000);
	while(1)
	{
		for(j=0;j<30;j++)
		{
			printf("%d   :%d  \r\n",j,ADC_Conf[j]);
		}
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
