#include "STD_Types.h"
#include "util.h"
#include "SYSTICK_priv.h"
#include "SYSTICK_int.h"

volatile u32 u32delay;

void (*InterruptCallback)(void) = &vidInterruptStub;


/*****************************************/
/***********Public Functions**************/
/*****************************************/

/************************************************************************************************/
/* Description: Initialize the Systick Peripheral												*/
/* Input      : u32 u32LoadCpy		                                	        				*/
/*              Description: 24-bit value loaded to the Load Register to count it down          */
/* 				Range: 	0 ~ 16777215															*/
/* Output     : Void                                                                  		 	*/
/* Scope      : Public                                                                 			*/
/************************************************************************************************/
void SYSTICK_vidInit(u32 u32LoadCpy)
{
	//load value to load register
	SYSTICK_LOAD = u32LoadCpy & 0x00FFFFFF;
	//reset value register, also resetting the count flag
	SYSTICK_VAL = 0;
	//Enbale timer, enable interrupt, select HSI as clock source
	SYSTICK_CTRL = 0x07;
}


/************************************************************************************************/
/* Description: Delay with ms																	*/
/* Input      : u32 u32delayCpy		                                	        				*/
/*              Description: Delay value in milliseconds								        */
/* 				Range: 	u32																		*/
/* Output     : Void                                                                  		 	*/
/* Scope      : Public                                                                 			*/
/************************************************************************************************/
void _delay_ms(u32 u32delayCpy)
{
	u32delay = u32delayCpy;
	while (u32delay != 0);
}



/************************************************************************************************/
/* Description: Systick Interrupt handler														*/
/* Input      : void (*phandler)(void)		                                	        		*/
/*              Description: Pointer to interrupt handler								        */
/* Output     : Void                                                                  		 	*/
/* Scope      : Public                                                                 			*/
/************************************************************************************************/
void SYSTICK_vidSetCallback(void (*phandler)(void))
{
	InterruptCallback = phandler;
}



/******************************************/
/***********Private Functions**************/
/******************************************/
void vidInterruptStub(void)
{
	__asm__("NOP");
}



void __attribute__ ((section(".after_vectors"),weak))
SysTick_Handler (void)
{
  // DO NOT loop, just return.
  // Useful in case someone (like STM HAL) inadvertently enables SysTick.
	InterruptCallback();
}

