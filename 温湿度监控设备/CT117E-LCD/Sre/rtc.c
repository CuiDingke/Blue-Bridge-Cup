#include "stm32f10x.h"
#include "rtc.h"
#include "lcd.h"
//#include "led.h"
uint32_t THH = 0, TMM = 0, TSS = 0;
uint32_t TimeVar=86399;
uint8_t aa[50];

void RTC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSICmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET){}
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask();
	RTC_SetPrescaler(40000);
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC, ENABLE);	
	RTC_SetCounter(0x0);
	RTC_WaitForLastTask();	
		
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);		
}

void Time_Display(void)
{
  if (RTC_GetCounter() == 0x0001517F)
  {
	RTC_SetCounter(0x0);
	RTC_WaitForLastTask();
  }
  
	THH = TimeVar / 3600;
	TMM = (TimeVar % 3600) / 60;
	TSS = (TimeVar % 3600) % 60;

}

void RTC_IRQHandler(void)
{
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
	TimeVar++;
	if(TimeVar==86400) TimeVar=0;
	Time_Display();
//	Zt=GPIO_ReadInputData(GPIOC);
	
//	SCQ_Init(Zt);
	RTC_ClearITPendingBit(RTC_IT_SEC);
	RTC_WaitForLastTask();
  }
}

