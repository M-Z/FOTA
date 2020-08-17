/*
 * GSM_program.c
 *
 *  Created on: 25 Sep 2019
 *      Author: Mario
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

u8 GSM_u8USARTChannel = 0;
u8 GSM_u8DMADoneFlag = 0;
u8 GSM_u8NumberOfTerminations = 0;
u8* pu8UARTBuffer = (void*)0;



/*****************************************/
/***********Public Functions**************/
/*****************************************/

/****************************************************************************************/
/* Description: Checks to see if GSM module is connected to UARTx and disable			*/
/* 				notifications, echo, calls 												*/
/* Input      : u8 u8GSMUARTChannel                                                     */
/*              Description: The UART Channel the GSM is connected to					*/
/* 				Range:	USART_CHANNEL_1,	USART_CHANNEL_2,	USART_CHANNEL_3			*/
/*						USART_CHANNEL_4,	USART_CHANNEL_5								*/
/* Output     : Error_Status                                                            */
/*				Range: OK if initialization succeeded, NOK if failed					*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
Error_Status GSM_enuInit(u8 u8GSMUARTChannel)
{
	Error_Status enuReturnValue = OK;
	Error_Status enuCheckValue = NOK;

	if (u8GSMUARTChannel < 6)
	{
		GSM_u8USARTChannel = u8GSMUARTChannel;

		while (enuCheckValue == NOK)
		{
			enuCheckValue = enuSendCommand( "ATE0" );
		}

		enuSendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");		/* Set the Connection type to GPRS */

		/* Open the GPRS Context */
		enuCheckValue = enuSendCommand("AT+SAPBR=1,1");
		while (enuCheckValue == NOK)
		{
			enuSendCommand("AT+SAPBR=0,1");
			enuCheckValue = enuSendCommand("AT+SAPBR=1,1");
		}
	}
	else
	{
		enuReturnValue = indexOutOfRange;
	}

	return enuReturnValue;
}

/****************************************************************************************/
/* Description: Opens HTTP connection and configures it									*/
/* Input      : Void				                                                    */
/* Output     : Void		                                                            */
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void GSM_vidInitHTTP(void)
{
	Error_Status enuErrorCheck = OK;

	/* Initiate HTTP */
	enuErrorCheck = enuSendCommand("AT+HTTPINIT");
	while (enuErrorCheck == NOK)
	{
		enuSendCommand("AT+HTTPTERM");
		enuErrorCheck = enuSendCommand("AT+HTTPINIT");
	}

	enuSendCommand("AT+HTTPSSL=1");							/* Enable HTTPS */
	enuSendCommand("AT+HTTPPARA=\"CID\",1");			/* Choose barrier profile */
	enuSendCommand("AT+HTTPPARA=\"REDIR\",1");		/* Enable redirection (i.e. If domain redirected to the secure page) */
}



/****************************************************************************************/
/* Description: Sends a get request														*/
/* Input      : const u8* pu8URL				                                        */
/*              Description: The URL/IP to send the request to							*/
/* 				Range: array of u8														*/
/* Output     : u32			                                                            */
/*				Description: Number of characters received from the Request				*/
/*				Range: u32																*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
u32 GSM_enuGETRequestInit(const u8* pu8URL)
{
	volatile u8 au8ResponseBuffer[64] = {0};		/* \r\nOK\r\n or \r\nERROR\r\n */
	u32 u32Counter = 0;
	Error_Status enuErrorCheck = OK;
	u32 u32ReturnValue = 0;

	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8ResponseBuffer, 64 );
	USART_voidSendString(GSM_u8USARTChannel, "AT+HTTPPARA=\"URL\",\"");
	USART_voidSendString(GSM_u8USARTChannel, pu8URL);
	USART_voidSendString(GSM_u8USARTChannel, "\"\r\n");

	while (!u8CheckBufferTermination(au8ResponseBuffer, 9, 2));
	DMA_voidDisable(DMA_CHANNEL_5);

	enuErrorCheck = enuFindString(au8ResponseBuffer, "OK", 9);
	if (enuErrorCheck == NOK)
	{
		return u32ReturnValue;
	}
	vidClearBuffer(au8ResponseBuffer,64);

	/* Execute GET request */
	enuErrorCheck = enuSendCommand("AT+HTTPACTION=0");
	if (enuErrorCheck == NOK)
	{
		return u32ReturnValue;
	}


	/* Now should receive "+HTTPACTION: 0,200,x" */
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8ResponseBuffer, 64 );

	while ( !u8CheckBufferTermination( au8ResponseBuffer, 64, 2 ) );
	DMA_voidDisable( DMA_CHANNEL_5 );

	/* Response 200 */
	if ( au8ResponseBuffer[17] == '2' && au8ResponseBuffer[18] == '0' && au8ResponseBuffer[19] == '0' )
	{
		for (u32Counter = 21; au8ResponseBuffer[u32Counter] != '\r'; u32Counter++)
		{
			u32ReturnValue = (u32ReturnValue * 10) + (au8ResponseBuffer[u32Counter] - '0');
		}

	}
	else
	{
		u32ReturnValue = 0;
	}

	return u32ReturnValue;
}




/****************************************************************************************/
/* Description: Gets Data after the HTTP request											*/
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
u16 GSM_u16GETData(u32 u32StartPoint, u16 u16DataLength, u8* au8Data)
{
	volatile u8 au8Response[300] = {0};
	u16 u16ReceivedDataSize = 0;
	u16 u16ResponseSize = u16DataLength + (u16)25;
	u8  au8startpointascii[11] = {0};
	u8 au8sizeascii[11] = {0};
	u16 u16Counter = 0;
	u8 u8sizeasciistartpoint = 0;
	u8 u8startasciistartpoint = 0;
	u8 u8DataStartPoint = 0;

	u32 delay =0;

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

	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8Response, u16ResponseSize );
	USART_voidSendString( GSM_u8USARTChannel, "AT+HTTPREAD=" );
	USART_voidSendString( GSM_u8USARTChannel, &(au8startpointascii[10 - u8startasciistartpoint]));
	USART_voidSendString( GSM_u8USARTChannel, ",");
	USART_voidSendString( GSM_u8USARTChannel, &(au8sizeascii[10 - u8sizeasciistartpoint]));
	USART_voidSendString( GSM_u8USARTChannel, "\r\n");
	vidClearBuffer(au8Response, 300);

	while ((enuFindString(au8Response, "\r\nOK\r\n",u16ResponseSize) == NOK) && (enuFindString(au8Response, "\r\nNOK\r\n",u16ResponseSize) == NOK));
//	for (delay = 0; delay<7200000; delay++ );
	DMA_voidDisable( DMA_CHANNEL_5 );

	if (enuFindString( au8Response, "+HTTPREAD: ", 100 ) == NOK)
	{
		return 0;
	}

	for (u16Counter = 13; au8Response[u16Counter] != '\r'; u16Counter++)
	{
		u16ReceivedDataSize = (u16ReceivedDataSize * 10) + (au8Response[u16Counter] - '0');
	}

	u16Counter = u16Counter + 2;
	u8DataStartPoint = u16Counter;
	for ( ; u16Counter < (u8DataStartPoint + u16ReceivedDataSize); u16Counter++)
	{
		au8Data[u16Counter - u8DataStartPoint] = au8Response[u16Counter];
	}
	if (enuFindString( (au8Response+u16Counter), "OK", 300-u16Counter ) == NOK)
	{
		return 0;
	}

	return u16ReceivedDataSize;
}



/****************************************************************************************/
/* Description: Sends a post request													*/
/* Input      : const u8* pu8URL				                                        */
/*              Description: The URL/IP to send the request to							*/
/* 				Range: array of u8														*/
/* Output     : Error_Status			                                                */
/*				Description: It returns OK if the Action cmd response contains '200'	*/
/*							 Otherwise it return NOK									*/
/*				Range: OK, NOK															*/
/* 				u32 * pu32DataSize														*/
/* 				Desicription: It return the received data size by reference 			*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
Error_Status GSM_enuPOSTRequestInit(const u8* pu8URL, const u8* postRequestData, u8* responseData, u32 * pu32DataSize)

{
	u32 u32Counter = 0;
	volatile u8 au8ResponseBuffer[64] = {0};		/* \r\nOK\r\n or \r\nERROR\r\n */
	Error_Status enuErrorCheck = OK;
	Error_Status enuServerStatus;
	u32 u32count=0;
	enuErrorCheck = enuSendCommand("AT+HTTPPARA=\"content\",\"application/json\"");
	*pu32DataSize = 0;

	/*Send URL*/
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8ResponseBuffer, 64 );
	USART_voidSendString(GSM_u8USARTChannel, "AT+HTTPPARA=\"URL\",\"");
	USART_voidSendString(GSM_u8USARTChannel, pu8URL);
	USART_voidSendString(GSM_u8USARTChannel, "\"\r\n");

	while (!u8CheckBufferTermination(au8ResponseBuffer, 9, 2));
	DMA_voidDisable(DMA_CHANNEL_5);

	vidClearBuffer(au8ResponseBuffer, 64);

	/*Send HTTP POST request data*/
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8ResponseBuffer, 64 );
	USART_voidSendString(GSM_u8USARTChannel, "AT+HTTPDATA=100,10000");
	USART_voidSendString(GSM_u8USARTChannel, "\r\n");
	enuErrorCheck=NOK;
	while(enuErrorCheck == NOK && u32count<1000)
	{
		enuErrorCheck=enuFindString(au8ResponseBuffer, "DOWNLOAD", 12);
		u32count++;
	}
	while ( !u8CheckBufferTermination( au8ResponseBuffer, 64, 2 ) );
	//send data
	USART_voidSendString(GSM_u8USARTChannel, postRequestData);
//	USART_voidSendString(GSM_u8USARTChannel, "\r\n");
	while ( !u8CheckBufferTermination( au8ResponseBuffer, 64, 4 ) );
	DMA_voidDisable( DMA_CHANNEL_5 );

	vidClearBuffer(au8ResponseBuffer, 64);
	/*Send ACTION cmd */
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8ResponseBuffer, 64 );
	USART_voidSendString(GSM_u8USARTChannel, "AT+HTTPACTION=1");
	USART_voidSendString(GSM_u8USARTChannel, "\r\n");
	while ( !u8CheckBufferTermination( au8ResponseBuffer, 64, 4 ) );
	DMA_voidDisable( DMA_CHANNEL_5 );

	/*check if the Response status is 200 */
	if ( au8ResponseBuffer[23] == '2' && au8ResponseBuffer[24] == '0' && au8ResponseBuffer[25] == '0' )
	{
		//Request and response are OK
		//get File size
		for (u32Counter = 27; au8ResponseBuffer[u32Counter] != '\r'; u32Counter++)
		{
			*pu32DataSize = ((*pu32DataSize)* 10) + (au8ResponseBuffer[u32Counter] - '0');
		}
		return OK;
	}
	else
	{
		//Connection failed
		return NOK;
	}
}


/** FTP Functions **/

/*
 * @brief it serves GSM_enumFTPRequest function only to send some commands
 * @param pu8Command: command to transmit
 * @param parameter: parameters included in the command
 * 					if parameter existed --> provide it
 * 					if not existed --> write NULL
 */
static Error_Status GSM_enumSendFTPCommand( const u8* pu8Command, const u8* parameter) {
	u8 buffer[9];	/* \r\nOK\r\n or \r\nERROR\r\n */
	vidClearBuffer(buffer, 9);
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) buffer, 9 );

	if( parameter != nullPointer ) {
		USART_voidSendString(GSM_u8USARTChannel, pu8Command);
		USART_voidSendString(GSM_u8USARTChannel, "=\"");
		USART_voidSendString(GSM_u8USARTChannel, parameter);
		USART_voidSendString(GSM_u8USARTChannel, "\"\r\n");
	} else {}

	while ( !u8CheckBufferTermination( buffer, 9, 2 ) );
	DMA_voidDisable(DMA_CHANNEL_5);

	if (enuFindString( buffer, "OK", 9 ) == NOK) {
		return NOK;
	}

	return OK;
}

/**
 * @brief  		Sends a FTP request and dynamically receives the response in a buffer
 * @param 	URL: 					The URL/IP to send the request to
 * @param  userName:       request username
 * @param  passWord:       request password
 * @param	response: 			The address of the buffer to put back the response into
 * @param	responseSize: The buffer size
 * @retval 	Error_Status
 */
Error_Status GSM_enumFTPInit(const u8* URL,const u8* userName, const u8* passWord, const u8* fileName, const u8* filePath, u8* fileData, DownloadConfig downloadConfig) {

	u8 buffer[100];
	volatile u8 response[200];
	u8 x;

	enuSendCommand("AT+FTPCID=1");							/* SET FTP BEARER PROFILE IDENTIFIER */
	//GSM_enumSendFTPCommand("AT+FTPSSL", 2);					/* Enable Secure FTP */
	//GSM_enumSendFTPCommand("AT+FTPPORT", FTPPORT);			/* Send cmd "AT+FTPPORT=21*/
	vidClearBuffer(buffer,100);
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) buffer, 100 );
	USART_voidSendString(GSM_u8USARTChannel, "AT+FTPPORT=21");
	USART_voidSendChar(GSM_u8USARTChannel, '\r');
	USART_voidSendChar(GSM_u8USARTChannel, '\n');

	while ( !u8CheckBufferTermination( buffer, 100, 2 ) );
	DMA_voidDisable(DMA_CHANNEL_5);

	if (enuFindString( buffer, "OK", 100 ) == NOK) {
		return NOK;
	}
	GSM_enumSendFTPCommand("AT+FTPSERV", URL);					/* Send cmd "AT+FTPSERV="URL"*/
	GSM_enumSendFTPCommand("AT+FTPUN", userName);				/* Send cmd "AT+FTPUN="userName"*/
	GSM_enumSendFTPCommand("AT+FTPPW", passWord);				/* Send cmd "AT+FTPPW="passWord"*/
	GSM_enumSendFTPCommand("AT+FTPGETNAME", fileName);			/* Send cmd "AT+FTPGETNAME="fota.hex""*/
	GSM_enumSendFTPCommand("AT+FTPGETPATH", filePath);			/* Send cmd "AT+FTPGETPATH="/htdocs/""*/

	switch(downloadConfig)
	{
	case Standard:
		/* Send pu8Command "AT+FTPGET=1"*/
		vidClearBuffer(buffer,100);
		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) buffer, 100 );
		USART_voidSendString(GSM_u8USARTChannel, "AT+FTPGET=1");
		USART_voidSendChar(GSM_u8USARTChannel, '\r');
		USART_voidSendChar(GSM_u8USARTChannel, '\n');

		while ( !u8CheckBufferTermination( buffer, 200, 4) );
		DMA_voidDisable(DMA_CHANNEL_5);

		if (enuFindString( buffer, "+FTPGET: 1,1", 100 ) == NOK)
		{
			return NOK;
		}
		break;
	case Extended:
		/* Send pu8Command "AT+FTPGET=1"*/
		vidClearBuffer(buffer,100);
		USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) buffer, 100 );
		USART_voidSendString(GSM_u8USARTChannel, "AT+FTPEXTGET=1");
		USART_voidSendChar(GSM_u8USARTChannel, '\r');
		USART_voidSendChar(GSM_u8USARTChannel, '\n');

		while ( !u8CheckBufferTermination( buffer, 200, 4) );
		DMA_voidDisable(DMA_CHANNEL_5);

		if (enuFindString( buffer, "+FTPEXTGET: 1,0", 100 ) == NOK)
		{
			return NOK;
		}
		break;
	}




	return OK;
}


Error_Status GSM_enumFTPGet(u8 * fileData)
{
	u8 response[1500] = {0};
	/* Execute GET request */
	/* Send cmd "AT+FTPGET=2,1024"*/
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) response,1500);
	USART_voidSendString(GSM_u8USARTChannel, "AT+FTPGET=2,1460");
	USART_voidSendChar(GSM_u8USARTChannel, '\r');
	USART_voidSendChar(GSM_u8USARTChannel, '\n');

	//	while (enuFindString( response, "+FTPGET: 1,0", 200 ) == NOK);
	while ( !u8CheckBufferTermination( response, 1500, 6) );
	DMA_voidDisable(DMA_CHANNEL_5);
	getResponseData(response, fileData);

}
Error_Status GSM_enumFTPGetExtended(u8 * fileData, u32 size, u32 startPoint)
{
	u8 response[1500] = {0};
	u8  startpointascii[10] = {0};
	u8 sizeascii[10] = {0};
	u8 counter = 0;
	for (counter = 10; counter > 0; counter--)
	{
		if (size != 0)
		{
			sizeascii[counter-1] = (size % 10) + 48;
			size = size/10;
		}
		if (startPoint != 0)
		{
			startpointascii[counter-1] = (startPoint % 10) + 48;
			startPoint = startPoint/10;
		}
		if ( (size == 0) && (startPoint == 0) )
		{
			break;
		}
	}

	/* Execute GET Extended request */
	/* Send cmd "AT+FTPEXTGET=3,startpoint,length"*/
	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) response,1500);
	USART_voidSendString(GSM_u8USARTChannel, "AT+FTPEXTGET=3,");
	USART_voidSendString(GSM_u8USARTChannel, startpointascii);
	USART_voidSendString(GSM_u8USARTChannel, ",");
	USART_voidSendString(GSM_u8USARTChannel, sizeascii);
	USART_voidSendChar(GSM_u8USARTChannel, '\r');
	USART_voidSendChar(GSM_u8USARTChannel, '\n');

	//	while (enuFindString( response, "+FTPGET: 1,0", 200 ) == NOK);
	while ( !u8CheckBufferTermination( response, 1500, 6) );
	DMA_voidDisable(DMA_CHANNEL_5);
	getResponseData(response, fileData);
}





/******************************************/
/***********Private Functions**************/
/******************************************/



/****************************************************************************************/
/* Description: Interrupt Handler for the DMA					 						*/
/* Input      : Void			                                                        */
/* Output     : Void		                                                            */
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidDMAInterruptHandler(void)
{
	if (pu8UARTBuffer == (void*)0)
	{
		return;
	}
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
/* Description: Sends Command through UART and wait for response "\r\nOK\r\n"			*/
/* Input      : const u8* pu8Command                                                    */
/*              Description: Command to be sent							                */
/* 				Range: 	pointer to u8													*/
/* Output     : Error_Status        			                                        */
/*				Range: NOK if "\r\nOK\r\n is not received, OK if "\r\nOK\r\n is received*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
static Error_Status enuSendCommand(const u8* pu8Command)
{
	volatile u8 buffer[11] = {0};		/* 	\r\nOK\r\n or \r\nERROR\r\n	or ATE0\r\nOK\r\n	*/

	USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) buffer, 11 );

	/* Send the AT command */
	USART_voidSendString(GSM_u8USARTChannel, pu8Command);
	USART_voidSendChar(GSM_u8USARTChannel, '\r');
	USART_voidSendChar(GSM_u8USARTChannel, '\n');

	// Wait for starting and terminating /r/n
	while ( !u8CheckBufferTermination(  buffer, 11, 2 ) );
	DMA_voidDisable(DMA_CHANNEL_5);
	return enuFindString( buffer, "OK", 11 );
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

/*
 * @brief it takes the row data response frame from GSM Sim800l module then extract the required data from it and copy it to fileData array
 * @param response: the received row data from GSM array
 * @param fileData: the required data extracted from the received frame
 * @return OK-> if data is available
 * 		   NOK-> if data is not available
 */

static Error_Status getResponseData(u8 * response, u8 * fileData)
{
	u8 repeat = 0;
	u32 i;

	if(response[13] == '0')
	{
		return NOK;
	}

	for (i = 0; i < 1000; i++)
	{
		if (response[i] == '\r' && response[i + 1] == '\n')
		{
			repeat++;
			i ++;
		}

		// If we found staring and terminating /r/n  or if we exceeded the buffer
		if (i >= 1000 || repeat == 2)
		{
			i++;
			break;
		}

	}
	for (u32 j=0; j<1000; j++)
	{
		fileData[j]=response[i];
		i++;
		if (response[i] == '\r' && response[i + 1] == '\n')
		{
			break;
		}

	}

	return OK;

}

