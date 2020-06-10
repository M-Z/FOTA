/*
 * RTC_cfg.h
 *
 *  Created on: Jun 10, 2020
 *      Author: lenovo
 */

#ifndef RTC_CFG_H_
#define RTC_CFG_H_


/* Description:	One Second Interrupt Enable									*/
/* Range:		RTC_u8InterruptEnable,	RTC_u8InterruptDisable				*/
#define RTC_u8SECIE		RTC_u8InterruptDisable


/* Description:	Alarm Interrupt Enable										*/
/* Range:		RTC_u8InterruptEnable,	RTC_u8InterruptDisable				*/
#define RTC_u8ALRIE		RTC_u8InterruptDisable


/* Description:	Overflow Interrupt Enable									*/
/* Range:		RTC_u8InterruptEnable,	RTC_u8InterruptDisable				*/
#define RTC_u8OWIE		RTC_u8InterruptDisable


#endif /* RTC_CFG_H_ */
