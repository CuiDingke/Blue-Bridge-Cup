#include "stm32f10x.h"
#include "lcd.h"
#include "adc.h"
#include "pwm_input.h"
#include "pwm_toggle.h"
#include "misc.h"
#include "rtc.h"
#include "key.h"
#include "i2c.h"
#include "led.h"
#include "usart2_it.h"
#include "misc.h"
#include "stdio.h"

float T,H;
int m=0,n=0;
u32 TimingDelay = 0;
int Up=0,Down=0,Jian=0;
float Xin=0;
int A[50];
extern uint16_t ADC_Conf[60];
extern __IO uint32_t TIM3Freq;
void Delay_Ms(u32 nTime);
extern uint32_t THH, TMM, TSS;
extern int Ci;
extern u32 baibai;
extern __IO uint16_t CCR2_Val;
extern int JL;
extern int shuzu;
u8 *p;
u8 Zh[5];
int Zt;
extern vu32 kk[60][5];
u8 led1,led2;
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);

	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	Pwm_Input();
	Adc_Init();
	toggle_Config();
	RTC_Configuration();
	Key_Init();
	i2c_init();
  LED_Config();
	USART2_Config();
	SCQ_Init(0xffff);
	
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);

	Delay_Ms(1000);
	SCQ_Init(0xffff);
	while(1)
	{
		  Up=IIC_ReadOneData(20);
			Down=IIC_ReadOneData(21);
			Jian=IIC_ReadOneData(22);
			for(int i=0;i<4;i++)
			{
				Zh[i]=IIC_ReadOneData(i+1);
			}
			Xin=*((float *)Zh);
			baibai=Jian*900;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
			m++;
		}
		while(m%2==0)
		{
			T=24.4*Average_h(ADC_Conf)-20;
			if(T<=-19)  T=-20;
			CCR2_Val=18000/Xin;
			H=0.0089*TIM3Freq+1.1111;
			if(JL==1)
			{
				printf("当前温湿度阈值:%d度%d%%",Up,Down);
				printf("当前时间:%d-%d-%d",THH, TMM, TSS);
				JL=0;
			}
			if(JL==2)
			{
				for(int i=0;i<shuzu;i++)
				{
					printf("温湿度%d度%d%%\r\n",kk[i][0],kk[i][1]);
					printf("当前时间:%d-%d-%d\r\n",kk[i][2], kk[i][3], kk[i][4]);
				}
				JL=0;
			}
			if(T>Up)
			{
				led1++;
				if(led1==200) led1=0;
				if(led1%2==0) LED_Control(1,0);
				if(led1%2==1) LED_Control(1,1);
			}
			else
			{
				LED_Control(1,0);
			}
			if(H>Down)
			{
				led2++;
				if(led2==200) led2=0;
				if(led2%2==0) LED_Control(2,0);
				if(led2%2==1) LED_Control(2,1);
			}
			else
			{
				LED_Control(2,0);
			}
			LCD_DisplayStringLine(Line1 ,(unsigned char *)"   real time data   ");
			sprintf((char *)A,"Current temp:%.0fC      ",T );
			LCD_DisplayStringLine(Line3 ,(unsigned char *)A);
			sprintf((char *)A,"Current humidity:%.0f%%      ",H );
			LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
			sprintf((char*)A,"Time:%0.2d-%0.2d-%0.2d         ",THH, TMM, TSS);
	    LCD_DisplayStringLine(Line7,(unsigned char *)A);
			sprintf((char*)A,"   Record times :%d         ",Ci);
	    LCD_DisplayStringLine(Line9,(unsigned char *)A);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
		}
		while(m%2==1)
		{
			
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0);
			  n++;
			}
			if(JL==1)
			{
				printf("当前温湿度阈值:%d度%d%%",Up,Down);
				printf("当前时间:%d-%d-%d",THH, TMM, TSS);
				JL=0;
			}
			if(JL==2)
			{
				for(int i=0;i<=shuzu;i++)
				{
					printf("温湿度%d度%d%%\r\n",kk[i][0],kk[i][1]);
					printf("当前时间:%d-%d-%d\r\n",kk[i][2], kk[i][3], kk[i][4]);
				}
				JL=0;
			}
			if(T>Up)
			{
				led1++;
				if(led1==200) led1=0;
				if(led1%2==0) LED_Control(1,0);
				if(led1%2==1) LED_Control(1,1);
			}
			else
			{
				LED_Control(1,0);
			}
			if(H>Down)
			{
				led2++;
				if(led2==200) led2=0;
				if(led2%2==0) LED_Control(2,0);
				if(led2%2==1) LED_Control(2,1);
			}
			else
			{
				LED_Control(2,0);
			}
			while(n%4==0)
			{
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
					Up++;
				}
				T=24.4*Average_h(ADC_Conf)-20;
			  if(T<=-19)  T=-20;
				CCR2_Val=18000/Xin;
				H=0.0089*TIM3Freq+1.1111;
				if(JL==1)
				{
					printf("当前温湿度阈值:%d度%d%%",Up,Down);
					printf("当前时间:%d-%d-%d",THH, TMM, TSS);
					JL=0;
				}
				if(JL==2)
				{
					for(int i=0;i<shuzu;i++)
					{
						printf("温湿度%d度%d%%\r\n",kk[i][0],kk[i][1]);
						printf("当前时间:%d-%d-%d\r\n",kk[i][2], kk[i][3], kk[i][4]);
					}
					JL=0;
				}
				if(T>Up)
				{
					led1++;
					if(led1==200) led1=0;
					if(led1%2==0) LED_Control(1,0);
					if(led1%2==1) LED_Control(1,1);
				}
				else
			{
				LED_Control(1,0);
			}
			if(H>Down)
			{
				led2++;
				if(led2==200) led2=0;
				if(led2%2==0) LED_Control(2,0);
				if(led2%2==1) LED_Control(2,1);
			}
			else
			{
				LED_Control(2,0);
			}
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
					Up--;
				}
				IIC_WriteOneData(20,Up);
				IIC_WriteOneData(21,Down);
				IIC_WriteOneData(22,Jian);
				p=(u8*)&Xin;
				for(int i=0;i<4;i++)
				{
					IIC_WriteOneData(i+1,*(p+i));
				}
				LCD_SetTextColor(Red);
				sprintf((char *)A,"Upper limit:%dC      ",Up );
			  LCD_DisplayStringLine(Line3 ,(unsigned char *)A);
				LCD_SetTextColor(White);
				sprintf((char *)A,"Lower limit:%d%%      ",Down );
			  LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
			  sprintf((char *)A,"Sampling   :%dS      ",Jian );
			  LCD_DisplayStringLine(Line7 ,(unsigned char *)A);
			  sprintf((char *)A,"test signal:%.1fKHz      ",Xin );
			  LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
			}
			while(n%4==1)
			{
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
					Down++;
					if(Down>=100)Down=100;
				}
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
					Down--;
					if(Down<=0)Down=0;
				}
				T=24.4*Average_h(ADC_Conf)-20;
			  if(T<=-19)  T=-20;
				CCR2_Val=18000/Xin;
				H=0.0089*TIM3Freq+1.1111;
				if(JL==1)
				{
					printf("当前温湿度阈值:%d度%d%%",Up,Down);
					printf("当前时间:%d-%d-%d",THH, TMM, TSS);
					JL=0;
				}
				if(JL==2)
				{
					for(int i=0;i<shuzu;i++)
					{
						printf("温湿度%d度%d%%\r\n",kk[i][0],kk[i][1]);
						printf("当前时间:%d-%d-%d\r\n",kk[i][2], kk[i][3], kk[i][4]);
					}
					JL=0;
				}
				if(T>Up)
				{
					led1++;
					if(led1==200) led1=0;
					if(led1%2==0) LED_Control(1,0);
					if(led1%2==1) LED_Control(1,1);
				}
				else
				{
					LED_Control(1,0);
				}
				if(H>Down)
				{
					led2++;
					if(led2==200) led2=0;
					if(led2%2==0) LED_Control(2,0);
					if(led2%2==1) LED_Control(2,1);
				}
				else
				{
					LED_Control(2,0);
				}
				IIC_WriteOneData(20,Up);
				IIC_WriteOneData(21,Down);
				IIC_WriteOneData(22,Jian);
				p=(u8*)&Xin;
				for(int i=0;i<4;i++)
				{
					IIC_WriteOneData(i+1,*(p+i));
				}
				LCD_SetTextColor(Red);
				sprintf((char *)A,"Lower limit:%d%%      ",Down );
			  LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
				LCD_SetTextColor(White);
				sprintf((char *)A,"Upper limit:%dC      ",Up );
			  LCD_DisplayStringLine(Line3 ,(unsigned char *)A);
			  sprintf((char *)A,"Sampling   :%dS      ",Jian );
			  LCD_DisplayStringLine(Line7 ,(unsigned char *)A);
			  sprintf((char *)A,"test signal:%.1fKHz      ",Xin );
			  LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
			}
			while(n%4==2)
			{
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
					Jian++;
					if(Jian>=5)Jian=5;
				}
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
					Jian--;
					if(Jian<=1)Jian=1;
				}
				baibai=Jian*900;
				T=24.4*Average_h(ADC_Conf)-20;
			  if(T<=-19)  T=-20;
				CCR2_Val=18000/Xin;
				H=0.0089*TIM3Freq+1.1111;
				if(JL==1)
				{
					printf("当前温湿度阈值:%d度%d%%",Up,Down);
					printf("当前时间:%d-%d-%d",THH, TMM, TSS);
					JL=0;
				}
				if(JL==2)
				{
					for(int i=0;i<shuzu;i++)
					{
						printf("温湿度%d度%d%%\r\n",kk[i][0],kk[i][1]);
						printf("当前时间:%d-%d-%d\r\n",kk[i][2], kk[i][3], kk[i][4]);
					}
					JL=0;
				}
				if(T>Up)
				{
					led1++;
					if(led1==200) led1=0;
					if(led1%2==0) LED_Control(1,0);
					if(led1%2==1) LED_Control(1,1);
				}
				else
				{
					LED_Control(1,0);
				}
				if(H>Down)
				{
					led2++;
					if(led2==200) led2=0;
					if(led2%2==0) LED_Control(2,0);
					if(led2%2==1) LED_Control(2,1);
				}
				else
				{
					LED_Control(2,0);
				}
				IIC_WriteOneData(20,Up);
				IIC_WriteOneData(21,Down);
				IIC_WriteOneData(22,Jian);
				p=(u8*)&Xin;
				for(int i=0;i<4;i++)
				{
					IIC_WriteOneData(i+1,*(p+i));
				}
				LCD_SetTextColor(Red);
				sprintf((char *)A,"Sampling   :%dS      ",Jian );
			  LCD_DisplayStringLine(Line7 ,(unsigned char *)A);
				LCD_SetTextColor(White);
				sprintf((char *)A,"Upper limit:%dC      ",Up );
			  LCD_DisplayStringLine(Line3 ,(unsigned char *)A);
			  sprintf((char *)A,"Lower limit:%d%%      ",Down );
			  LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
			  sprintf((char *)A,"test signal:%.1fKHz      ",Xin );
			  LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
			}
			while(n%4==3)
			{
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
					Xin+=0.5;
					if(Xin>=11)Xin=11;
				}
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
					Xin-=0.5;
					if(Xin<=0)Xin=0;
				}
				T=24.4*Average_h(ADC_Conf)-20;
			  if(T<=-19)  T=-20;
				CCR2_Val=18000/Xin;
				H=0.0089*TIM3Freq+1.1111;
				if(JL==1)
				{
					printf("当前温湿度阈值:%d度%d%%",Up,Down);
					printf("当前时间:%d-%d-%d",THH, TMM, TSS);
					JL=0;
				}
				if(JL==2)
				{
					for(int i=0;i<shuzu;i++)
					{
						printf("温湿度%d度%d%%\r\n",kk[i][0],kk[i][1]);
						printf("当前时间:%d-%d-%d\r\n",kk[i][2], kk[i][3], kk[i][4]);
					}
					JL=0;
				}
				if(T>Up)
				{
					led1++;
					if(led1==200) led1=0;
					if(led1%2==0) LED_Control(1,0);
					if(led1%2==1) LED_Control(1,1);
				}
				else
				{
					LED_Control(1,0);
				}
				if(H>Down)
				{
					led2++;
					if(led2==200) led2=0;
					if(led2%2==0) LED_Control(2,0);
					if(led2%2==1) LED_Control(2,1);
				}
				else
				{
					LED_Control(2,0);
				}
				IIC_WriteOneData(20,Up);
				IIC_WriteOneData(21,Down);
				IIC_WriteOneData(22,Jian);
				p=(u8*)&Xin;
				for(int i=0;i<4;i++)
				{
					IIC_WriteOneData(i+1,*(p+i));
				}
				LCD_SetTextColor(Red);
				sprintf((char *)A,"test signal:%.1fKHz      ",Xin );
			  LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
				LCD_SetTextColor(White);
				sprintf((char *)A,"Upper limit:%dC      ",Up );
			  LCD_DisplayStringLine(Line3 ,(unsigned char *)A);
			  sprintf((char *)A,"Sampling   :%dS      ",Jian );
			  LCD_DisplayStringLine(Line7 ,(unsigned char *)A);
				sprintf((char *)A,"Lower limit:%d%%      ",Down );
			  LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
			}
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
		}
	}
}


void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
