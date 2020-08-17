#ifndef SYSTICK_INT_H
#define SYSTICK_INT_H

/*****************************************/
/***********Public Functions**************/
/*****************************************/

/************************************************************************************************/
/* Description: Initialize the Systick Peripheral
 */
/* Input      : u32 u32LoadCpy */
/*              Description: 24-bit value loaded to the Load Register to count
 * it down          */
/* 				Range: 	0 ~ 16777215
 */
/* Output     : Void */
/* Scope      : Public */
/************************************************************************************************/
void SYSTICK_vidInit(u32 u32LoadCpy);

/************************************************************************************************/
/* Description: Delay with ms
 */
/* Input      : u32 u32delayCpy */
/*              Description: Delay value in milliseconds
 */
/* 				Range: 	u32
 */
/* Output     : Void */
/* Scope      : Public */
/************************************************************************************************/
void _delay_ms(u32 u32delayCpy);

/************************************************************************************************/
/* Description: Systick Interrupt handler
 */
/* Input      : void (*phandler)(void) */
/*              Description: Pointer to interrupt handler
 */
/* Output     : Void */
/* Scope      : Public */
/************************************************************************************************/
void SYSTICK_vidSetCallback(void (*phandler)(void));

#endif
