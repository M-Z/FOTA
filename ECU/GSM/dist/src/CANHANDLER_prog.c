/*
 * CANHANDLER_prog.c
 *
 *  Created on: Feb 5, 2020
 *      Author: sondo
 */


#include "util.h"
#include "STD_Types.h"
#include "CAN.h"
#include "CANHANDLER_int.h"
#include "CANHANDLER_cfg.h"



/*****************************************/
/***********Public Functions**************/
/*****************************************/
/****************************************************************************************/
/* Description: Send Can Message 							 							*/
/* Input      : u8 u8MessageID		                                                	*/
/*              Description: ID of the message to send over CAN			                */
/* 				Range: 	u8																*/
/*				u8 u8Frame																*/
/*              Description: Type of Frame								                */
/* 				Range: 	CAN_u8REMOTE, CAN_u8DATA										*/
/*				u8* pu8Data																*/
/*              Description: Array containing data to send over CAN, NULL if Remote Fram*/
/* 				Range: 	u8*																*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
u8 CANHANDLER_vidSend(u8 u8MessageID, u8 u8Frame,u8* pu8Data, u8 u8DataLength)
{
	u8 u8MailBoxIndex = 0;
	u8 u8DataCounter = 0;
	for (u8MailBoxIndex = 0; u8MailBoxIndex < 3; u8MailBoxIndex++)
	{
		if (CAN_TxRdy[u8MailBoxIndex] == 1)
		{
			break;
		}
	}

	if (u8MailBoxIndex == 3)
	{
		return u8MailBoxIndex;
	}

	switch (u8Frame)
	{
	case CAN_u8REMOTEFRAME:
		CAN_TxMsg[u8MailBoxIndex].type = REMOTE_FRAME;
		CAN_TxMsg[u8MailBoxIndex].id = u8MessageID;                              // initialise message to send
		CAN_TxMsg[u8MailBoxIndex].len = u8DataLength;
		CAN_TxMsg[u8MailBoxIndex].format = STANDARD_FORMAT;
		CAN_TxRdy[u8MailBoxIndex] = 0;
		CAN_wrMsg(&(CAN_TxMsg[u8MailBoxIndex]), u8MailBoxIndex);
		break;

	case CAN_u8DATAFRAME:
		CAN_TxMsg[u8MailBoxIndex].type = DATA_FRAME;
		CAN_TxMsg[u8MailBoxIndex].id = u8MessageID;                              // initialise message to send

		for (u8DataCounter = 0; u8DataCounter < u8DataLength; u8DataCounter++)
		{
			CAN_TxMsg[u8MailBoxIndex].data[u8DataCounter] = pu8Data[u8DataCounter];
		}

		CAN_TxMsg[u8MailBoxIndex].len = u8DataLength;
		CAN_TxMsg[u8MailBoxIndex].format = STANDARD_FORMAT;
		CAN_TxRdy[u8MailBoxIndex] = 0;
		CAN_wrMsg(&(CAN_TxMsg[u8MailBoxIndex]), u8MailBoxIndex);
		break;

	}
	return u8MailBoxIndex;
}


/****************************************************************************************/
/* Description: Receive Can Message 							 						*/
/* Input      : Void																	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
u8 CANHANDLER_vidReceive(void)
{
	u8 u8counter = 0;
	u8 u8DataCounter = 0;
	if (CAN_RxRdy)
	{
		CAN_RxRdy = 0;
		for (u8counter = 0; u8counter < 3; u8counter++)
		{
			if (CAN_RxMsg[u8counter].u8ActiveFlag == 1)
			{
				switch (CAN_RxMsg[u8counter].id)
				{
				case CANHANDLER_u8ECUSWVERSION:
					for (u8DataCounter = 0; u8DataCounter < CAN_RxMsg[u8counter].len; u8DataCounter++)
					{
						/*TODO: Convert data to the array of current version from app/gsm/whatever */
						//au8CurrentVersion[u8DataCounter] = CAN_RxMsg[u8counter].data[u8DataCounter];
					}
					/*TODO: Set the flag from app/gsm/whatever */
					//u8AcceptUpdate = 1;
					break;

				case CANHANDLER_u8GUIUPDATEACCEPT:
					/*TODO: Set the flag from app/gsm/whatever */
					//u8AcceptUpdate = 1;
					break;

				case CANHANDLER_u8NEXTMSGREQUEST:
					/*TODO: Set the flag from app/gsm/whatever */
					//u8NextMsgRequest = 1;
					break;

				default:
					break;
				}
				CAN_RxMsg[u8counter].u8ActiveFlag = 0;
			}
		}
	}

}
