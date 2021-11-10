#include "stm32f10x.h"
#include "lcd.h"
#include  "led.h"
#include "Time_test.h"
#include "delay.h"
#include "bsp_usart1.h"
#include "stdio.h"
#include "pwm_output.h"
#include "rtc.h"

u32 TimingDelay = 0;
uint32_t TimeVar;
void Delay_Ms(u32 nTime);
void Delay_xs(int t);
void liang(void);
void SCQ_Init(int x );
 extern uint32_t THH, TMM, TSS;
int i = 1;
int j,l,m=0,n=0,w=0,a ,c,tt,mm;
int High[5]={-5,0,0,0,0};
int dui[5]={0,1,2,3,4};
char aa[50];
extern int q,p;
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	Delay_Ms(200);
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	LED_GPIO_Config();
	RTC_Configuration();
	TIM2_Configuration();
	TIM2_NVIC_Configuration();
	USART1_Config();
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_SetBackColor(White);
	LCD_SetTextColor(Black);
	
	LCD_DisplayStringLine(Line2,(unsigned char *)"        HIGH        ");
	sprintf((char*)aa,"         %d        ",i);
	LCD_DisplayStringLine1(Line4,(unsigned char *)aa);
	SCQ_Init(0XFF00);
	while(1)
	{
	  int	t = 200;
		tt = 5;
		SCQ_Init(0XFF00);
		mm = GPIO_ReadOutputData(GPIOC);
		sprintf((char*)aa,"         %d        ",i);
		LCD_DisplayStringLine1(Line4,(unsigned char *)aa);
		SCQ_Init(mm);
		liang();
		while(t--)
			{
				Delay_Ms(1);
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) {High[1] = 1;GPIOC->ODR&=~(1<<8);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0) {High[2] = 2;GPIOC->ODR&=~(1<<9);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0) {High[3] = 3;GPIOC->ODR&=~(1<<10);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0) {High[4] = 4;GPIOC->ODR&=~(1<<11);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}	
			}	
		if(i==2) tt = 6;
		for(j=0;j<tt;j++)
			{ 
				t=200;
				m = i+j;
				if(m>4) m = i+j-2*(i+j-4); 
				while(High[m]>0)
				{
					if(i>m) 
					{	
						GPIO_ResetBits(GPIOA,GPIO_Pin_4);
						n = i-m;
						TIM2_Mode_Config(999,71,600,0);
						TIM_Cmd(TIM3, ENABLE);
						a=3;
						TIM_Cmd(TIM2, ENABLE);
						for(w=0;w<n;w++)
						{
							Delay_xs(1);
							i--;
							liang();
							mm = GPIO_ReadOutputData(GPIOC);
							sprintf((char*)aa,"         %d        ",i);
			        LCD_DisplayStringLine1(Line4,(unsigned char *)aa);
							SCQ_Init(mm|0xf000);
						}
						a=0;
						TIM_Cmd(TIM3, DISABLE);
						a=1;
						TIM2_Mode_Config(999,35,0,600);
						TIM_Cmd(TIM3, ENABLE);
						GPIO_SetBits(GPIOA,GPIO_Pin_5);
						Delay_Ms(180);		
						TIM2_Mode_Config(999,35,0,500);
						GPIO_ResetBits(GPIOA,GPIO_Pin_5);
						Delay_Ms(180);
						TIM_Cmd(TIM3, DISABLE);
						TIM_Cmd(TIM2, DISABLE);
						a=0;
						mm = GPIO_ReadOutputData(GPIOC);
					  sprintf((char*)aa,"         %d        ",i);
			      LCD_DisplayStringLine1(Line4,(unsigned char *)aa);
					  SCQ_Init(mm);
						while(t--)
						{
							Delay_Ms(1);
							if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) {High[1] = 1;GPIOC->ODR&=~(1<<8);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
							if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0) {High[2] = 2;GPIOC->ODR&=~(1<<9);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
							if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0) {High[3] = 3;GPIOC->ODR&=~(1<<10);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
							if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0) {High[4] = 4;GPIOC->ODR&=~(1<<11);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
						}			
						p = 0;
						q = 0;
					}
					
					else 
					{
						GPIO_SetBits(GPIOA,GPIO_Pin_4);
						n = m-i;
						TIM2_Mode_Config(999,71,800,0);
						TIM_Cmd(TIM3, ENABLE);
						a=2;
						TIM_Cmd(TIM2, ENABLE);
						for(w=0;w<n;w++)
						{
							Delay_xs(1);
							i++;
							liang();
							mm = GPIO_ReadOutputData(GPIOC);
							sprintf((char*)aa,"         %d        ",i);
			        LCD_DisplayStringLine1(Line4,(unsigned char *)aa);
							SCQ_Init(mm|0xf000);
						}
						a=0;
						TIM_Cmd(TIM3, DISABLE);	
						a=1;
						TIM2_Mode_Config(999,35,0,600);
						TIM_Cmd(TIM3, ENABLE);
						GPIO_SetBits(GPIOA,GPIO_Pin_5);
						Delay_Ms(180);
						TIM2_Mode_Config(999,35,0,500);
						GPIO_ResetBits(GPIOA,GPIO_Pin_5);
						Delay_Ms(180);
						TIM_Cmd(TIM3, DISABLE);
						TIM_Cmd(TIM2, DISABLE);
						a=0;
						mm = GPIO_ReadOutputData(GPIOC);
						sprintf((char*)aa,"         %d        ",i);
						LCD_DisplayStringLine1(Line4,(unsigned char *)aa);
						SCQ_Init(mm);
						while(t--)
						{
							Delay_Ms(1);
							if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) {High[1] = 1;GPIOC->ODR&=~(1<<8);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
							if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0) {High[2] = 2;GPIOC->ODR&=~(1<<9);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
							if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0) {High[3] = 3;GPIOC->ODR&=~(1<<10);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
							if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0) {High[4] = 4;GPIOC->ODR&=~(1<<11);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);j=1;}
				
						}			
            p = 0;
						q = 0;						
					}
						i = m;
					  
						j = 0;
					  
					  break;
				}
				
				High[i]=0;
			}
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
void Delay_xs(int t)
{
	while(t--)
	{
		Delay_Ms(650);
	}
}
void liang(void)
{
	if(i==1) GPIOC->ODR|=(1<<8);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);
	if(i==2) GPIOC->ODR|=(1<<9);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);
	if(i==3) GPIOC->ODR|=(1<<10);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);
	if(i==4) GPIOC->ODR|=(1<<11);GPIOD->ODR|=(1<<2);GPIOD->ODR&=~(1<<2);
}

