#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.7
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	 

//0,不支持ucos
//1,支持ucos
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持UCOS
																	    
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

//输出 
#define PAO0   (*((vu32*)(0x42210180 + 0*4)))
#define PAO1   (*((vu32*)(0x42210180 + 1*4)))
#define PAO2   (*((vu32*)(0x42210180 + 2*4)))
#define PAO3   (*((vu32*)(0x42210180 + 3*4)))
#define PAO4   (*((vu32*)(0x42210180 + 4*4)))
#define PAO5   (*((vu32*)(0x42210180 + 5*4)))
#define PAO6   (*((vu32*)(0x42210180 + 6*4)))
#define PAO7   (*((vu32*)(0x42210180 + 7*4)))
#define PAO8   (*((vu32*)(0x42210180 + 8*4)))
#define PAO9   (*((vu32*)(0x42210180 + 9*4)))
#define PAO10 (*((vu32*)(0x42210180 + 10*4)))
#define PAO11 (*((vu32*)(0x42210180 + 11*4)))
#define PAO12 (*((vu32*)(0x42210180 + 12*4)))
#define PAO13 (*((vu32*)(0x42210180 + 13*4)))
#define PAO14 (*((vu32*)(0x42210180 + 14*4)))
#define PAO15 (*((vu32*)(0x42210180 + 15*4)))

#define PBO0   (*((vu32*)(0x42218180 + 0*4)))
#define PBO1   (*((vu32*)(0x42218180 + 1*4)))
#define PBO2   (*((vu32*)(0x42218180 + 2*4)))
#define PBO3   (*((vu32*)(0x42218180 + 3*4)))
#define PBO4   (*((vu32*)(0x42218180 + 4*4)))
#define PBO5   (*((vu32*)(0x42218180 + 5*4)))
#define PBO6   (*((vu32*)(0x42218180 + 6*4)))
#define PBO7   (*((vu32*)(0x42218180 + 7*4)))
#define PBO8   (*((vu32*)(0x42218180 + 8*4)))
#define PBO9   (*((vu32*)(0x42218180 + 9*4)))
#define PBO10   (*((vu32*)(0x42218180 + 10*4)))
#define PBO11   (*((vu32*)(0x42218180 + 11*4)))
#define PBO12   (*((vu32*)(0x42218180 + 12*4)))
#define PBO13   (*((vu32*)(0x42218180 + 13*4)))
#define PBO14   (*((vu32*)(0x42218180 + 14*4)))
#define PBO15   (*((vu32*)(0x42218180 + 15*4)))

#define PCO0   (*((vu32*)(0x42220180 + 0*4)))
#define PCO1   (*((vu32*)(0x42220180 + 1*4)))
#define PCO2   (*((vu32*)(0x42220180 + 2*4)))
#define PCO3   (*((vu32*)(0x42220180 + 3*4)))
#define PCO4   (*((vu32*)(0x42220180 + 4*4)))
#define PCO5   (*((vu32*)(0x42220180 + 5*4)))
#define PCO6   (*((vu32*)(0x42220180 + 6*4)))
#define PCO7   (*((vu32*)(0x42220180 + 7*4)))
#define PCO8   (*((vu32*)(0x42220180 + 8*4)))
#define PCO9   (*((vu32*)(0x42220180 + 9*4)))
#define PCO10   (*((vu32*)(0x42220180 + 10*4)))
#define PCO11   (*((vu32*)(0x42220180 + 11*4)))
#define PCO12   (*((vu32*)(0x42220180 + 12*4)))
#define PCO13   (*((vu32*)(0x42220180 + 13*4)))
#define PCO14   (*((vu32*)(0x42220180 + 14*4)))
#define PCO15   (*((vu32*)(0x42220180 + 15*4)))

#define PDO0   (*((vu32*)(0x42228180 + 0*4)))
#define PDO1   (*((vu32*)(0x42228180 + 1*4)))
#define PDO2   (*((vu32*)(0x42228180 + 2*4)))
#define PDO3   (*((vu32*)(0x42228180 + 3*4)))
#define PDO4   (*((vu32*)(0x42228180 + 4*4)))
#define PDO5   (*((vu32*)(0x42228180 + 5*4)))
#define PDO6   (*((vu32*)(0x42228180 + 6*4)))
#define PDO7   (*((vu32*)(0x42228180 + 7*4)))
#define PDO8   (*((vu32*)(0x42228180 + 8*4)))
#define PDO9   (*((vu32*)(0x42228180 + 9*4)))
#define PDO10 (*((vu32*)(0x42228180 + 10*4)))
#define PDO11 (*((vu32*)(0x42228180 + 11*4)))
#define PDO12 (*((vu32*)(0x42228180 + 12*4)))
#define PDO13 (*((vu32*)(0x42228180 + 13*4)))
#define PDO14 (*((vu32*)(0x42228180 + 14*4)))
#define PDO15 (*((vu32*)(0x42228180 + 15*4)))

#define PEO0   (*((vu32*)(0x42230180 + 0*4)))
#define PEO1   (*((vu32*)(0x42230180 + 1*4)))
#define PEO2   (*((vu32*)(0x42230180 + 2*4)))
#define PEO3   (*((vu32*)(0x42230180 + 3*4)))
#define PEO4   (*((vu32*)(0x42230180 + 4*4)))
#define PEO5   (*((vu32*)(0x42230180 + 5*4)))
#define PEO6   (*((vu32*)(0x42230180 + 6*4)))
#define PEO7   (*((vu32*)(0x42230180 + 7*4)))
#define PEO8   (*((vu32*)(0x42230180 + 8*4)))
#define PEO9   (*((vu32*)(0x42230180 + 9*4)))
#define PEO10   (*((vu32*)(0x42230180 + 10*4)))
#define PEO11   (*((vu32*)(0x42230180 + 11*4)))
#define PEO12   (*((vu32*)(0x42230180 + 12*4)))
#define PEO13   (*((vu32*)(0x42230180 + 13*4)))
#define PEO14   (*((vu32*)(0x42230180 + 14*4)))
#define PEO15   (*((vu32*)(0x42230180 + 15*4)))

#define PFO0   (*((vu32*)(0x42238180 + 0*4)))
#define PFO1   (*((vu32*)(0x42238180 + 1*4)))
#define PFO2   (*((vu32*)(0x42238180 + 2*4)))
#define PFO3   (*((vu32*)(0x42238180 + 3*4)))
#define PFO4   (*((vu32*)(0x42238180 + 4*4)))
#define PFO5   (*((vu32*)(0x42238180 + 5*4)))
#define PFO6   (*((vu32*)(0x42238180 + 6*4)))
#define PFO7   (*((vu32*)(0x42238180 + 7*4)))
#define PFO8   (*((vu32*)(0x42238180 + 8*4)))
#define PFO9   (*((vu32*)(0x42238180 + 9*4)))
#define PFO10   (*((vu32*)(0x42238180 + 10*4)))
#define PFO11   (*((vu32*)(0x42238180 + 11*4)))
#define PFO12   (*((vu32*)(0x42238180 + 12*4)))
#define PFO13   (*((vu32*)(0x42238180 + 13*4)))
#define PFO14   (*((vu32*)(0x42238180 + 14*4)))
#define PFO15   (*((vu32*)(0x42238180 + 15*4)))

#define PGO0   (*((vu32*)(0x42240180 + 0*4)))
#define PGO1   (*((vu32*)(0x42240180 + 1*4)))
#define PGO2   (*((vu32*)(0x42240180 + 2*4)))
#define PGO3   (*((vu32*)(0x42240180 + 3*4)))
#define PGO4   (*((vu32*)(0x42240180 + 4*4)))
#define PGO5   (*((vu32*)(0x42240180 + 5*4)))
#define PGO6   (*((vu32*)(0x42240180 + 6*4)))
#define PGO7   (*((vu32*)(0x42240180 + 7*4)))
#define PGO8   (*((vu32*)(0x42240180 + 8*4)))
#define PGO9   (*((vu32*)(0x42240180 + 9*4)))
#define PGO10 (*((vu32*)(0x42240180 + 10*4)))
#define PGO11 (*((vu32*)(0x42240180 + 11*4)))
#define PGO12 (*((vu32*)(0x42240180 + 12*4)))
#define PGO13 (*((vu32*)(0x42240180 + 13*4)))
#define PGO14 (*((vu32*)(0x42240180 + 14*4)))
#define PGO15 (*((vu32*)(0x42240180 + 15*4)))

//输入
#define PAI0   (*((vu32*)(0x42210100 + 0*4)))
#define PAI1   (*((vu32*)(0x42210100 + 1*4)))
#define PAI2   (*((vu32*)(0x42210100 + 2*4)))
#define PAI3   (*((vu32*)(0x42210100 + 3*4)))
#define PAI4   (*((vu32*)(0x42210100 + 4*4)))
#define PAI5   (*((vu32*)(0x42210100 + 5*4)))
#define PAI6   (*((vu32*)(0x42210100 + 6*4)))
#define PAI7   (*((vu32*)(0x42210100 + 7*4)))
#define PAI8   (*((vu32*)(0x42210100 + 8*4)))
#define PAI9   (*((vu32*)(0x42210100 + 9*4)))
#define PAI10   (*((vu32*)(0x42210100 + 10*4)))
#define PAI11   (*((vu32*)(0x42210100 + 11*4)))
#define PAI12   (*((vu32*)(0x42210100 + 12*4)))
#define PAI13   (*((vu32*)(0x42210100 + 13*4)))
#define PAI14   (*((vu32*)(0x42210100 + 14*4)))
#define PAI15   (*((vu32*)(0x42210100 + 15*4)))

#define PBI0   (*((vu32*)(0x42218100 + 0*4)))
#define PBI1   (*((vu32*)(0x42218100 + 1*4)))
#define PBI2   (*((vu32*)(0x42218100 + 2*4)))
#define PBI3   (*((vu32*)(0x42218100 + 3*4)))
#define PBI4   (*((vu32*)(0x42218100 + 4*4)))
#define PBI5   (*((vu32*)(0x42218100 + 5*4)))
#define PBI6   (*((vu32*)(0x42218100 + 6*4)))
#define PBI7   (*((vu32*)(0x42218100 + 7*4)))
#define PBI8   (*((vu32*)(0x42218100 + 8*4)))
#define PBI9   (*((vu32*)(0x42218100 + 9*4)))
#define PBI10   (*((vu32*)(0x42218100 + 10*4)))
#define PBI11   (*((vu32*)(0x42218100 + 11*4)))
#define PBI12   (*((vu32*)(0x42218100 + 12*4)))
#define PBI13   (*((vu32*)(0x42218100 + 13*4)))
#define PBI14   (*((vu32*)(0x42218100 + 14*4)))
#define PBI15   (*((vu32*)(0x42218100 + 15*4)))

#define PCI0   (*((vu32*)(0x42220100 + 0*4)))
#define PCI1   (*((vu32*)(0x42220100 + 1*4)))
#define PCI2   (*((vu32*)(0x42220100 + 2*4)))
#define PCI3   (*((vu32*)(0x42220100 + 3*4)))
#define PCI4   (*((vu32*)(0x42220100 + 4*4)))
#define PCI5   (*((vu32*)(0x42220100 + 5*4)))
#define PCI6   (*((vu32*)(0x42220100 + 6*4)))
#define PCI7   (*((vu32*)(0x42220100 + 7*4)))
#define PCI8   (*((vu32*)(0x42220100 + 8*4)))
#define PCI9   (*((vu32*)(0x42220100 + 9*4)))
#define PCI10   (*((vu32*)(0x42220100 + 10*4)))
#define PCI11   (*((vu32*)(0x42220100 + 11*4)))
#define PCI12   (*((vu32*)(0x42220100 + 12*4)))
#define PCI13   (*((vu32*)(0x42220100 + 13*4)))
#define PCI14   (*((vu32*)(0x42220100 + 14*4)))
#define PCI15   (*((vu32*)(0x42220100 + 15*4)))

#define PDI0   (*((vu32*)(0x42228100 + 0*4)))
#define PDI1   (*((vu32*)(0x42228100 + 1*4)))
#define PDI2   (*((vu32*)(0x42228100 + 2*4)))
#define PDI3   (*((vu32*)(0x42228100 + 3*4)))
#define PDI4   (*((vu32*)(0x42228100 + 4*4)))
#define PDI5   (*((vu32*)(0x42228100 + 5*4)))
#define PDI6   (*((vu32*)(0x42228100 + 6*4)))
#define PDI7   (*((vu32*)(0x42228100 + 7*4)))
#define PDI8   (*((vu32*)(0x42228100 + 8*4)))
#define PDI9   (*((vu32*)(0x42228100 + 9*4)))
#define PDI10   (*((vu32*)(0x42228100 + 10*4)))
#define PDI11   (*((vu32*)(0x42228100 + 11*4)))
#define PDI12   (*((vu32*)(0x42228100 + 12*4)))
#define PDI13   (*((vu32*)(0x42228100 + 13*4)))
#define PDI14   (*((vu32*)(0x42228100 + 14*4)))
#define PDI15   (*((vu32*)(0x42228100 + 15*4)))

#define PEI0   (*((vu32*)(0x42230100 + 0*4)))
#define PEI1   (*((vu32*)(0x42230100 + 1*4)))
#define PEI2   (*((vu32*)(0x42230100 + 2*4)))
#define PEI3   (*((vu32*)(0x42230100 + 3*4)))
#define PEI4   (*((vu32*)(0x42230100 + 4*4)))
#define PEI5   (*((vu32*)(0x42230100 + 5*4)))
#define PEI6   (*((vu32*)(0x42230100 + 6*4)))
#define PEI7   (*((vu32*)(0x42230100 + 7*4)))
#define PEI8   (*((vu32*)(0x42230100 + 8*4)))
#define PEI9   (*((vu32*)(0x42230100 + 9*4)))
#define PEI10   (*((vu32*)(0x42230100 + 10*4)))
#define PEI11   (*((vu32*)(0x42230100 + 11*4)))
#define PEI12   (*((vu32*)(0x42230100 + 12*4)))
#define PEI13   (*((vu32*)(0x42230100 + 13*4)))
#define PEI14   (*((vu32*)(0x42230100 + 14*4)))
#define PEI15   (*((vu32*)(0x42230100 + 15*4)))

#define PFI0   (*((vu32*)(0x42238100 + 0*4)))
#define PFI1   (*((vu32*)(0x42238100 + 1*4)))
#define PFI2   (*((vu32*)(0x42238100 + 2*4)))
#define PFI3   (*((vu32*)(0x42238100 + 3*4)))
#define PFI4   (*((vu32*)(0x42238100 + 4*4)))
#define PFI5   (*((vu32*)(0x42238100 + 5*4)))
#define PFI6   (*((vu32*)(0x42238100 + 6*4)))
#define PFI7   (*((vu32*)(0x42238100 + 7*4)))
#define PFI8   (*((vu32*)(0x42238100 + 8*4)))
#define PFI9   (*((vu32*)(0x42238100 + 9*4)))
#define PFI10   (*((vu32*)(0x42238100 + 10*4)))
#define PFI11   (*((vu32*)(0x42238100 + 11*4)))
#define PFI12   (*((vu32*)(0x42238100 + 12*4)))
#define PFI13   (*((vu32*)(0x42238100 + 13*4)))
#define PFI14   (*((vu32*)(0x42238100 + 14*4)))
#define PFI15   (*((vu32*)(0x42238100 + 15*4)))

#define PGI0   (*((vu32*)(0x42240100 + 0*4)))
#define PGI1   (*((vu32*)(0x42240100 + 1*4)))
#define PGI2   (*((vu32*)(0x42240100 + 2*4)))
#define PGI3   (*((vu32*)(0x42240100 + 3*4)))
#define PGI4   (*((vu32*)(0x42240100 + 4*4)))
#define PGI5   (*((vu32*)(0x42240100 + 5*4)))
#define PGI6   (*((vu32*)(0x42240100 + 6*4)))
#define PGI7   (*((vu32*)(0x42240100 + 7*4)))
#define PGI8   (*((vu32*)(0x42240100 + 8*4)))
#define PGI9   (*((vu32*)(0x42240100 + 9*4)))
#define PGI10   (*((vu32*)(0x42240100 + 10*4)))
#define PGI11   (*((vu32*)(0x42240100 + 11*4)))
#define PGI12   (*((vu32*)(0x42240100 + 12*4)))
#define PGI13   (*((vu32*)(0x42240100 + 13*4)))
#define PGI14   (*((vu32*)(0x42240100 + 14*4)))
#define PGI15   (*((vu32*)(0x42240100 + 15*4)))


//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址

#endif
