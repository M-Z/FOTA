/*
 * SCH_priv.h
 *
 *  Created on: Oct 12, 2018
 *      Author: sondo
 */

#ifndef SCH_PRIV_H_
#define SCH_PRIV_H_




/**************************************/
/******* Private Functions ************/
/**************************************/
/***************************************************************************************/
/* Description: Scheduler Function							                           */
/* Input      : Void                                                                   */
/* Output     : Void                                                                   */
/* Scope      : Private                                                                */
/***************************************************************************************/
void Scheduler(void);

///***************************************************************************************/
///* Description: Systick Interrupt Handler Function							           */
///* Input      : Void                                                                   */
///* Output     : Void                                                                   */
///* Scope      : Private                                                                */
///***************************************************************************************/
//void SystickInterruptHandler(void);

/***************************************/
/******** Private Definitions **********/
/***************************************/

/* Overflow Counts Calculations */
#define OVF_COUNT	(u32)((TICK_TIME * 72000) - 1)




#endif /* SCH_PRIV_H_ */
