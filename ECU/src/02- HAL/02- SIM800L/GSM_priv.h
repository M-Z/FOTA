/*
 * GSM_priv.h
 *
 *  Created on: 25 Sep 2019
 *      Author: Mario
 */

#ifndef GSM_PRIV_H_
#define GSM_PRIV_H_

/******************************************/
/***********Private Functions**************/
/******************************************/



/****************************************************************************************/
/* Description: Interrupt Handler for the DMA					 						*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidDMAInterruptHandler(void);


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




/****************************************************************************************/
/* Description: Checks to see if GSM finished sending \r\n 								*/
/* Input      : u8* pu8Buffer                                                           */
/*              Description: The DMA buffer to check in					                */
/* 				Range: 	pointer to u8													*/
/*				u32 u32BufferSize														*/
/*              Description: Size of the Buffer							                */
/* 				Range: 	u32																*/
/*				u8 u8TerminationOccurences												*/
/*              Description: Number of occurrences we are expecting				        */
/* 				Range: 	u8																*/
/* Output     : u8        			                                                    */
/*				Range: 0 if termination is not done, 1 if termination is done			*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
static u8 u8CheckBufferTermination(u8* pu8Buffer, u32 u32BufferSize, u8 u8TerminationOccurences);


/****************************************************************************************/
/* Description: Sends Command through UART and wait for response "\r\nOK\r\n"			*/
/* Input      : const u8* pu8Command                                                    */
/*              Description: Command to be sent							                */
/* 				Range: 	pointer to u8													*/
/* Output     : Error_Status        			                                        */
/*				Range: NOK if "\r\nOK\r\n is not received, OK if "\r\nOK\r\n is received*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
static Error_Status enuSendCommand(const u8* pu8Command);



/****************************************************************************************/
/* Description: Clears the data in the Buffer and replace it with zeros					*/
/* Input      : u8* pu8Buffer		                                                    */
/*              Description: Buffer to be cleard							            */
/* 				Range: 	pointer to u8													*/
/*				u32 u32BufferLength														*/
/*              Description: Size of the buffer to be cleared							*/
/* 				Range: 	u32																*/
/* Output     : Void																	*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
static void vidClearBuffer(u8* pu8Buffer, u32 u32BufferLength);



#endif /* GSM_PRIV_H_ */
