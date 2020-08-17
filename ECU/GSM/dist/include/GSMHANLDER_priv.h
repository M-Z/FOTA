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
//	MessageReceived,
	SendingMessage
}MessageState;


typedef enum
{
	/* Settings */
	DisableEcho,
	SetBearerParameters,
	OpenBearer,
	CloseBearer,

	/* Initialize HTTP */
	InitializeHTTP,
	TerminateHTTP,
	EnableSSL,

	/* Set HTTP Parameters */
	SetCID,
	EnableREDIR,

	/* POST Request */
	SetContentType,
	SetURL,
	SendHTTPData,
	SendVehicleName,
	POSTRequest,

	/* Read Received Data */
	GETSWVersion,

	/* Compare SW Versions */
	CompareSWVersion,

	/* User Acceptance from GUI */
	AcceptUpdate,

	/* Get The Hex File */
	GETHash,
	GETHexFile,
	CheckDecryption,
	SendFile,
	ReceiveFeedback,

	/* Diagnostics Session */
	SendDiag,


	Done
}Step;


/*****************************************/
/*********Private Functions	*************/
/*****************************************/


/****************************************************************************************/
/* Description: Send GSM command								 						*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidSendCommand(u8* pu8Command);


/****************************************************************************************/
/* Description: Send HTTP Data										 					*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidSendHTTPData(void);


/****************************************************************************************/
/* Description: Send Vehicle name and Password										 	*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidSendVehicleName(void);



/****************************************************************************************/
/* Description: Send PostRequest													 	*/
/* Input      : Void			                                                        */
/* Output     : u32			                                                            */
/*				Description: Received Data Size											*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
u32 u32SendPostRequest(void);



/****************************************************************************************/
/* Description: Gets Data after the HTTP request										*/
/* Input      : u32 u32StartPoint				                                        */
/*              Description: Start Point in the file to get the data from				*/
/* 				Range: 0 ~ u32															*/
/*				u16 u16DataLength														*/
/*              Description: Length of data to return									*/
/* 				Range: 0 ~ u32															*/
/*				u8* au8Data																*/
/*              Description: Array to return the data in								*/
/* Output     : u16			                                                            */
/*				Description: Length of the data returned								*/
/*				Range:0 ~ u16DataLength													*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
u16 u16GETData(u32 u32StartPoint, u16 u16DataLength, u8* au8Data);



/****************************************************************************************/
/* Description: Check if an update is available											*/
/* Input      : u8* au8Data																*/
/*              Description: Version from the server									*/
/* Output     : Void																	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void vidCheckUpdate(u8* au8Data);


/****************************************************************************************/
/* Description: Interrupt Handler for the DMA					 						*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidDMAIRQ(void);

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

Error_Status DMAListen(u8* pu8state);


#endif /* GSMHANLDER_PRIV_H_ */
