/*
 * FLASH_prog.c
 *
 *  Created on: Sep 26, 2019
 *      Author: sondo
 */

#include "util.h"
#include "STD_Types.h"
//#include "DEBUG_int.h"
#include "FLASH_priv.h"
#include "FLASH_cfg.h"
#include "FLASH_int.h"


/*****************************************/
/***********Public Variables**************/
/*****************************************/
const u8 u8Version[]= "V01";


/*****************************************/
/***********Public Functions**************/
/*****************************************/


/****************************************************************************************/
/* Description: Log the Driver Version													*/
/* Input      : Void																	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
//void Flash_vidGetVersionInfo(void)
//{
//	Debug_LogVersion(u8Version);
//}


/****************************************************************************************/
/* Description: Write one word in the Flash Memory										*/
/* Input      : u32* pu32address		                                	            */
/*              Description: Address to write in the flash		                        */
/*				u32 u32value															*/
/*              Description: Word to write in flash			                 		    */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void FLASH_vidWriteWord(u32* pu32address, u32 u32value)
{
	u16* address = (u16*)pu32address;
	/* Perform Unlock Sequence */
	if (GET_BIT(FLASH_CR,LOCK) == FLASH_u8LOCKED)
	{
		FLASH_KEYR = FLASH_u32KEY1;
		FLASH_KEYR = FLASH_u32KEY2;
	}
	/* Set Programming Bit */
	SET_BIT(FLASH_CR, PG);
	/* Put first half-word int he address */
	*address = (u16)(u32value & HALFWORDMASK);
	/* Wait for the busy flag */
	while (GET_BIT(FLASH_SR,BSY) == FLASH_u8BSY);
	/* Write second half-word in the address */
	*(address+1) = (u16)(u32value >> HALFWORDOFFSET);
	/* Wait for busy bit */
	while (GET_BIT(FLASH_SR,BSY) == FLASH_u8BSY);
	/* Reset programming Bit */
	CLR_BIT(FLASH_CR,PG);
}

/****************************************************************************************/
/* Description: Write an array in the Flash memory										*/
/* Input      : u32* pu32address		                                	            */
/*              Description: address to write in the flash		                        */
/*				u32* pu32array															*/
/*              Description:array address to write in flash			                    */
/*				u8 u8arraysize															*/
/*              Description: Size of the array to write in the flash		            */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void FLASH_vidWriteArray(u32* pu32address, u32* pu32array, u8 u8arraysize)
{
	u8 u8counter = 0;
	u16* address = (u16*)pu32address;
	/* Perform Unlock Sequence */
	if (GET_BIT(FLASH_CR,LOCK) == FLASH_u8LOCKED)
	{
		FLASH_KEYR = FLASH_u32KEY1;
		FLASH_KEYR = FLASH_u32KEY2;
	}
	/* Set Programming Bit */
	SET_BIT(FLASH_CR, PG);

	for (u8counter = 0 ; u8counter < u8arraysize; u8counter++)
	{
		/* Put first half-word in the address */
		*(address+(u8counter*2)) = (u16)(pu32array[u8counter] & HALFWORDMASK);
		/* Wait for the busy flag */
		while (GET_BIT(FLASH_SR,BSY) == FLASH_u8BSY);
		/* Write second half-word in the address */
		*(address+1+(u8counter*2)) = (u16)(pu32array[u8counter] >> HALFWORDOFFSET);
		/* Wait for busy bit */
		while (GET_BIT(FLASH_SR,BSY) == FLASH_u8BSY);
	}
	/* Reset programming Bit */
	CLR_BIT(FLASH_CR,PG);
}


/****************************************************************************************/
/* Description: Erase Page in Flash Memory												*/
/* Input      : u8 u8PageNumber		                                	               	*/
/*              Description: Page to erase in the Flash			                        */
/*				Range: 0 ~ 127															*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void FLASH_vidErasePage(u8 u8PageNumber)
{
	u32 u32FlashBaseAddress = FLASH_u32BASEADDRESS;
	/* Perform Unlock Sequence */
	if (GET_BIT(FLASH_CR,LOCK) == FLASH_u8LOCKED)
	{
		FLASH_KEYR = FLASH_u32KEY1;
		FLASH_KEYR = FLASH_u32KEY2;
	}
	/* Set Erase Bit */
	SET_BIT(FLASH_CR, PER);
	/* Wait for busy bit */
	while (GET_BIT(FLASH_SR,BSY) == FLASH_u8BSY);
	/* Write page address in the Address Register*/
	FLASH_AR = u32FlashBaseAddress + (u32)(FLASH_u16PAGESIZE * (u16)u8PageNumber);
	/* Set Start Bit */
	SET_BIT(FLASH_CR, STRT);
	/* Wait for Busy Flag */
	while (GET_BIT(FLASH_SR,BSY) == FLASH_u8BSY);
	/* Reset Erase Bit */
	CLR_BIT(FLASH_CR, PER);

}


/****************************************************************************************/
/* Description: Read one word from the Flash Memory										*/
/* Input      : u32* pu32address		                                	            */
/*              Description: Address to read in the flash		                        */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
u32 FLASH_u32ReadWord(u32* pu32address)
{
	return *(pu32address);
}


/****************************************************************************************/
/* Description: Read an array from the Flash memory										*/
/* Input      : u32* pu32address		                                	            */
/*              Description: address to read from the flash		                        */
/*				u32* pu32array															*/
/*              Description:array address to put in data from flash			            */
/*				u8 u8arraysize															*/
/*              Description: Size of the array to read from the flash		            */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void FLASH_vidReadArray(u32* pu32address, u32* pu32array, u8 u8arraysize)
{
	u8 u8counter = 0;
	for (u8counter = 0; u8counter < u8arraysize; u8counter++)
	{
		pu32array[u8counter] = *(pu32address + u8counter);
	}
}

