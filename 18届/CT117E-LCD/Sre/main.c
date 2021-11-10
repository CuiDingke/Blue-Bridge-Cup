#include "stm32f10x.h"
#include "lcd.h"
#include "key.h"
#include "led.h"
#include "gpio.h"
#include "pwm.h"
#include "time.h"
u32 TimingDelay = 0;
int TAI=1,Jilu,T=300,i,m=1,n,j,k,w,TT;
uint8_t Tai[5]={0,0,0,0,0};
extern uint32_t THH, TMM, TSS;
extern int a,mm;
void Delay_Ms(u32 nTime);
void Deng(void);
void mie(void);
uint8_t A[50],B[50];
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	Delay_Ms(200);
	STM3210B_LCD_Init();
	
	RTC_Configuration();
	Key_Init();
	LED_Config();
	Gpio_Init();
	Time_Init();
	
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White); 
	LCD_DisplayStringLine(Line2 ,(unsigned char *)"        HIGH    ");
	LCD_DisplayStringLine1(Line4 ,(unsigned char *)"         1    ");
	Delay_Ms(1000);
  SCQ_Init(0XFF00);
	while(1)
	{
		while(T--)
		{
			Delay_Ms(10);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) {Tai[1]=1;}	
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0) {Tai[2]=1;}
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0) {Tai[3]=1;}
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0) {Tai[4]=1;}
			Deng();
	  }
		for(i=0;i<8;i++)
		{
			T=40;	
			j=m+i;
			if(j>4) j=9-j;		
			while(Tai[j]>0)
			{
				Tai[j]=0;
				if(j>m)
				{
					n=j-m;
					PwmOut_Init(999,71,800,0);
					TIM_Cmd(TIM3, ENABLE);
					mm = GPIO_ReadOutputData(GPIOC);
					a=2;
					TIM_Cmd(TIM2, ENABLE);
					for(k=0;k<n;k++)
					{
						
						GPIO_SetBits(GPIOA,GPIO_Pin_4);
						Delay_Ms(6000);
						m++;
						mie();
						Jilu=GPIO_ReadInputData(GPIOC);
						sprintf((char*)A,"         %d        ",m);
						LCD_DisplayStringLine1(Line4,(unsigned char *)A);
						SCQ_Init(Jilu);
						
					}
					Jilu=GPIO_ReadInputData(GPIOC);
					SCQ_Init(Jilu|0xf000);
					PwmOut_Init(999,35,0,600);
					a=1;
					GPIO_SetBits(GPIOA,GPIO_Pin_5);
					T=40;
					while(T--)
					{
						Delay_Ms(10);
						if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) {Tai[1]=1;}	
						if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0) {Tai[2]=1;}
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0) {Tai[3]=1;}
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0) {Tai[4]=1;}
						Deng();
					}
					Delay_Ms(30);
					PwmOut_Init(999,35,0,500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					Delay_Ms(200);
					TIM_Cmd(TIM2, DISABLE);
					TIM_Cmd(TIM3, DISABLE);
				}	
        else
				{
					n=m-j;
					PwmOut_Init(999,71,600,0);
					TIM_Cmd(TIM3, ENABLE);
					mm = GPIO_ReadOutputData(GPIOC);
					a=3;
					TIM_Cmd(TIM2, ENABLE);
					for(k=0;k<n;k++)
					{
						PwmOut_Init(999,71,600,0);
						TIM_Cmd(TIM3, ENABLE);
						GPIO_ResetBits(GPIOA,GPIO_Pin_4);
						Delay_Ms(6000);
						m--;
						mie();
						Jilu=GPIO_ReadInputData(GPIOC);
						sprintf((char*)A,"         %d        ",m);
						LCD_DisplayStringLine1(Line4,(unsigned char *)A);
						SCQ_Init(Jilu);
					}
					Jilu=GPIO_ReadInputData(GPIOC);
					SCQ_Init(Jilu|0xf000);
					PwmOut_Init(999,35,0,600);
					a=1;
					GPIO_SetBits(GPIOA,GPIO_Pin_5);
					T=20;
					while(T--)
					{
						Delay_Ms(10);
						if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) {Tai[1]=1;}	
						if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0) {Tai[2]=1;}
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0) {Tai[3]=1;}
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0) {Tai[4]=1;}
						Deng();
					}
					Delay_Ms(30);
					PwmOut_Init(999,35,0,500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					Delay_Ms(200);
					TIM_Cmd(TIM2, DISABLE);
					TIM_Cmd(TIM3, DISABLE);
				}	
				a=0;
				Jilu=GPIO_ReadInputData(GPIOC);
				sprintf((char*)A,"         %d        ",m);
				LCD_DisplayStringLine1(Line4,(unsigned char *)A);
				SCQ_Init(Jilu);
				break;
			}
			mie();
		}	
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

void Deng(void)
{
	if(Tai[1]==1) GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	if(Tai[2]==1) GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	if(Tai[3]==1) GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	if(Tai[4]==1) GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	
	GPIOD->ODR|=(1<<2);
	GPIOD->ODR&=~(1<<2);
}
void mie(void)
{
	if(m==1) GPIO_SetBits(GPIOC,GPIO_Pin_8);
	if(m==2) GPIO_SetBits(GPIOC,GPIO_Pin_9);
	if(m==3) GPIO_SetBits(GPIOC,GPIO_Pin_10);
	if(m==4) GPIO_SetBits(GPIOC,GPIO_Pin_11);
	GPIOD->ODR|=(1<<2);
	GPIOD->ODR&=~(1<<2);
}
