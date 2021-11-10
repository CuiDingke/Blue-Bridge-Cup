#include "stm32f10x.h"
#include "lcd.h"
#include "key.h"
#include "led.h"
#include "tim2.h"
#include "pwm_toggle.h"
#include "misc.h"
#include "rtc.h"
#include "i2c.h"
u32 TimingDelay = 0;
extern uint8_t temp;
int m=0;
int A[50];
uint8_t B[5];
int kk=0;
extern int n;
float Vim=0,Vavg=0,S=0,Toyal=0,ToYal=0,toyal=0;
extern uint32_t THH, TMM, TSS;
extern uint32_t j=18000000;
extern __IO uint32_t TIM3Freq;
extern uint32_t TimeVar;
int jishu=0;
int pp=0;
extern int n;
int c=0;
extern uint8_t temp;
void Delay_Ms(u32 nTime);
int main(void)
{
  u8 *p;
	SysTick_Config(SystemCoreClock/1000);
	Delay_Ms(200);
	STM3210B_LCD_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	RTC_Configuration();
	i2c_init();
	Key_Init();
	LED_Config();
	SCQ_Init(0xff00);
	tim2_huo();

	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	Delay_Ms(1000);
	SCQ_Init(0xff00);
	
	while(1)
	{
		for(kk=0;kk<4;kk++)
		{
			B[kk] = IIC_ReadOneData(kk+1);
		}
		Toyal=*((float *)B);
		toyal = Toyal;
		TimeVar=86399;
	  sprintf((char*) A," Vim(km/h): %D          ",0);
		LCD_DisplayStringLine(Line0 ,(unsigned char *)A);
		sprintf((char*) A," Vavg(km/h): %.3f  ",Vavg);
		LCD_DisplayStringLine(Line2 ,(unsigned char *)A);
		sprintf((char*) A," S(km): %.3lf  ",S);
		LCD_DisplayStringLine(Line6 ,(unsigned char *)A);
		sprintf((char*) A,"  Toyal(km): %F  ",Toyal);
		LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)  
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		  break;
		}	
	}
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
				m-=1000;
				j=18000000/m;
				TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
				toggle_Config();
			}	
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
				m+=1000;
				if(m>20000) m=20000;
				j=18000000/m;
				TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
				toggle_Config();
			}
		if(m<=0)
		{
			m=0;
			TIM_ITConfig(TIM2, TIM_IT_CC2, DISABLE);
			Vim=0;
			jishu = THH*3600+TMM*60+TSS;
			Vavg = S*3600/jishu;
			ToYal=Toyal;
			p=(u8 *)&ToYal;
			for(kk=0;kk<4;kk++)
			{				
				IIC_WriteOneData(kk+1,*(p+kk));
			}
			n=0;
			S=0;
			while(1)
			{
				TimeVar=86399;
				for(kk=0;kk<4;kk++)
				{
					B[kk] = IIC_ReadOneData(kk+1);
				}
				Toyal=*((float *)B);
				toyal = Toyal;
				sprintf((char*) A," Vim(km/h): %.1f          ",Vim);
				LCD_DisplayStringLine(Line0 ,(unsigned char *)A);
				sprintf((char*) A," Vavg(km/h): %.3f  ",Vavg);
				LCD_DisplayStringLine(Line2 ,(unsigned char *)A);
				sprintf((char*) A," S(km): %.3f  ",S);
				LCD_DisplayStringLine(Line6 ,(unsigned char *)A);
				sprintf((char*) A,"  Toyal(km): %.3f  ",Toyal);
				LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
				break;
			}
		}
		S=0.000002*n;	
    Toyal=toyal+S;		
		if(Vim>90)
		{
			c=1;
		}
		else 
		{
			c=0;
			SCQ_Init(0xff00);
		}
		sprintf((char*) A," Vim(km/h): %.1f          ",Vim);
		LCD_DisplayStringLine(Line0 ,(unsigned char *)A);
		sprintf((char*) A," Vavg(km/h): %.3f  ",Vavg);
		LCD_DisplayStringLine(Line2 ,(unsigned char *)A);
		sprintf((char*) A," S(km): %.3f  ",S);
		LCD_DisplayStringLine(Line6 ,(unsigned char *)A);
		sprintf((char*) A,"  Toyal(km): %.3f  ",Toyal);
		LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
	}
}
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
