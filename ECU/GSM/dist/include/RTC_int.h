/*
 * RTC_int.h
 *
 *  Created on: Jun 10, 2020
 *      Author: lenovo
 */

#ifndef RTC_INT_H_
#define RTC_INT_H_

/****************************************/
/*********Public Definitions*************/
/****************************************/

/*****************************************/
/***********Public Functions**************/
/*****************************************/

/****************************************************************************************/
/* Description: Initialize RTC Peripheral.
 */
/* Input      : Void */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void RTC_vidInit(void);

/****************************************************************************************/
/* Description: Set Prescaler Value, set it to 0x7FFF to be 1 second period
 */
/* Input      : u32 u32Prescaler */
/*              Description: Clock Prescaler */
/* 				Range: 	0 ~ 1048575	 (20 bits)
 */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void RTC_vidSetPrescaler(u32 u32Prescaler);

/****************************************************************************************/
/* Description: Set Counter Value
 */
/* Input      : u32 u32Count */
/*              Description: Initial value of the counter
 */
/* 				Range: 	u32
 */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void RTC_vidSetCounter(u32 u32Count);

/****************************************************************************************/
/* Description: Get Counter Value
 */
/* Input      : Void */
/* Output     : u32 */
/*              Description: Current value of the counter
 */
/* Scope      : Public */
/****************************************************************************************/
u32 RTC_vidGetCounter(void);

/****************************************************************************************/
/* Description: Set Alarm Value
 */
/* Input      : u32 u32Alarm */
/*              Description: Value of the alarm
 */
/* 				Range: 	u32
 */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void RTC_vidSetAlarm(u32 u32Alarm);

#endif /* RTC_INT_H_ */
