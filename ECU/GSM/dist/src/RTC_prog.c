/*
 * RTC_prog.c
 *
 *  Created on: Jun 10, 2020
 *      Author: lenovo
 */

#include "STD_Types.h"
#include "util.h"
#include "RTC_priv.h"
#include "RTC_cfg.h"
#include "RTC_int.h"


/****************************************************************************************/
/* Description: Initialize RTC Peripheral. 											 	*/
/* Input      : Void                                                                   	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void RTC_vidInit(void)
{
	SET_BIT(RTC_CRL,RTC_RSF);
	/* Wait for synchronization flag */
	while (GET_BIT(RTC_CRL,RTC_RSF) == 0);
	/* Wait for RTCOFF flag */
	while (GET_BIT(RTC_CRL,RTC_RTOFF) == 0);

	/* Set the interrupt bits */
	RTC_CRH |= ((RTC_u8SECIE) | (RTC_u8ALRIE << RTC_ALRIE) | (RTC_u8OWIE << RTC_OWIE));
}


/****************************************************************************************/
/* Description: Set Prescaler Value, set it to 0x7FFF to be 1 second period 			*/
/* Input      : u32 u32Prescaler                                                       	*/
/*              Description: Clock Prescaler					                        */
/* 				Range: 	0 ~ 1048575	 (20 bits)											*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void RTC_vidSetPrescaler(u32 u32Prescaler)
{
	/* Wait for RTCOFF flag */
	while (GET_BIT(RTC_CRL,RTC_RTOFF) == 0);

	/* Enter Configuration Mode */
	SET_BIT(RTC_CRL, RTC_CNF);

	/* Set prescaler value */
	RTC_PRLL = (u32Prescaler & 0x00000000FFFFFFFF);
	RTC_PRLH = ((u32Prescaler >> 16) & 0x000000000000000F);

	CLR_BIT(RTC_CRL, RTC_CNF);
}



/****************************************************************************************/
/* Description: Set Counter Value														*/
/* Input      : u32 u32Count                                                    	   	*/
/*              Description: Initial value of the counter					            */
/* 				Range: 	u32																*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void RTC_vidSetCounter(u32 u32Count)
{
	/* Wait for RTCOFF flag */
	while (GET_BIT(RTC_CRL,RTC_RTOFF) == 0);

	/* Enter Configuration Mode */
	SET_BIT(RTC_CRL, RTC_CNF);

	/* Set prescaler value */
	RTC_CNTL = (u32Count & 0x00000000FFFFFFFF);
	RTC_CNTH = ((u32Count >> 16) & 0x00000000FFFFFFFF);

	CLR_BIT(RTC_CRL, RTC_CNF);

}


/****************************************************************************************/
/* Description: Get Counter Value														*/
/* Input      : Void		                                                    	   	*/
/* Output     : u32                                                                   	*/
/*              Description: Current value of the counter					            */
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
u32 RTC_vidGetCounter(void)
{
	u32 u32temp = 0;

	/* Get counter value */
	u32temp = (RTC_CNTL | (RTC_CNTH << 16));

	return u32temp;
}


/****************************************************************************************/
/* Description: Set Alarm Value															*/
/* Input      : u32 u32Alarm                                                    	   	*/
/*              Description: Value of the alarm						           			*/
/* 				Range: 	u32																*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void RTC_vidSetAlarm(u32 u32Alarm)
{
	/* Wait for RTCOFF flag */
	while (GET_BIT(RTC_CRL,RTC_RTOFF) == 0);

	/* Enter Configuration Mode */
	SET_BIT(RTC_CRL, RTC_CNF);

	/* Set prescaler value */
	RTC_ALRL = (u32Alarm & 0x00000000FFFFFFFF);
	RTC_ALRH = ((u32Alarm >> 16) & 0x00000000FFFFFFFF);

	CLR_BIT(RTC_CRL, RTC_CNF);

}
