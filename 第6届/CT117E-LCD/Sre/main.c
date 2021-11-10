#include "stm32f10x.h"
#include "lcd.h"
#include "tim2.h"
#include "pwm_toggle.h"
#include "misc.h" 
#include "key.h"
#include "led.h"
#include "i2c.h"
#include "usart2_it.h"
#include "stdio.h"

extern __IO uint16_t CCR1_Val,CCR2_Val;
u32 TimingDelay = 0;
extern __IO uint32_t TIM3Freq1;
extern __IO uint32_t TIM3Freq;
int A[50];
int J1=1,J2=0,J3=2,J4=2;
int Tong=1,Xun=0;
extern u8 Rcount,Rover;
extern u8 USAERT_buffer[20];
void Delay_Ms(u32 nTime);

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	Delay_Ms(200);
	STM3210B_LCD_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	USART2_Config();
	tim2_huo();
	toggle_Config();
	Key_Init();
	LED_Config();
	i2c_init();
	
	
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);

	SCQ_Init(0xffff);
	J3=IIC_ReadOneData(1);
	J4=IIC_ReadOneData(2);
	Delay_Ms(1000);
	while(1)
	{
		CCR1_Val=2000000/(J3*TIM3Freq);
	  CCR2_Val=2000000/(J4*TIM3Freq1);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
				J1++;
			}	
			while(J1%2==1)  //本地模式
			{
				USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
				USART_Cmd(USART2, DISABLE);
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
				{
					while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0);
					J2++;
				}
				while(J2%2==0)  //通道1
				{
					Tong=1;
					SCQ_Init(0xfeff);
					if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
						J3--;
						if(J3<=1) J3=1;
					}
					if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
						J3++;
						if(J3>=10) J3=10;
					}
					CCR1_Val=2000000/(J3*TIM3Freq);
					IIC_WriteOneData(1,J3);
					if(TIM3Freq<50||TIM3Freq>50000) 
					{
						GPIO_ResetBits(GPIOA,GPIO_Pin_6);
					}
					sprintf((char *)A,"Channel(1): %d    ",TIM3Freq);
					LCD_DisplayStringLine(Line1 ,(unsigned char *)A);
					sprintf((char *)A,"N(1): %d     ",J3);
					LCD_DisplayStringLine(Line3 ,(unsigned char *)A);	
					sprintf((char *)A,"Channel(2): %d     ",TIM3Freq1);
					LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
					sprintf((char *)A,"N(2): %d     ",J4);
					LCD_DisplayStringLine(Line7 ,(unsigned char *)A);
					sprintf((char *)A,"                 %d ",Tong);
					LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
				}
				
				while(J2%2==1)  //通道2
				{
					Tong=2;
					SCQ_Init(0xfdff);
					if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
						J4--;
						if(J4<=1) J4=1;
					}
					if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
					{
						while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
						J4++;
						if(J4>=10) J4=10;
					}
					CCR2_Val=2000000/(J4*TIM3Freq1);
					IIC_WriteOneData(2,J4);
					if(TIM3Freq1<50||TIM3Freq1>50000) 
					{
						GPIO_ResetBits(GPIOA,GPIO_Pin_7);
					}
					sprintf((char *)A,"Channel(1): %d     ",TIM3Freq);
					LCD_DisplayStringLine(Line1 ,(unsigned char *)A);
					sprintf((char *)A,"N(1): %d     ",J3);
					LCD_DisplayStringLine(Line3 ,(unsigned char *)A);	
					sprintf((char *)A,"Channel(2): %d     ",TIM3Freq1);
					LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
					sprintf((char *)A,"N(2): %d     ",J4);
					LCD_DisplayStringLine(Line7 ,(unsigned char *)A);
					sprintf((char *)A,"                 %d ",Tong);
					LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
					if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) break;
				}
			  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)  break;
			} 
			
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
				J1++;
			}	
			while(J1%2==0)
			{
				SCQ_Init(0xfbff); 
				USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
				USART_Cmd(USART2, ENABLE);
				
				if(Rover==1)
				{
					if(USAERT_buffer[0]=='S'&&USAERT_buffer[1]=='E'&&USAERT_buffer[2]=='T')
					{
						if(USAERT_buffer[4]=='1') 
						{
							Tong=1;
							J3=((int)USAERT_buffer[6]-48)*10+((int)USAERT_buffer[7]-48);
							if(J3<=2) J3=2;
							if(J3>=10) J3=10;
							CCR1_Val=2000000/(J3*TIM3Freq);
							IIC_WriteOneData(1,J3);
							if(TIM3Freq<50||TIM3Freq>50000) 
							{
								GPIO_ResetBits(GPIOA,GPIO_Pin_6);
							}	
						}
						if(USAERT_buffer[4]=='2') 
						{
							Tong=2;
							J4=((int)USAERT_buffer[6]-48)*10+((int)USAERT_buffer[7]-48);
							if(J4<=2) J4=2;
							if(J4>=10) J4=10;
							CCR2_Val=2000000/(J4*TIM3Freq1);
							IIC_WriteOneData(2,J4);
							if(TIM3Freq1<50||TIM3Freq1>50000) 
							{
								GPIO_ResetBits(GPIOA,GPIO_Pin_7);
							}	
						}	
					}
					Rover=0;
				}
				for(Xun=0;Xun<10;Xun++)
				{
					USAERT_buffer[Xun]=0;
				}
				sprintf((char *)A,"Channel(1): %d     ",TIM3Freq);
				LCD_DisplayStringLine(Line1 ,(unsigned char *)A);
				sprintf((char *)A,"N(1): %d     ",J3);
				LCD_DisplayStringLine(Line3 ,(unsigned char *)A);	
				sprintf((char *)A,"Channel(2): %d     ",TIM3Freq1);
				LCD_DisplayStringLine(Line5 ,(unsigned char *)A);
				sprintf((char *)A,"N(2): %d     ",J4);
				LCD_DisplayStringLine(Line7 ,(unsigned char *)A);
				sprintf((char *)A,"                 %d ",Tong);
				LCD_DisplayStringLine(Line9 ,(unsigned char *)A);
				if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)  break;
			}
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
