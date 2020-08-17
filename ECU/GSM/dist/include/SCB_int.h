/*
 * SCB_int.h
 *
 *  Created on: Jan 30, 2020
 *      Author: sondo
 */
/************************************************************************/
/* Author  : Sondos Aly	                                                */
/* Date    : 15/5/2020                                                  */
/* Version : V01	                                                    */
/************************************************************************/
/* Modification Log                                                     */
/* -----------------                                                    */
/*     Name     |    Version    |                 Changes               */
/*  Sondos 		        V01                      First Creation         */
/*  Sondos				V02					Added Interrupt Priorities	*/
/************************************************************************/

#ifndef SCB_INT_H_
#define SCB_INT_H_

/*****************************************/
/***********Public Definitions************/
/*****************************************/
#define SCB_u8MEMNGFAULT				0			//Memory Management fault
#define SCB_u8BUSFAULT					1			//Bus Fault
#define SCB_u8USAGEFAULT				2			//Usage Fault
#define SCB_u8SVCALL					7			//SVCall
#define SCB_u8PENDSV					10			//PendSV
#define SCB_u8SYSTICK					11			//TSystick Exception


/*****************************************/
/***********Public Functions**************/
/*****************************************/
/****************************************************************************************/
/* Description: Setting Interrupt Vector Table Base address	 							*/
/* Input      : u32 u32VTORBaseAddress                                                 	*/
/*              Description: Address to set the VTOR to			                        */
/* 				Range: 	u32																*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCB_vidSetInterruptVectorTable(u32 u32VTORBaseAddress);


/****************************************************************************************/
/* Description: Perform Soft Reset							 							*/
/* Input      : Void				                                                 	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCB_vidPerformSoftReset(void);


/****************************************************************************************/
/* Description: Set Interrupt Priorities of fault handlers							 	*/
/* Input      : u8 u8PeripheralIndex                                	               	*/
/*              Description: Peripheral to disable the NVIC for                        	*/
/* 				Range: 	SCB_u8MEMNGFAULT,		SCB_u8BUSFAULT,		SCB_u8USAGEFAULT	*/
/*						SCB_u8SVCALL,			SCB_u8PENDSV,		SCB_u8SYSTICK		*/
/*				u8 u8Priority                                	               			*/
/*              Description: Priority of Interrupt Handler	                        	*/
/* 				Range: 0 ~ 255															*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCB_vidSetInterruptPriority(u8 u8InterruptIndex, u8 u8Priority);

#endif /* SCB_INT_H_ */
