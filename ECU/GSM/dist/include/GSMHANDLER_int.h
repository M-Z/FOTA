/*
 * GSMHANDLER_int.h
 *
 *  Created on: May 16, 2020
 *      Author: lenovo
 */

#ifndef GSMHANDLER_INT_H_
#define GSMHANDLER_INT_H_


extern u8 GSMHANDLER_u8GSMBusy;

/*****************************************/
/*********Public Definitions*************/
/*****************************************/



/*****************************************/
/***********Public Functions**************/
/*****************************************/

/****************************************************************************************/
/* Description: GSM Task in the Scheduler												*/
/* Input      : Void					                                                */
/* Output     : Void		                                                            */
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void GSMHANDLER_vidTask(void);



/****************************************************************************************/
/* Description: Start Diagnostics Send to Server										*/
/* Input      : Void					                                                */
/* Output     : Void		                                                            */
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void GSMHANDLER_vidStartDiag(void);

#endif /* GSMHANDLER_INT_H_ */
