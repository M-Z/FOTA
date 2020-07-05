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
#include "GSMHANDLER_int.h"

u8 CANHANDLER_u8SWVersionReceived = 0;
u8 CANHANDLER_u8UpdateAcceptReceived = 0;
u8 CANHANDLER_u8NextMsgRequest = 0;
u8 CANHANDLER_u8FlashBankReceived = 0;
u8 CANHANDLER_u8DTCsReceived = 0;

u8 CANHANDLER_au8ECUVersion[8] = {0};
u8 CANHANDLER_au8DTCs[8] = {0};
u8 CANHANDLER_u8UsedBank = 0xFF;

CAN_msg CANHANDLER_strPendingMsg[10] = {0};
u8 CANHANDLER_u8PendingFlag[10] = {0};
u8 u8PendingMsgs = 0;


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
void CANHANDLER_vidSend(u8 u8MessageID, u8 u8Frame,u8* pu8Data, u8 u8DataLength)
{
	u8 u8MailBoxIndex = 0;
	u8 u8DataCounter = 0;
	u8 u8PendingMsgID = 0;
	u8 u8Counter = 0;

	for (u8MailBoxIndex = 0; u8MailBoxIndex < 3; u8MailBoxIndex++)
	{
		if (CAN_TxRdy[u8MailBoxIndex] == 1)
		{
			break;
		}
	}

	if (u8MailBoxIndex < 3)
	{
		/* Send Message */
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
	}
	else
	{
		for (u8Counter = 0; u8Counter < 10; u8Counter++)
		{
			if (CANHANDLER_u8PendingFlag[u8Counter] == 0)
			{
				/* Set the message as Pending */
				switch (u8Frame)
				{
				case CAN_u8REMOTEFRAME:
					CANHANDLER_strPendingMsg[u8Counter].type = REMOTE_FRAME;
					CANHANDLER_strPendingMsg[u8Counter].id = u8MessageID;                              // initialise message to send
					CANHANDLER_strPendingMsg[u8Counter].len = u8DataLength;
					CANHANDLER_strPendingMsg[u8Counter].format = STANDARD_FORMAT;
					break;

				case CAN_u8DATAFRAME:
					CANHANDLER_strPendingMsg[u8Counter].type = DATA_FRAME;
					CANHANDLER_strPendingMsg[u8Counter].id = u8MessageID;                              // initialise message to send

					for (u8DataCounter = 0; u8DataCounter < u8DataLength; u8DataCounter++)
					{
						CANHANDLER_strPendingMsg[u8Counter].data[u8DataCounter] = pu8Data[u8DataCounter];
					}

					CANHANDLER_strPendingMsg[u8Counter].len = u8DataLength;
					CANHANDLER_strPendingMsg[u8Counter].format = STANDARD_FORMAT;
					break;
				}

				CANHANDLER_u8PendingFlag[u8Counter] = 1;
				u8PendingMsgs = 1;
			}
		}
	}
}




/****************************************************************************************/
/* Description: Send Can Message Task 							 						*/
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
void CANHANDLER_vidSendTask(void)
{
	u8 u8MailBoxIndex = 0;
	u8 u8DataCounter = 0;
	u8 u8Counter = 0;

	if (u8PendingMsgs == 1)
	{
		u8PendingMsgs = 0;
		for (u8Counter = 0; u8Counter < 10; u8Counter++)
		{
			if (CANHANDLER_u8PendingFlag[u8Counter] == 1)
			{
				for (u8MailBoxIndex = 0; u8MailBoxIndex < 3; u8MailBoxIndex++)
				{
					if (CAN_TxRdy[u8MailBoxIndex] == 1)
					{
						CAN_wrMsg(&(CANHANDLER_strPendingMsg[u8Counter]), u8MailBoxIndex);
						CANHANDLER_u8PendingFlag[u8Counter] = 0;
					}
					else
					{
						/* Stop the search and keep PendingMessages Flag active */
						u8PendingMsgs = 1;
						break;
					}
				}
			}
			else
			{
				/* Do Nothing */
			}
		}
	}

}



/****************************************************************************************/
/* Description: Receive Can Message 							 						*/
/* Input      : Void																	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void CANHANDLER_vidReceive(void)
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
						CANHANDLER_au8ECUVersion[u8DataCounter] = CAN_RxMsg[u8counter].data[u8DataCounter];
					}
					CANHANDLER_u8SWVersionReceived = 1;
					break;

				case CANHANDLER_u8GUIUPDATEACCEPT:
					CANHANDLER_u8UpdateAcceptReceived = 1;
					break;

				case CANHANDLER_u8NEXTMSGREQUEST:
					CANHANDLER_u8NextMsgRequest = 1;
					break;

				case CANHANDLER_u8GETFLASHBANK:
					CANHANDLER_u8FlashBankReceived = 1;
					CANHANDLER_u8UsedBank = CAN_RxMsg[u8counter].data[0];
					break;

				case CANHANDLER_u8ECUDTCs:
					switch(CAN_RxMsg[u8counter].type)
					{
					case CAN_u8REMOTEFRAME:
						/* Start Diagnostics Session */
						GSMHANDLER_vidStartDiag();
						break;

					case CAN_u8DATAFRAME:
						for (u8DataCounter = 0; u8DataCounter < CAN_RxMsg[u8counter].len; u8DataCounter++)
						{
							CANHANDLER_au8DTCs[u8DataCounter] = CAN_RxMsg[u8counter].data[u8DataCounter];
						}
						CANHANDLER_u8DTCsReceived = 1;
						break;
					}
					break;

				default:
					break;
				}
				CAN_RxMsg[u8counter].u8ActiveFlag = 0;
			}
		}
	}

}

