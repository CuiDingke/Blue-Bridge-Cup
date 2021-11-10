#include "stm32f10x_it.h"
#include "lcd.h"
#include "adc.h"
extern u32 TimingDelay;
int _Ms=0;
extern uint16_t ADC_Conf[30];
extern float T1,T2,T3;
float a1,a2,a3;
uint8_t A[50],B[50],C[50];

void SysTick_Handler(void)
{
	TimingDelay--;
	if(++_Ms==500)
	{
		_Ms=0;
		Average_h(ADC_Conf);
		a1=T1*3.3/4095;
		a2=(1.43-T2)*1000/4.3+25;
		a3=T3*3.3/4095;
		sprintf((char*)A,"DIAN1:%.2f",a1);
		LCD_DisplayStringLine(Line2 ,(unsigned char *)A);
		sprintf((char*)B,"WEN 1:%.2f",a2);
		LCD_DisplayStringLine(Line4 ,(unsigned char *)B);
		sprintf((char*)C,"DIAN2:%.2f",a3);
		LCD_DisplayStringLine(Line6 ,(unsigned char *)C);
	}	
}
