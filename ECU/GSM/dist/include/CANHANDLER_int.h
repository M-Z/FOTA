/*
 * CANHANDLER_int.h
 *
 *  Created on: Feb 5, 2020
 *      Author: sondo
 */

#ifndef CANHANDLER_INT_H_
#define CANHANDLER_INT_H_

extern u8 CANHANDLER_u8SWVersionReceived;
extern u8 CANHANDLER_u8UpdateAcceptReceived;
extern u8 CANHANDLER_u8NextMsgRequest;
extern u8 CANHANDLER_u8FlashBankReceived;
extern u8 CANHANDLER_u8DTCsReceived;

extern u8 CANHANDLER_au8ECUVersion[8];
extern u8 CANHANDLER_au8DTCs[8];
extern u8 CANHANDLER_u8UsedBank;

/*****************************************/
/***********Public Definitions************/
/*****************************************/
/* Can Frame Types Definitions */
#define CAN_u8REMOTEFRAME 1
#define CAN_u8DATAFRAME 0

/*****************************************/
/***********Public Functions**************/
/*****************************************/
/****************************************************************************************/
/* Description: Send Can Message
 */
/* Input      : u8 u8MessageID */
/*              Description: ID of the message to send over CAN */
/* 				Range: 	u8
 */
/*				u8 u8Frame
 */
/*              Description: Type of Frame
 */
/* 				Range: 	CAN_u8REMOTEFRAME, CAN_u8DATAFRAME
 */
/*				u8* pu8Data
 */
/*              Description: Array containing data to send over CAN, NULL if
 * Remote Fram*/
/* 				Range: 	u8*
 */
/*				u8 u8DataLength
 */
/*              Description: Length of Data to be sent in bytes
 */
/* 				Range: 	0 ~ 8
 */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void CANHANDLER_vidSend(u8 u8MessageID, u8 u8Frame, u8 *pu8Data,
                        u8 u8DataLength);

/****************************************************************************************/
/* Description: Send Can Message Task
 */
/* Input      : u8 u8MessageID */
/*              Description: ID of the message to send over CAN */
/* 				Range: 	u8
 */
/*				u8 u8Frame
 */
/*              Description: Type of Frame
 */
/* 				Range: 	CAN_u8REMOTE, CAN_u8DATA
 */
/*				u8* pu8Data
 */
/*              Description: Array containing data to send over CAN, NULL if
 * Remote Fram*/
/* 				Range: 	u8*
 */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void CANHANDLER_vidSendTask(void);

/****************************************************************************************/
/* Description: Receive Can Message
 */
/* Input      : Void
 */
/* Output     : Void */
/* Scope      : Public */
/****************************************************************************************/
void CANHANDLER_vidReceive(void);

#endif /* CANHANDLER_INT_H_ */
