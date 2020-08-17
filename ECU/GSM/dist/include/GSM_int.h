#ifndef GSM_INT_H_
#define GSM_INT_H_

/**************** FTP Download Configuartions ******************/
typedef enum { Standard, Extended } DownloadConfig;

/*****************************************/
/*********Public Definitions*************/
/*****************************************/
extern u8 GSM_u8USARTChannel;

/*****************************************/
/***********Public Functions**************/
/*****************************************/

/****************************************************************************************/
/* Description: Checks to see if GSM module is connected to UARTx and disable
 */
/* 				notifications, echo, calls
 */
/* Input      : u8 u8GSMUARTChannel */
/*              Description: The UART Channel the GSM is connected to
 */
/* 				Range:	USART_CHANNEL_1,	USART_CHANNEL_2,
 * USART_CHANNEL_3			*/
/*						USART_CHANNEL_4,	USART_CHANNEL_5
 */
/* Output     : Error_Status */
/*				Range: OK if initialization succeeded, NOK if failed
 */
/* Scope      : Public */
/****************************************************************************************/
Error_Status GSM_enuInit(u8 u8GSMUARTChannel);

/****************************************************************************************/
/* Description: Opens HTTP connection and configures it
 */
/* Input      : Void */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void GSM_vidInitHTTP(void);

/****************************************************************************************/
/* Description: Sends a get request
 */
/* Input      : const u8* pu8URL */
/*              Description: The URL/IP to send the request to
 */
/* 				Range: array of u8
 */
/* Output     : u32 */
/*				Description: Number of characters received from the
 * Request				*/
/*				Range: u32
 */
/* Scope      : Public */
/****************************************************************************************/
u32 GSM_enuGETRequestInit(const u8 *pu8URL);

/****************************************************************************************/
/* Description: Gets Data after the get request
 */
/* Input      : u32 u32StartPoint */
/*              Description: Start Point in the file to get the data from
 */
/* 				Range: 0 ~ u32
 */
/*				u16 u16DataLength
 */
/*              Description: Length of data to return
 */
/* 				Range: 0 ~ u32
 */
/*				u8* au8Data
 */
/*              Description: Array to return the data in
 */
/* Output     : u16 */
/*				Description: Length of the data returned
 */
/*				Range:0 ~ u16DataLength
 */
/* Scope      : Public */
/****************************************************************************************/
u16 GSM_u16GETData(u32 u32StartPoint, u16 u16DataLength, u8 *au8Data);

/****************************************************************************************/
/* Description: Sends a post request
 */
/* Input      : const u8* pu8URL */
/*              Description: The URL/IP to send the request to
 */
/* 				Range: array of u8
 */
/* Output     : Error_Status */
/*				Description: It returns OK if the Action cmd response
 * contains '200'	*/
/*							 Otherwise it return NOK
 */
/*				Range: OK, NOK
 */
/* 				u32 * pu32DataSize
 */
/* 				Desicription: It return the received data size by
 * reference 			*/
/* Scope      : Public */
/****************************************************************************************/
Error_Status GSM_enuPOSTRequestInit(const u8 *pu8URL, const u8 *postRequestData,
                                    u8 *responseData, u32 *pu32DataSize);

/** FTP Functions **/

/*
 * @brief it serves GSM_enumFTPRequest function only to send some commands
 * @param pu8Command: command to transmit
 * @param parameter: parameters included in the command
 * 					if parameter existed --> provide it
 * 					if not existed --> write NULL
 */
static Error_Status GSM_enumSendFTPCommand(const u8 *pu8Command,
                                           const u8 *parameter);

/**
 * @brief  		Sends a FTP request and dynamically receives the response
 * in a buffer
 * @param 	URL: 					The URL/IP to send the request
 * to
 * @param  userName:       request username
 * @param  passWord:       request password
 * @param	response: 			The address of the buffer to put back the
 * response into
 * @param	responseSize: The buffer size
 * @retval 	Error_Status
 */
Error_Status GSM_enumFTPInit(const u8 *URL, const u8 *userName,
                             const u8 *passWord, const u8 *fileName,
                             const u8 *filePath, u8 *fileData,
                             DownloadConfig downloadConfig);

Error_Status GSM_enumFTPGet(u8 *fileData);

Error_Status GSM_enumFTPGetExtended(u8 *fileData, u32 size, u32 startPoint);

/*
 * @brief it takes the row data response frame from GSM Sim800l module then
 * extract the required data from it and copy it to fileData array
 * @param response: the received row data from GSM array
 * @param fileData: the required data extracted from the received frame
 * @return OK-> if data is available
 * 		   NOK-> if data is not available
 */

static Error_Status getResponseData(u8 *response, u8 *fileData);

#endif /* GSM_INT_H_ */
