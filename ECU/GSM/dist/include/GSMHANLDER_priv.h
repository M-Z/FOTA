/*
 * GSMHANLDER_priv.h
 *
 *  Created on: May 16, 2020
 *      Author: lenovo
 */

#ifndef GSMHANLDER_PRIV_H_
#define GSMHANLDER_PRIV_H_


/*****************************************/
/*********Private Definitions*************/
/*****************************************/

typedef enum
{
	IDLE,
	WaitingForMessage,
//	MessageReceived
}RecieveState;



/*****************************************/
/*********Private Functions	*************/
/*****************************************/

/****************************************************************************************/
/* Description: Interrupt Handler for the DMA					 						*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidDMAIRQ(void);


/****************************************************************************************/
/* Description: Finds the expected string in the buffer 								*/
/* Input      : u8* pu8Buffer                                                           */
/*              Description: Array to search for the string in			                */
/* 				Range: 	pointer to u8													*/
/*				const u8* pu8ExpectedString												*/
/*              Description: String to search for in the Buffer			                */
/* 				Range: 	pointer to u8													*/
/*				u32 u32Size																*/
/*              Description: Size of the array we are searching in				        */
/* 				Range: 	u32																*/
/* Output     : Error_Status                                                            */
/*				Range: OK if the string is found, NOK if the string isn't found			*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
static Error_Status enuFindString(u8* pu8Buffer, const u8* pu8ExpectedString, u32 u32Size);

Error_Status DMAListen(u8* pu8state);


#endif /* GSMHANLDER_PRIV_H_ */
