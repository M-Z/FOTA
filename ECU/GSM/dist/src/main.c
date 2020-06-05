#include "STD_Types.h"
#include "util.h"
#include "RCC_int.h"
#include "DIO_int.h"
#include "NVIC_int.h"
#include "AFIO_init.h"
#include "AFIO_config.h"
#include "USART_int.h"
#include "DMA_int.h"
#include "SCH_int.h"
#include "SCH_cfg.h"
#include "SCB_int.h"
#include "CAN.h"
#include "CANHANDLER_int.h"
#include "CANHANDLER_cfg.h"
#include "GSM_int.h"
#include "GSMHANDLER_int.h"
#include "crypto.h"
#include "Application.h"

#include "Timer_int.h"

u8 u8CharCount = 0;
u8 u8Received = 0;
u8 flag = 0;
/* Private variables ---------------------------------------------------------*/

/* string length only, without '\0' end of string marker */
u8 MessageDigest[CRL_SHA256_SIZE];
s32 MessageDigestLength = 0;


const u32 InputLength = 4;
u8 InputMessage[];
u8 Expected_OutputMessage[32]={0};




void Blink_LED1(void);

int	main(int argc, char* argv[])
{
	s32 status = HASH_SUCCESS;
	Update_Status serverStatus;
	u8 responseData[200]={0};
	u8 HexData[8] = {0};
	u8 au8CurrentVersion[3] = {0};
	u8 u8Counter  = 0;
	u8 u8MailBoxIndex = 0;
	filter_type filters[] = {{CANHANDLER_u8NEXTMSGREQUEST,REMOTE_FRAME, STANDARD_FORMAT},{CANHANDLER_u8GUIUPDATEACCEPT,REMOTE_FRAME, STANDARD_FORMAT}, {CANHANDLER_u8ECUSWVERSION, DATA_FRAME, STANDARD_FORMAT}};
	u8 au8Response[250] = {0};
	u32 u32filesize = 0;
	u32 delay= 0;
	u32 u32Counter = 0;
	u16 u16ReceivedDataSize = 0;
	volatile u8 u8NextMsgRequest = 0;
	volatile u8 u8AcceptUpdate = 0;
	u8 u8UpdateProgress = 0;
	u8 rxcount = 0;
	DMA_Config newDMA =
	{
			DMA_CHANNEL_5,	// Channel number: CHANNEL_1, CHANNEL_2, ...
			FALSE,			// Memory to Memory: TRUE, FALSE
			VERY_HIGH,		// LOW, MEDIUM, HIGH, VERY_HIGH
			BITS_8,			// Specifies Source data size alignment (byte, half word, word).
			BITS_8,			// Specifies Destination data size alignment (byte, half word, word).
			TRUE,			// Specifies if MEM address is incremented or not
			FALSE,			// Specifies PERIPHRAL address is incremented or not.
			FALSE,			// Specifies the normal or circular operation mode: TRUE, FALSE
			FROM_PERIPHRAL,	// If the data will be transferred from memory to peripheral: FROM_MEM, FROM_PERIPHRAL
			FALSE,			// Transfer error interrupt enable
			FALSE,			// Half transfer interrupt enable
			FALSE			// Transfer complete interrupt enable
	};


	DMA_Config DMA_Transmit =
	{
			DMA_CHANNEL_4,	// Channel number: CHANNEL_1, CHANNEL_2, ...
			FALSE,			// Memory to Memory: TRUE, FALSE
			VERY_HIGH,		// LOW, MEDIUM, HIGH, VERY_HIGH
			BITS_8,			// Specifies Source data size alignment (byte, half word, word).
			BITS_8,			// Specifies Destination data size alignment (byte, half word, word).
			FALSE,			// Specifies if MEM address is incremented or not
			TRUE,			// Specifies PERIPHRAL address is incremented or not.
			FALSE,			// Specifies the normal or circular operation mode: TRUE, FALSE
			FROM_PERIPHRAL,	// If the data will be transferred from memory to peripheral: FROM_MEM, FROM_PERIPHRAL
			FALSE,			// Transfer error interrupt enable
			FALSE,			// Half transfer interrupt enable
			TRUE			// Transfer complete interrupt enable
	};

	RCC_vidInit();
	RCC_vidEnablePeripheral(RCC_u8GPIOACLK);
	RCC_vidEnablePeripheral(RCC_u8GPIOBCLK);
	RCC_vidEnablePeripheral(RCC_u8GPIOCCLK);
	RCC_vidEnablePeripheral(RCC_u8USART1CLK);
	RCC_vidEnablePeripheral(RCC_u8CANCLK);
	RCC_vidEnablePeripheral(RCC_u8AFIOCLK);
	RCC_vidEnablePeripheral( RCC_u8DMA1CLK );

	AFIO_vidinit();
	DIO_vidInit();

	NVIC_vidInit();
	NVIC_vidEnableInterrupt(NVIC_u8DMA1_CHANNEL5);
	NVIC_vidEnableInterrupt(NVIC_u8DMA1_CHANNEL4);
	NVIC_vidEnableInterrupt(NVIC_u8USB_HP_CAN_TX);
	NVIC_vidEnableInterrupt(NVIC_u8USB_LP_CAN_RX0);
	NVIC_vidSetPriority(NVIC_u8USB_HP_CAN_TX, 3);	//Group 0, sub 3
	NVIC_vidSetPriority(NVIC_u8USB_LP_CAN_RX0, 3);	//Group 0, sub 3
	SCB_vidSetInterruptPriority(SCB_u8SYSTICK, 4);	//Group 1, sub 0

	RCC_vidEnablePeripheral(RCC_u8TIM1CLK);
	NVIC_vidEnableInterrupt(NVIC_u8TIM1_UP);
	Timer1_UEV_Interrupt();


	DMA_enumInit(newDMA);
	DMA_enumInit(DMA_Transmit);

	USART_enumInit(USART_CHANNEL_1);

	/* Create Tasks */
	task led1 = {1000, 0, RUNNING, Blink_LED1};
	task gsm  = {10, 0, RUNNING, GSMHANDLER_vidTask};
	task CANReceiver = {9, 0, RUNNING,CANHANDLER_vidReceive};
	task CANSender = {9, 0, RUNNING,CANHANDLER_vidSendTask};

	/* Send Tasks to Scheduler */
	SCH_vidCreateTask(0, &gsm);
	SCH_vidCreateTask(1, &CANReceiver);
	SCH_vidCreateTask(2, &CANSender);
	SCH_vidCreateTask(3, &led1);

	/* Start the Scheduler */
	SCH_vidStart();



	//------------CAN Bus Intialization---------------------------------------------------------------------
	CAN_setup ();                                   // setup CAN interface
	CAN_vid_filter_list(filters,CANHANDLER_u8MAXFILTERNUMBERS);
	CAN_testmode(0);      // Normal, By Salma
	CAN_start ();                                   // leave init mode
	CAN_waitReady ();                               // wait til mbx is empty
	if (CAN_RxRdy)
	{
		CAN_RxRdy = 0;
	}
	//-------------------------------------------------------------------------------------------------------

	//Intialize GSM and HTTP
//	GSM_enuInit( USART_CHANNEL_1 );
//	GSM_vidInitHTTP();
//	//check the latest version of a certain ECU on the server
//	/***** Without Version Feedback *******/
//	//bank 1 c13
//	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/v/5eb4957d8f310f60b7db600f", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//	//bank 2 c14
//	//	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/v/5eb495fa8f310f60b7db6011", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//
//	/***** With Version Feedback *******/
//	//bank 1 c13
////	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/v/5ebdc50b8f310f60b7db6013", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//	//bank 2 c14
//	//	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/v/5ebdc54f8f310f60b7db6017", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//
//	/* Get Server Response */
//	u16ReceivedDataSize = GSM_u16GETData(0, (u16)u32filesize, responseData);
//
//	/* Get the Current ECU Version */
//	do
//	{
//		u8MailBoxIndex = CANHANDLER_vidSend(CANHANDLER_u8ECUSWVERSION, CAN_u8REMOTEFRAME, (void*)0,0);
//	} while (u8MailBoxIndex == 3);
//	while (u8AcceptUpdate == 0)
//	{
//		if (CAN_RxRdy)
//		{
//			CAN_RxRdy = 0;
//			if (CAN_RxMsg[0].u8ActiveFlag == 1)
//			{
//				switch (CAN_RxMsg[0].id)
//				{
//				case CANHANDLER_u8ECUSWVERSION:
//					for (u8Counter = 0; u8Counter < 3; u8Counter++)
//					{
//						au8CurrentVersion[u8Counter] = CAN_RxMsg[0].data[u8Counter];
//					}
//					u8AcceptUpdate = 1;
//					break;
//				default:
//					break;
//				}
//				CAN_RxMsg[0].u8ActiveFlag = 0;
//			}
//		}
//	}
//
//	/* Check the correctness of login data */
//	serverStatus = serverResponseHandling(responseData);
//	if(serverStatus == checkupdate)
//	{
//		serverStatus=updateVersioncheck(responseData, au8CurrentVersion);
//	}
//	else if(serverStatus == VehicleNotFound)
//	{
//		//The username passed in post requet init is incorrect
//		asm("NOP");
//	}
//	else if(serverStatus == IncorrectPassword)
//	{
//		//The password passed in post requet init is incorrect
//		asm("NOP");
//	}
//
//
//	/* if the login succeed check the update version*/
//	if(serverStatus == updateExist)
//	{
//		do
//		{
//			u8MailBoxIndex = CANHANDLER_vidSend(CANHANDLER_u8UPDATEREQUESTGUI, CAN_u8REMOTEFRAME, (void*)0,1);
//		} while (u8MailBoxIndex == 3);
//		while (u8AcceptUpdate == 0)
//		{
//			if (CAN_RxRdy)
//			{
//				CAN_RxRdy = 0;
//				if (CAN_RxMsg[0].u8ActiveFlag == 1)
//				{
//					switch (CAN_RxMsg[0].id)
//					{
//					case CANHANDLER_u8GUIUPDATEACCEPT:
//						u8AcceptUpdate = 1;
//						break;
//					default:
//						break;
//					}
//					CAN_RxMsg[0].u8ActiveFlag = 0;
//				}
//			}
//		}
//		u8AcceptUpdate = 0;
//		CANHANDLER_vidSend(CANHANDLER_u8UPDATEREQUESTID, CAN_u8REMOTEFRAME, (void*)0,1);
//	}
//	else if(serverStatus ==  updateRollbackExist)
//	{
//		asm("NOP");
//	}
//	else if(serverStatus == updateNotExist)
//	{
//		asm("NOP");
//	}
//	//Request update file if needed
//
//	/***** Without Version Feedback *******/
//	//bank 1 c13
////	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/get/5eb4957d8f310f60b7db600f", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//	//bank 2 c14
//	//	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/get/5eb495fa8f310f60b7db6011", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//
//	/***** With Version Feedback *******/
//	//bank 1 c13
//	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/get/5ebdc50b8f310f60b7db6013", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//	//bank 2 c14
//	//	GSM_enuPOSTRequestInit("34.65.7.33/API/firmware/get/5ebdc54f8f310f60b7db6017", "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", responseData, &u32filesize);
//
//	//Read the file
//	for (u32Counter = 0; u32Counter < u32filesize; u32Counter += 264)
//	{
//		u8UpdateProgress = (u8)((u32Counter*(u32)100)/u32filesize);
//		//get the Hash code of a certain part of file
//		u16ReceivedDataSize = GSM_u16GETData(u32Counter, (u16)64, Expected_OutputMessage);
//		//Read certain part of file
//		u16ReceivedDataSize = GSM_u16GETData((u32Counter+64), (u16)200, au8Response);
//		/* DeInitialize STM32 Cryptographic Library */
//		Crypto_DeInit();
//		//Generate Hash code for a certain part of file
//		status = STM32_SHA256_HASH_DigestCompute((u8*)au8Response, u16ReceivedDataSize, (u8*)MessageDigest, &MessageDigestLength);
//		//if Hash generation succeed, Compare the received Hash code with the generated Hash code
//		if (status == HASH_SUCCESS) {
//			if (Buffercmp(Expected_OutputMessage,MessageDigest) == PASSED) {
//				//Correct Hash check, Flash the file
//				asm("NOP");
//			} else {
//				asm("NOP");
//				//Incorrect Hash check, Retry one time only
//			}
//		} else {
//			//Hash check Error, Retry again
//			/* Add application traintment in case of hash not success possible values of status:
//			 * HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT, HASH_ERR_BAD_OPERATION
//			 */
//			asm("NOP");
//		}
//		//if Hash check succedded, send file data through CAN bus
//		u8Counter = 0;
//
//
//
//		while (u8Counter < u16ReceivedDataSize)
//		{
//			/* Clear Hex Data Array */
//			for (u8CharCount = 0; u8CharCount < 8; u8CharCount++)
//			{
//				HexData[u8CharCount] = 0;
//			}
//			for (u8CharCount = 0 ; u8CharCount < 8; )
//			{
//				if (au8Response[u8Counter] != '\n')
//				{
//					HexData[u8CharCount] = au8Response[u8Counter];
//					u8CharCount++;
//				}
//				else
//				{
//
//				}
//				u8Counter++;
//				if ((HexData[u8CharCount-1] == '\r') || (u8Counter == u16ReceivedDataSize))
//				{
//					//					u8CharCount++;
//					break;
//				}
//			}
//			do
//			{
//				u8MailBoxIndex = CANHANDLER_vidSend(CANHANDLER_u8HEXFILEID, CAN_u8DATAFRAME, HexData, u8CharCount);
//			} while (u8MailBoxIndex == 3);
//			while (u8NextMsgRequest == 0)
//			{
//				if (CAN_RxRdy)
//				{
//					CAN_RxRdy = 0;
//					if (CAN_RxMsg[0].u8ActiveFlag == 1)
//					{
//						switch (CAN_RxMsg[0].id)
//						{
//						case CANHANDLER_u8NEXTMSGREQUEST:
//							u8NextMsgRequest = 1;
//							break;
//						default:
//							break;
//						}
//						CAN_RxMsg[0].u8ActiveFlag = 0;
//					}
//				}
//			}
//			u8NextMsgRequest = 0;
//		}
//		do
//		{
//			u8MailBoxIndex = CANHANDLER_vidSend(CANHANDLER_u8UPDATEPROGRESS, CAN_u8DATAFRAME, &u8UpdateProgress, 1);
//		} while (u8MailBoxIndex == 3);
//	}
//	u8UpdateProgress = 100;
//	do
//	{
//		u8MailBoxIndex = CANHANDLER_vidSend(CANHANDLER_u8UPDATEPROGRESS, CAN_u8DATAFRAME, &u8UpdateProgress, 1);
//	} while (u8MailBoxIndex == 3);

	while (1)
	{

	}
}


void Blink_LED1(void)
{
	static u8 x = 0;
	if (x == 0)
	{
		DIO_vidSetPinValue(DIO_u8PORTC, DIO_u8PIN13, DIO_u8LOW);
		x = 1;
	}
	else if (x == 1)
	{
		DIO_vidSetPinValue(DIO_u8PORTC, DIO_u8PIN13, DIO_u8HIGH);
		x = 0;
	}
}
