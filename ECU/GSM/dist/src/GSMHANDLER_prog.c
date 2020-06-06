/*
   GSM_handler.c

    Created on: 15 May 2020
        Author: Michael
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

#include "SCH_int.h"
#include "SCH_cfg.h"

#include "CANHANDLER_int.h"
#include "CANHANDLER_cfg.h"

#include "GSMHANLDER_priv.h"
#include "GSMHANDLER_int.h"

#include "crypto.h"
#include "Application.h"



#include "Timer_int.h"

MessageState GSM_enuListenFlag = IDLE;

Step GSMHANDLER_enuCurrentStep = DisableEcho;
Step GSMHANDLER_enuRollBackStep = DisableEcho;
Step GSMHANDLER_enuNextStep = DisableEcho;

Step GSMHANDLER_enuServerStep = GETSWVersion; /* Either GetSWVersion or GETHexFile */

volatile u8 au8listenBuffer[225];
u8 * pu8StatePtr;
u32 u32ResponseFileSize = 0;

u8 GSMHANDLER_u8TransmissionCompleteFlag = 0;


/*****************************************/
/***********Public Functions**************/
/*****************************************/


/****************************************************************************************/
/* Description: GSM Task in the Scheduler						                        */
/* Input      : Void                                            			            */
/* Output     : Void                                                                	*/
/* Scope      : Public                                                                  */
/****************************************************************************************/
void GSMHANDLER_vidTask(void)
{
	static u8 au8Data[200] = {0};
	static u8 au8ExpectedHash[64] = {0};
	static u16 u16ReceivedDataSize = 0;
	static u8 u8CanMessageSent = 0;
	static u32 u32ResponseDataSize = 0;
	static u32 u32StartPoint = 0;
	static u8 u8UsedBank = 0;
	u8 u8UpdateProgress = 0;

	s32 status = HASH_SUCCESS;
	/* string length only, without '\0' end of string marker */
	u8 MessageDigest[CRL_SHA256_SIZE];
	s32 MessageDigestLength = 0;

	switch (GSMHANDLER_enuCurrentStep)
	{
	//Initialize GSM
	case DisableEcho:
		GSMHANDLER_enuNextStep = SetBearerParameters;
		GSMHANDLER_enuRollBackStep = DisableEcho;
		vidSendCommand("ATE0\r\n");
		break;

	case SetBearerParameters:
		GSMHANDLER_enuNextStep = OpenBearer;
		GSMHANDLER_enuRollBackStep = SetBearerParameters;
		vidSendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n");
		break;

	case OpenBearer:
		GSMHANDLER_enuNextStep = InitializeHTTP;
		GSMHANDLER_enuRollBackStep = CloseBearer;
		vidSendCommand("AT+SAPBR=1,1\r\n");
		break;

	case CloseBearer:
		GSMHANDLER_enuNextStep = OpenBearer;
		GSMHANDLER_enuRollBackStep = CloseBearer;
		vidSendCommand("AT+SAPBR=0,1\r\n");
		break;

	case InitializeHTTP:
		GSMHANDLER_enuNextStep = EnableSSL;
		GSMHANDLER_enuRollBackStep = TerminateHTTP;
		vidSendCommand("AT+HTTPINIT\r\n");
		break;

	case TerminateHTTP:
		GSMHANDLER_enuNextStep = InitializeHTTP;
		GSMHANDLER_enuRollBackStep = TerminateHTTP;
		vidSendCommand("AT+HTTPTERM\r\n");
		break;


	case EnableSSL:
		if (u8CanMessageSent == 0)
		{
			CANHANDLER_vidSend(CANHANDLER_u8GETFLASHBANK, CAN_u8REMOTEFRAME, NULL ,0);
			u8CanMessageSent = 1;
		}
		GSMHANDLER_enuNextStep = SetCID;
		GSMHANDLER_enuRollBackStep = EnableSSL;
		vidSendCommand("AT+HTTPSSL=1\r\n");
		break;

	case SetCID:
		GSMHANDLER_enuNextStep = EnableREDIR;
		GSMHANDLER_enuRollBackStep = SetCID;
		vidSendCommand("AT+HTTPPARA=\"CID\",1\r\n");
		break;


	case EnableREDIR:
		GSMHANDLER_enuNextStep = SetContentType;
		GSMHANDLER_enuRollBackStep = EnableREDIR;
		vidSendCommand("AT+HTTPPARA=\"REDIR\",1\r\n");
		break;

	case SetContentType:
		GSMHANDLER_enuNextStep = SetURL;
		GSMHANDLER_enuRollBackStep = SetContentType;
		vidSendCommand("AT+HTTPPARA=\"content\",\"application/json\"\r\n");
		break;

	case SetURL:
		GSMHANDLER_enuNextStep = SendHTTPData;
		GSMHANDLER_enuRollBackStep = SetURL;
		if (CANHANDLER_u8FlashBankReceived == 1)
		{
			u8CanMessageSent = 0;
			CANHANDLER_u8FlashBankReceived = 0;
		}
		else
		{

		}

		if (CANHANDLER_u8UsedBank == 1)
		{
			if (GSMHANDLER_enuServerStep == GETSWVersion)
			{
				//C13 ON Bank 1 w/o feedback
//					vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/v/5ed3cf5e3735b16961faf0fd\"\r\n");
				//C13 ON Bank 1 with feedback
				vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/v/5edbb180c67d0c31ae720b92\"\r\n");
			}
			else if (GSMHANDLER_enuServerStep == GETHexFile)
			{
				//C13 ON Bank 1 w/o feedback
//					vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/get/5ed3cf5e3735b16961faf0fd\"\r\n");
				//C13 ON Bank 1 with feedback
				vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/get/5edbb180c67d0c31ae720b92\"\r\n");
			}
		}
		else if (CANHANDLER_u8UsedBank == 0)
		{
			if (GSMHANDLER_enuServerStep == GETSWVersion)
			{
				//C14 on Bank 2 w/o feedback
//					vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/v/5ed97e86c67d0c31ae720b90\"\r\n");
				//C14 ON Bank 2 with feedback
				vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/v/5edbb355c67d0c31ae720b94\"\r\n");
			}
			else if (GSMHANDLER_enuServerStep == GETHexFile)
			{
				//C14 on Bank 2 w/o feedback
//					vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/get/5ed97e86c67d0c31ae720b90\"\r\n");
				//C14 ON Bank 2 with feedback
				vidSendCommand("AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/get/5edbb355c67d0c31ae720b94\"\r\n");
			}
		}
		else
		{
			/* Not yet received */
		}

		break;

	case SendHTTPData:
		vidSendHTTPData();
		break;


	case SendVehicleName:
		vidSendVehicleName();
		break;

	case POSTRequest:
		u32ResponseDataSize = u32SendPostRequest();
		break;


	case GETSWVersion:
		/* Send SW Version Request Through CAN */
		if (u8CanMessageSent == 0)
		{
			CANHANDLER_vidSend(CANHANDLER_u8ECUSWVERSION, CAN_u8REMOTEFRAME, NULL ,0);
			u8CanMessageSent = 1;
		}
		u16ReceivedDataSize = u16GETData(0,u32ResponseDataSize,au8Data);
		break;


	case CompareSWVersion:
		/* Wait for the CAN Response */
		if (CANHANDLER_u8SWVersionReceived == 1)
		{
			u8CanMessageSent = 0;
			CANHANDLER_u8SWVersionReceived = 0;
			/* Check if an update is available */
			vidCheckUpdate(au8Data);
		}
		else
		{
			/* TODO: Timeout? resend CAN Message */
		}
		break;

	case AcceptUpdate:
		/* Wait for User Acceptance */
		if (CANHANDLER_u8UpdateAcceptReceived == 1)
		{
			u8CanMessageSent = 0;
			CANHANDLER_u8UpdateAcceptReceived = 0;
			CANHANDLER_vidSend(CANHANDLER_u8UPDATEREQUESTID, CAN_u8REMOTEFRAME, NULL,0);
			GSMHANDLER_enuCurrentStep = SetContentType;
			GSMHANDLER_enuServerStep = GETHexFile;
		}
		else
		{
			/* TODO: Timeout? resend CAN Message */
		}
		break;

	case GETHash:
		u16ReceivedDataSize = u16GETData(u32StartPoint, (u16)64,au8ExpectedHash);
		break;

	case GETHexFile:
		u16ReceivedDataSize = u16GETData((u32StartPoint+64), (u16)200, au8Data);
		break;

	case CheckDecryption:

		/* DeInitialize STM32 Cryptographic Library */
		Crypto_DeInit();
		//Generate Hash code for a certain part of file
		status = STM32_SHA256_HASH_DigestCompute((u8*)au8Data, u16ReceivedDataSize, (u8*)MessageDigest, &MessageDigestLength);
		//if Hash generation succeed, Compare the received Hash code with the generated Hash code
		if (status == HASH_SUCCESS) {
			if (Buffercmp(au8ExpectedHash,MessageDigest) == PASSED) {
				//Correct Hash check, Flash the file
				GSMHANDLER_enuCurrentStep = SendFile;
			} else {
				asm("NOP");
				//Incorrect Hash check, Retry one time only
			}
		} else {
			//Hash check Error, Retry again
			/* Add application traintment in case of hash not success possible values of status:
			 * HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT, HASH_ERR_BAD_OPERATION
			 */
			asm("NOP");
		}
		break;

	case SendFile:
		vidSendHexFile(au8Data, u16ReceivedDataSize);
		break;

	case ReceiveFeedback:
		if (CANHANDLER_u8NextMsgRequest == 1)
		{
			CANHANDLER_u8NextMsgRequest = 0;

			GSMHANDLER_enuCurrentStep = GSMHANDLER_enuNextStep;
			if (GSMHANDLER_enuNextStep == GETHash)
			{
				/* Send Update Status to GUI */
				u8UpdateProgress = (u8)((u32StartPoint*(u32)100)/u32ResponseDataSize);
				CANHANDLER_vidSend(CANHANDLER_u8UPDATEPROGRESS, CAN_u8DATAFRAME, &u8UpdateProgress, 1);
				u32StartPoint += 264;
				if (u32StartPoint >= u32ResponseDataSize)
				{
					GSMHANDLER_enuCurrentStep = Done;
				}
				else
				{
					/* Do Nothing */
				}
			}
			else
			{
				/* Do Nothing */
			}
		}
		break;

	case Done:
		u8UpdateProgress = 100;
		CANHANDLER_vidSend(CANHANDLER_u8UPDATEPROGRESS, CAN_u8DATAFRAME, &u8UpdateProgress, 1);
		SCH_vidStopTask(0);
		break;
	}
}



/****************************************************************************************/
/* Description: Send GSM command								 						*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidSendCommand(u8* pu8Command)
{
	Error_Status enuresponseStatus = NOK;

	switch (GSM_enuListenFlag)
	{
	case IDLE:
		DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
		USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, pu8Command, 0 );
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
			enuresponseStatus = enuFindString(au8listenBuffer, "\r\nOK\r\n", 64);
			if (enuresponseStatus == OK)
			{
				GSM_enuListenFlag = IDLE;
				GSMHANDLER_enuCurrentStep = GSMHANDLER_enuNextStep;
				DMA_voidDisable(DMA_CHANNEL_5);
				vidClearBuffer(au8listenBuffer,64);
			}
			else
			{
				/* Check for Error Response */
				enuresponseStatus = enuFindString(au8listenBuffer, "\r\nERROR\r\n", 64);
				if (enuresponseStatus == OK)
				{
					GSMHANDLER_enuCurrentStep = GSMHANDLER_enuRollBackStep;
					GSM_enuListenFlag = IDLE;
					DMA_voidDisable(DMA_CHANNEL_5);
					vidClearBuffer(au8listenBuffer,64);
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
}



/****************************************************************************************/
/* Description: Send HTTP Data										 					*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidSendHTTPData(void)
{
	Error_Status enuresponseStatus = NOK;

	switch (GSM_enuListenFlag)
	{
	case IDLE:
		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
		USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPDATA=100,10000\r\n", 0 );
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
			enuresponseStatus = enuFindString(au8listenBuffer, "DOWNLOAD\r\n", 64);
			if (enuresponseStatus == OK)
			{
				GSM_enuListenFlag = IDLE;
				GSMHANDLER_enuCurrentStep = SendVehicleName;
				DMA_voidDisable(DMA_CHANNEL_5);
				vidClearBuffer(au8listenBuffer,64);
			}
			else
			{
				/* Check for Error Response */
				enuresponseStatus = enuFindString(au8listenBuffer, "\r\nERROR\r\n", 64);
				if (enuresponseStatus == OK)
				{
					GSM_enuListenFlag = IDLE;
					GSMHANDLER_enuCurrentStep = InitializeHTTP;
					DMA_voidDisable(DMA_CHANNEL_5);
					vidClearBuffer(au8listenBuffer,64);
				}
				else
				{
					/* Do Nothing */
				}
			}
		}
		break;

	}
}



/****************************************************************************************/
/* Description: Send Vehicle name and Password										 	*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidSendVehicleName(void)
{
	Error_Status enuresponseStatus = NOK;

	switch (GSM_enuListenFlag)
	{
	case IDLE:
		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
		if (GSMHANDLER_enuServerStep == GETSWVersion)
		{
			USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", 0 );
		}
		else if (GSMHANDLER_enuServerStep == GETHexFile)
		{
			USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "{\"vehicleName\":\"fota user\",\"password\":\"123\", \"bytes\": \"200\", \"hashType\": \"sha256\"}\r\n", 0 );
		}
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
			enuresponseStatus = enuFindString(au8listenBuffer, "\r\nOK\r\n", 64);
			if (enuresponseStatus == OK)
			{
				GSM_enuListenFlag = IDLE;
				GSMHANDLER_enuCurrentStep = POSTRequest;
				DMA_voidDisable(DMA_CHANNEL_5);
				vidClearBuffer(au8listenBuffer,64);
			}
			else
			{
				/* Check for Error Response */
				enuresponseStatus = enuFindString(au8listenBuffer, "\r\nERROR\r\n", 64);
				if (enuresponseStatus == OK)
				{
					GSM_enuListenFlag = IDLE;
					GSMHANDLER_enuCurrentStep = SendVehicleName;
					DMA_voidDisable(DMA_CHANNEL_5);
					vidClearBuffer(au8listenBuffer,64);
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
}


/****************************************************************************************/
/* Description: Send PostRequest													 	*/
/* Input      : Void			                                                        */
/* Output     : u32			                                                            */
/*				Description: Received Data Size											*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
u32 u32SendPostRequest(void)
{
	Error_Status enuresponseStatus = NOK;
	u8 u8Counter = 0;
	u32 u32ReceivedDataSize = 0;

	switch (GSM_enuListenFlag)
	{
	case IDLE:
		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
		USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPACTION=1\r\n", 0 );
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
			if(u8CheckBufferTermination(au8listenBuffer, 64, 4 )  == 1)
			{
				enuresponseStatus = enuFindString(au8listenBuffer, "\r\nOK\r\n", 64);
				if (enuresponseStatus == OK)
				{

					enuresponseStatus = enuFindString(au8listenBuffer, "200", 64);
					if (enuresponseStatus == OK)
					{
						GSM_enuListenFlag = IDLE;
						DMA_voidDisable(DMA_CHANNEL_5);
						//get Received data size
						for (u8Counter = 27; au8listenBuffer[u8Counter] != '\r'; u8Counter++)
						{
							u32ReceivedDataSize = ((u32ReceivedDataSize)* 10) + (au8listenBuffer[u8Counter] - '0');
						}

						GSM_enuListenFlag = IDLE;
						vidClearBuffer(au8listenBuffer,64);

						if (GSMHANDLER_enuServerStep == GETSWVersion)
						{
							GSMHANDLER_enuCurrentStep = GETSWVersion;
						}
						else if (GSMHANDLER_enuServerStep == GETHexFile)
						{
							GSMHANDLER_enuCurrentStep = GETHash;
						}
					}
					else
					{
						GSM_enuListenFlag = IDLE;
						GSMHANDLER_enuCurrentStep = InitializeHTTP;
					}
				}
			}
			else
			{
				/* Check for Error Response */
				enuresponseStatus = enuFindString(au8listenBuffer, "\r\nERROR\r\n", 64);
				if (enuresponseStatus == OK)
				{
					GSM_enuListenFlag = IDLE;
					GSMHANDLER_enuCurrentStep = InitializeHTTP;
					DMA_voidDisable(DMA_CHANNEL_5);
					vidClearBuffer(au8listenBuffer,64);
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
	return u32ReceivedDataSize;
}


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
u16 u16GETData(u32 u32StartPoint, u16 u16DataLength, u8* au8Data)
{
	Error_Status enuresponseStatus = NOK;
	static u8 au8Cmd[100] = "AT+HTTPREAD=";
	u8 u8Counter = 12;
	u8 u8Counter2 = 0;
	u16 u16ReceivedDataSize = 0;
	u8  au8startpointascii[11] = {0};
	u8 au8sizeascii[11] = {0};
	u16 u16Counter = 0;
	u8 u8sizeasciistartpoint = 0;
	u8 u8startasciistartpoint = 0;
	u8 u8DataStartPoint = 0;

	switch (GSM_enuListenFlag)
	{
	case IDLE:
		if (u32StartPoint == 0)
		{
			au8startpointascii[9] = '0';
			u8startasciistartpoint = 1;
		}
		if (u16DataLength == 0)
		{
			au8sizeascii[9] = '0';
			u8sizeasciistartpoint = 1;
		}

		for (u16Counter = 10; u16Counter > 0; u16Counter--)
		{
			if (u16DataLength != 0)
			{
				au8sizeascii[u16Counter-1] = (u16DataLength % 10) + 48;
				u16DataLength = u16DataLength/10;
				u8sizeasciistartpoint++;
			}
			if (u32StartPoint != 0)
			{
				au8startpointascii[u16Counter-1] = (u32StartPoint % 10) + 48;
				u32StartPoint = u32StartPoint/10;
				u8startasciistartpoint++;
			}
			if ( (au8sizeascii == 0) && (u32StartPoint == 0) )
			{
				break;
			}
		}


		//Re-Construct Command
		//Concatenate "AT+HTTPREAD="


		while(u8Counter2 < u8startasciistartpoint)
		{
			au8Cmd[u8Counter] = au8startpointascii[10 - u8startasciistartpoint + u8Counter2];
			u8Counter++;
			u8Counter2++;
		}

		au8Cmd[u8Counter] = ',';
		u8Counter++;
		u8Counter2 = 0;

		while(u8Counter2 < u8sizeasciistartpoint)
		{
			au8Cmd[u8Counter] = au8sizeascii[10 - u8sizeasciistartpoint + u8Counter2];
			u8Counter++;
			u8Counter2++;
		}

		au8Cmd[u8Counter] = '\r';
		u8Counter++;
		au8Cmd[u8Counter] = '\n';
		u8Counter++;
		au8Cmd[u8Counter] = '\0';

		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 225 );
		USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, au8Cmd, 0 );
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
			enuresponseStatus = enuFindString(au8listenBuffer, "\r\nOK\r\n", 225);
			if (enuresponseStatus == OK)
			{
				DMA_voidDisable(DMA_CHANNEL_5);
				for (u16Counter = 13; au8listenBuffer[u16Counter] != '\r'; u16Counter++)
				{
					u16ReceivedDataSize = (u16ReceivedDataSize * 10) + (au8listenBuffer[u16Counter] - '0');
				}

				// The Received data is version info from server
				u16Counter = u16Counter + 2;
				u8DataStartPoint = u16Counter;
				for ( ; u16Counter < (u8DataStartPoint + u16ReceivedDataSize); u16Counter++)
				{
					au8Data[u16Counter - u8DataStartPoint] = au8listenBuffer[u16Counter];
				}
				GSM_enuListenFlag = IDLE;
				vidClearBuffer(au8listenBuffer,225);
				if (GSMHANDLER_enuServerStep == GETSWVersion)
				{
					GSMHANDLER_enuCurrentStep = CompareSWVersion;
				}
				else if (GSMHANDLER_enuServerStep == GETHexFile)
				{
					if (GSMHANDLER_enuCurrentStep == GETHash)
					{
						GSMHANDLER_enuCurrentStep = GETHexFile;
					}
					else if (GSMHANDLER_enuCurrentStep == GETHexFile)
					{
						GSMHANDLER_enuCurrentStep = CheckDecryption;
					}
				}

			}
			else
			{
				/* Check for Error Response */
				enuresponseStatus = enuFindString(au8listenBuffer, "\r\nERROR\r\n", 225);
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
	return u16ReceivedDataSize;
}


/****************************************************************************************/
/* Description: Check if an update is available											*/
/* Input      : u8* au8Data																*/
/*              Description: Version from the server									*/
/* Output     : Void																	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void vidCheckUpdate(u8* au8Data)
{
	Update_Status serverStatus = updateExist;

	serverStatus = serverResponseHandling(au8Data);
	if(serverStatus == checkupdate)
	{
		serverStatus = updateVersioncheck(au8Data,CANHANDLER_au8ReceivedData);
		if(serverStatus == updateExist)
		{
			CANHANDLER_vidSend(CANHANDLER_u8UPDATEREQUESTGUI, CAN_u8REMOTEFRAME, NULL, 0);
			GSMHANDLER_enuCurrentStep = AcceptUpdate;
		}
		else if(serverStatus ==  updateRollbackExist)
		{
			/* TODO: Handle Rollbacks */
			asm("NOP");
		}
		else if(serverStatus == updateNotExist)
		{
			/* TODO: Add requests other ECUs softwares from server */
			GSMHANDLER_enuCurrentStep = Done;
		}
	}
	else if(serverStatus == VehicleNotFound)
	{
		//The username passed in post request init is incorrect
		GSMHANDLER_enuCurrentStep = InitializeHTTP;
	}
	else if(serverStatus == IncorrectPassword)
	{
		//The password passed in post requet init is incorrect
		GSMHANDLER_enuCurrentStep = InitializeHTTP;
	}
	else
	{
		GSMHANDLER_enuCurrentStep = InitializeHTTP;
	}
}



/****************************************************************************************/
/* Description: Check if an update is available											*/
/* Input      : u8* au8Data																*/
/*              Description: File to be sent											*/
/* Output     : Void																	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void vidSendHexFile(u8* au8Data, u16 u16ReceivedDataSize)
{
	static u8 u8Counter = 0;
	u8 au8HexData[8] = {0};
	u8 u8CharCount = 0;
	for (u8CharCount = 0 ; u8CharCount < 8; )
	{
		if (au8Data[u8Counter] != '\n')
		{
			au8HexData[u8CharCount] = au8Data[u8Counter];
			u8CharCount++;
		}
		else
		{

		}
		u8Counter++;
		if ((au8HexData[u8CharCount-1] == '\r') || (u8Counter == u16ReceivedDataSize))
		{
			break;
		}
	}
	if (au8Data[u8Counter] == '\n')
	{
		u8Counter++;
	}
	CANHANDLER_vidSend(CANHANDLER_u8HEXFILEID, CAN_u8DATAFRAME, au8HexData, u8CharCount);
	GSMHANDLER_enuCurrentStep = ReceiveFeedback;

	if (u8Counter < u16ReceivedDataSize)
	{
		GSMHANDLER_enuNextStep = SendFile;
	}
	else
	{
		u8Counter = 0;
		GSMHANDLER_enuNextStep = GETHash;
	}
}


/****************************************************************************************/
/* Description: Interrupt Handler for the DMA                     */
/* Input      : Void                                                              */
/* Output     : Void                                                                */
/* Scope      : Private                                                                 */
/****************************************************************************************/
void vidDMAIRQ(void)
{
	GSMHANDLER_u8TransmissionCompleteFlag = 1;
}



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
static u8 u8CheckBufferTermination(u8* pu8Buffer, u32 u32BufferSize, u8 u8TerminationOccurences)
{
	u8 u8Repeats = 0;
	u8 u8ReturnValue = 0;
	u32 u32Counter = 0;
	for (u32Counter = 0; u32Counter < u32BufferSize; u32Counter++)
		if (pu8Buffer[u32Counter] == '\r' && pu8Buffer[u32Counter + 1] == '\n') {
			u8Repeats++;
			u32Counter++;

			// If we found staring and terminating /r/n  or if we exceeded the pu8Buffer
			if ( u32Counter >= u32BufferSize || u8Repeats == u8TerminationOccurences)
			{
				u8ReturnValue = 1;
				break;
			}
		}

	return u8ReturnValue;
}

/****************************************************************************************/
/* Description: Finds the expected string in the buffer                 */
/* Input      : u8* pu8Buffer                                                           */
/*              Description: Array to search for the string in                      */
/*        Range:  pointer to u8                         */
/*        const u8* pu8ExpectedString                       */
/*              Description: String to search for in the Buffer                     */
/*        Range:  pointer to u8                         */
/*        u32 u32Size                               */
/*              Description: Size of the array we are searching in                */
/*        Range:  u32                               */
/* Output     : Error_Status                                                            */
/*        Range: OK if the string is found, NOK if the string isn't found     */
/* Scope      : Private                                                                 */
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
static void vidClearBuffer(u8* pu8Buffer, u32 u32BufferLength)
{
	u32 u32Counter = 0;
	for(u32Counter = 0; u32Counter < u32BufferLength; u32Counter++)
	{
		pu8Buffer[u32Counter] = 0;
	}
}

//Error_Status DMAListen(u8* pu8state)
//{
//  GSM_u8ListenFlag = ON;
//
//  //Check if the GSM terminate the buffer or not
//  if(u8CheckBufferTermination(au8listenBuffer, 64, 2))
//  {
//    //check if the response is OK or NOK
//    if (enuFindString(au8listenBuffer, "OK", 64) == OK)
//    {
//      // Response contain "OK"
//      DMA_voidDisable(DMA_CHANNEL_5);
//      GSM_u8ListenFlag = OFF;
//      return OK;
//
//    }
//    else if(enuFindString(au8listenBuffer, "ERROR", 64) == OK)
//    {
//      // Response contain "ERROR"
//      DMA_voidDisable(DMA_CHANNEL_5);
//      GSM_u8ListenFlag = OFF;
//      return NOK;
//    }
//    else
//    {
//      // Unknown respose
//      DMA_voidDisable(DMA_CHANNEL_5);
//      GSM_u8ListenFlag = OFF;
//      //return unknown message
//    }
//
//  }
//  return wait;
//}
//
