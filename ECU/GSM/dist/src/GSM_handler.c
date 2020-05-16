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

#include "GSM_priv.h"
#include "GSM_int.h"
#include "GSM_conf.h"

#include "crypto.h"
#include "Application.h"

u8 GSM_u8ListenFlag = OFF;
u8 au8listenBuffer[64];
u8 * pu8StatePtr;

extern u8 GSM_u8USARTChannel;
/***********************************************************************************************************************/
/********************************************Public Functions***********************************************************/
/***********************************************************************************************************************/
void GSM_handler(void)
{
	Error_Status responseStatus;
	static u8 u8state = 1;
	static u8 u8flag = 0;
	switch(u8state)
	{

	//Intialize GSM
	case 1:
		// Send ATEO Cmd
		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
		USART_voidSendString(GSM_u8USARTChannel, "ATE0");
		USART_voidSendString(GSM_u8USARTChannel, "\r\n");
		u8state++;
		break;
	case 2:
		//Listen on DMA buffer, waiting for "ok"
		responseStatus = DMAListen(&u8state);
		if (responseStatus == OK)
		{
			u8state++;
		}
		else if (responseStatus == NOK)
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
		responseStatus = DMAListen(&u8state);
		if (responseStatus == OK)
		{
			u8state++;
		}
		else if (responseStatus == NOK)
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
		responseStatus = DMAListen(&u8state);
		if (responseStatus == OK)
		{
			u8state++;
		}
		else if (responseStatus == NOK)
		{
			u8flag = 1;
			u8state--;
		}
		break;

	}
}


Error_Status DMAListen(void)
{
	GSM_u8ListenFlag = ON;

	//Check if the GSM terminate the buffer or not
	if(u8CheckBufferTermination(au8listenBuffer, 64, 2))
	{
		//check if the response is OK or NOK
		if (enuFindString(au8listenBuffer, "OK", 64) == OK)
		{
			// Response contain "OK"
			DMA_voidDisable(DMA_CHANNEL_5);
			GSM_u8ListenFlag = OFF;
			return OK;

		}
		else if(enuFindString(au8listenBuffer, "ERROR", 64) == OK)
		{
			// Response contain "ERROR"
			DMA_voidDisable(DMA_CHANNEL_5);
			GSM_u8ListenFlag = OFF;
			return NOK;
		}
		else
		{
			// Unknown respose
			DMA_voidDisable(DMA_CHANNEL_5);
			GSM_u8ListenFlag = OFF;
			//return unknown message
		}

	}
	return wait;
}

