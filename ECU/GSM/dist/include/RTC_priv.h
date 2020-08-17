/*
 * RTC_priv.h
 *
 *  Created on: Jun 10, 2020
 *      Author: lenovo
 */

#ifndef RTC_PRIV_H_
#define RTC_PRIV_H_

/***************************************/
/******** Private Definitions **********/
/***************************************/

/******** Register Declarations ************/
#define RTC_CRH (*((volatile u32 *)0x40002800))
#define RTC_CRL (*((volatile u32 *)0x40002804))
#define RTC_PRLH (*((volatile u16 *)0x40002808))
#define RTC_PRLL (*((volatile u16 *)0x4000280C))
#define RTC_DIVH (*((volatile u16 *)0x40002810))
#define RTC_DIVL (*((volatile u16 *)0x40002814))
#define RTC_CNTH (*((volatile u16 *)0x40002818))
#define RTC_CNTL (*((volatile u16 *)0x4000281C))
#define RTC_ALRH (*((volatile u16 *)0x40002820))
#define RTC_ALRL (*((volatile u16 *)0x40002824))

/*********** RTC_CRH Register Bits *******************/
#define RTC_SECIE 0
#define RTC_ALRIE 1
#define RTC_OWIE 2

/*********** RTC_CRL Register Bits *******************/
#define RTC_SECF 0
#define RTC_ALRF 1
#define RTC_OWF 2
#define RTC_RSF 3
#define RTC_CNF 4
#define RTC_RTOFF 5

/*********** Interrupt Enable/Disable Definitions *******************/
#define RTC_u8InterruptDisable 0
#define RTC_u8InterruptEnable 1
#endif /* RTC_PRIV_H_ */
