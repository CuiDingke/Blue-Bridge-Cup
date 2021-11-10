#include "usart2_it.h"
#include "misc.h"
#include "stdio.h"
//u8 USAERT_buffer[20];
//u8 Rcount=0,Rover=0;
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx ;
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (unsigned char) ch);
	while (!(USART2->SR & USART_FLAG_TXE));
	
	return (ch);
}


//void USART2_IRQHandler(void)
//{
//	 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//	 {
//		 USART_ClearITPendingBit( USART2, USART_IT_RXNE);
//		 USAERT_buffer[Rcount++]=USART_ReceiveData( USART2);
//	     if((USAERT_buffer[Rcount]=='x')||(Rcount==20))
//		 {
//			 Rcount=0;
//			 Rover=1;
//			 USART_ITConfig(USART2, USART_IT_RXNE,DISABLE);
//		 }
//	 }
//}



//void USART2_SendData(u8 *str)
//{
//	uint8_t index=0;
//	do 
//	{ 
//		USART_SendData( USART2,str[index] );
//		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
//		index++;	
//	}
//	while(str[index]!=0);
//}
