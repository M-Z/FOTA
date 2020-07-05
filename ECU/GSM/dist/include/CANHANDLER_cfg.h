/*
 * CANHANDLER_cfg.h
 *
 *  Created on: Feb 5, 2020
 *      Author: sondo
 */

#ifndef CANHANDLER_CFG_H_
#define CANHANDLER_CFG_H_

/* Description:	Maximum Number of Filters ion filters array					*/
/* Range:		1 ~ 13														*/
#define CANHANDLER_u8MAXFILTERNUMBERS		6


/* Description:	Tx Message IDs												*/
/* Range:		u8															*/
#define CANHANDLER_u8UPDATEREQUESTID		40	//remote from main to app (to reset)
#define CANHANDLER_u8HEXFILEID				45	//data from main to app (sending the hex file)
#define CANHANDLER_u8UPDATEREQUESTGUI		65	//remote from main to gui(ask user to accept update)
#define CANHANDLER_u8UPDATEPROGRESS			75	//data from main to gui (the update progress for progress bar)
#define CANHANDLER_u8GETFLASHBANK			90
#define CANHANDLER_u8GSMBUSY				20	//remote to gui to display gsm is busy and cannot send diag

/* Description:	Rx Message IDs												*/
/* Range:		u8															*/
#define CANHANDLER_u8GUIUPDATEACCEPT		70	//remote from gui to main (user accept update)
#define CANHANDLER_u8ECUSWVERSION			80	//remote from main to app (request SW version ID on ECU) , data from app to main (the SW version)
#define CANHANDLER_u8NEXTMSGREQUEST			60	//remote from app to main (feedback after receiving file)
#define CANHANDLER_u8ECUDTCs				25  //data from app to main

#endif /* CANHANDLER_CFG_H_ */
