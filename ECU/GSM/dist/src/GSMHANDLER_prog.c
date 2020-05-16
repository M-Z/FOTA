/*
 * GSM_handler.c
 *
 *  Created on: 15 May 2020
 *      Author: Michael
 */

#include "STD_Types.h"
#include "BIT_MATH.h"

#include "RCC_int.h"
#include "NVIC_int.h"
#include "USART_int.h"
#include "DMA_int.h"

//#include "GSM_priv.h"
#include "GSM_int.h"
#include "GSM_conf.h"

#include "GSMHANLDER_priv.h"
#include "GSMHANDLER_int.h"

#include "crypto.h"
#include "Application.h"

RecieveState GSM_enuListenFlag = IDLE;
u8 au8listenBuffer[64];
u8 * pu8StatePtr;
u8 GSMHANDLER_u8TransmissionCompleteFlag = 0;

/*****************************************/
/***********Public Functions**************/
/*****************************************/

/****************************************************************************************/
/* Description: GSM Task in the Scheduler												*/
/* Input      : Void					                                                */
/* Output     : Void		                                                            */
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void GSMHANDLER_vidTask(void)
{
	Error_Status enuresponseStatus = NOK;
	static u8 u8state = 1;
	static u8 u8flag = 0;
	switch(u8state)
	{

	//Intialize GSM
	case 1:
		// Send ATEO Cmd
		switch (GSM_enuListenFlag)
		{
		case IDLE:
			DMA_enumSetCallback(DMA_CHANNEL_4,vidDMAIRQ);
			USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
			USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "ATE0\r\n", 0 );
			GSM_enuListenFlag = WaitingForMessage;
			break;
		case WaitingForMessage:
			/* Reset The transmission flag if the transmission is done */
			if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
			{
				GSMHANDLER_u8TransmissionCompleteFlag = 0;
			}
			else
			{
				/* Check for OK response */
				enuresponseStatus = enuFindString(au8listenBuffer,"\r\n\OK\r\n",64);
				if (enuresponseStatus == OK)
				{
					u8state++;
				}
				else
				{
					/* Check for Error Response */
					enuresponseStatus = enuFindString(au8listenBuffer,"\r\n\ERROR\r\n",64);
					if (enuresponseStatus == OK)
					{
						GSM_enuListenFlag = IDLE;
					}
					else
					{
						/* Do Nothing */
					}
				}
			}
			break;

		default:
			break;
		}
		break;

		//		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
		//		USART_voidSendString(GSM_u8USARTChannel, "ATE0");
		//		USART_voidSendString(GSM_u8USARTChannel, "\r\n");
		//		u8state++;
		//		}
		//		break;
		case 2:
			//Listen on DMA buffer, waiting for "ok"
			enuresponseStatus = DMAListen(&u8state);
			if (enuresponseStatus == OK)
			{
				u8state++;
			}
			else if (enuresponseStatus == NOK)
			{
				u8state--;
			}
			break;
		case 3:
			USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
			USART_voidSendString(GSM_u8USARTChannel, "AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
			USART_voidSendString(GSM_u8USARTChannel, "\r\n");
			u8state++;
			break;
		case 4:
			//Listen on DMA buffer, waiting for "OK" or "Error"
			enuresponseStatus = DMAListen(&u8state);
			if (enuresponseStatus == OK)
			{
				u8state++;
			}
			else if (enuresponseStatus == NOK)
			{
				u8state--;
			}
			break;
		case 5:
			USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
			if(u8flag == 0)
			{
				USART_voidSendString(GSM_u8USARTChannel, "AT+SAPBR=1,1");
			}
			else if( u8flag == 1)
			{
				u8flag == 0;
				USART_voidSendString(GSM_u8USARTChannel, "AT+SAPBR=0,1");

			}
			USART_voidSendString(GSM_u8USARTChannel, "\r\n");
			u8state++;

			break;
		case 6:
			//Listen on DMA buffer, waiting for "OK" or "Error"
			enuresponseStatus = DMAListen(&u8state);
			if (enuresponseStatus == OK)
			{
				u8state++;
			}
			else if (enuresponseStatus == NOK)
			{
				u8flag = 1;
				u8state--;
			}
			break;

	}
}


/****************************************************************************************/
/* Description: Interrupt Handler for the DMA					 						*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidDMAIRQ(void)
{
	GSMHANDLER_u8TransmissionCompleteFlag = 1;
}


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
static Error_Status enuFindString(u8* pu8Buffer, const u8* pu8ExpectedString, u32 u32Size)
{
	u32 u32MessageCounter = 0;
	u32 u32StringStartIndex = 0;
	u32 u32StringCounter = 0;
	u8 u8FoundFlag = 1;

	// Loop through the pu8Buffer
	for (u32 u32StringStartIndex = 0; u32StringStartIndex < u32Size; u32StringStartIndex++)
	{
		// If match occurred
		if (pu8Buffer[u32StringStartIndex] == pu8ExpectedString[0])
		{
			u32MessageCounter = 1;
			u8FoundFlag = 1;
			// Loop through the message
			for (u32 u32StringCounter = u32StringStartIndex + 1; pu8ExpectedString[u32MessageCounter] != '\0'; u32StringCounter++)
			{
				if (pu8ExpectedString[u32MessageCounter] != pu8Buffer[u32StringCounter])
				{
					u8FoundFlag = 0;
					break;
				}
				u32MessageCounter++;
			}

			// If all match found and we have checked all the message
			if ((u8FoundFlag == 1) && (pu8ExpectedString[u32MessageCounter] == '\0'))
			{
				return OK;
			}
		}
	}

	return NOK;
}

//Error_Status DMAListen(u8* pu8state)
//{
//	GSM_u8ListenFlag = ON;
//
//	//Check if the GSM terminate the buffer or not
//	if(u8CheckBufferTermination(au8listenBuffer, 64, 2))
//	{
//		//check if the response is OK or NOK
//		if (enuFindString(au8listenBuffer, "OK", 64) == OK)
//		{
//			// Response contain "OK"
//			DMA_voidDisable(DMA_CHANNEL_5);
//			GSM_u8ListenFlag = OFF;
//			return OK;
//
//		}
//		else if(enuFindString(au8listenBuffer, "ERROR", 64) == OK)
//		{
//			// Response contain "ERROR"
//			DMA_voidDisable(DMA_CHANNEL_5);
//			GSM_u8ListenFlag = OFF;
//			return NOK;
//		}
//		else
//		{
//			// Unknown respose
//			DMA_voidDisable(DMA_CHANNEL_5);
//			GSM_u8ListenFlag = OFF;
//			//return unknown message
//		}
//
//	}
//	return wait;
//}
//
