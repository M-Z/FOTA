/*
 * Application.h
 *
 *  Created on: 13 Mar 2020
 *      Author: Michael
 */

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "crypto.h"
#include "Application.h"

/***********************************************************************************************************************/
/********************************************Public Functions***********************************************************/
/***********************************************************************************************************************/

/********************************************************************************************************************/
/* Description: Check update request status in Server response 														*/
/* Input      : u8 * pu8ServerResponse                                        							            */
/*              Description: pointer to server response																*/
/* Output     : Update_Status                                                  							            */
/*				Range: checkupdate: if the respond with file update version											*/
/* 					   VehicleNotFound: if the user name in the update POST request not found in server database	*/
/* 					   Incorrect password: if the password in the update POST request is incorrect					*/
/* Scope      : Public                                                                 								*/
/********************************************************************************************************************/
Update_Status serverResponseHandling(u8 * pu8ServerResponse)
{
	u8 au8UpdateStatus1[]={"Vehicle not found"};
	u8 au8UpdateStatus2[]={"Incorrect password"};
	Error_Status enuCmpStatus = OK;

	enuCmpStatus = enuFindString2(pu8ServerResponse, au8UpdateStatus1, 100);
	if(enuCmpStatus == OK)
	{
		return VehicleNotFound;
	}
	enuCmpStatus = enuFindString2(pu8ServerResponse, au8UpdateStatus2, 100);
	if(enuCmpStatus == OK)
	{
		return IncorrectPassword;
	}

	return checkupdate;

}

/********************************************************************************************************************/
/* Description: It compare a certain file version on the server and the existing version on a certain ECU			*/
/* Input      : u8 * pu8ServerResponse                                        							            */
/*              Description: pointer to server response which contain a certain file version						*/
/* 				u8 *  pu8CurrentECUVersion																			*/
/* 				Description: pointer to a certain ECU software version string which is must be written in the		*/
/* 							 following form "vmajor.minor.patch" (Ex: "v2.1.5")										*/
/* Output     : Update_Status                                                  							            */
/*				Range: updateNotExist: if the update version and the existing software version on a certain			*/
/* 					   				   ECU are the same																*/
/* 					   updateExist: if the update version is newer than the existing software version on			*/
/* 									a certain ECU																	*/
/* 					   updateRollbackExis: if the existing software version on a certain ECU is newer than			*/
/*  									   the update version														*/
/* Scope      : Public                                                                 								*/
/********************************************************************************************************************/
Update_Status updateVersioncheck(u8* pu8ServerResponse, u8* pu8CurrentECUVersion)
{
	/*index [0] -> major, [1]-> minor, [2]->patch*/
	u16 currentECUversion[3];
	u16 serverFileversion[3];
	vidGetVersion(pu8CurrentECUVersion, &currentECUversion[0], &currentECUversion[1], &currentECUversion[2]);
	vidGetVersion(pu8ServerResponse, &serverFileversion[0], &serverFileversion[1], &serverFileversion[2]);
	if (serverFileversion[0] == currentECUversion[0] && serverFileversion[1] == currentECUversion[1] && serverFileversion[2] == currentECUversion[2])
	{
		return updateNotExist;
	}
	if(serverFileversion[0] > currentECUversion[0])
	{
		return updateExist;
	}
	else if(serverFileversion[0] < currentECUversion[0])
	{
		return updateRollbackExist;
	}
	if(serverFileversion[1] > currentECUversion[1])
	{
		return updateExist;
	}
	else if(serverFileversion[1] < currentECUversion[1])
	{
		return updateRollbackExist;
	}
	if(serverFileversion[2] > currentECUversion[2])
	{
		return updateExist;
	}
	else if(serverFileversion[2] < currentECUversion[2])
	{
		return updateRollbackExist;
	}
}


/******************************************************************************************************************/
/* Description: It compute HASH digest code according to SHA256	(Security stack)							      */
/* Input      :	u8 * InputMessage                                                       						  */
/*              Description: pointer to input message to be hashed												  */
/*				u32 InputMessageLength													                          */
/*				Description: input data message length in byte 							                          */
/* 				u32 *MessageDigest														                          */
/* 				Description: pointer to output parameter that will handle message digest                          */
/* 				s32* MessageDigestLength												                          */
/* 				Description:  pointer to output digest length							                          */
/*  Output    : error status															                          */
/*  			Range: HASH_SUCCESS if success											                          */
/*        			   HASH_ERR_BAD_PARAMETER,  										                          */
/*				       HASH_ERR_BAD_CONTEXT,											                          */
/*         		  	   HASH_ERR_BAD_OPERATION if error occured.                                                   */
/* Scope      : Public                                                                	                          */
/******************************************************************************************************************/
s32 STM32_SHA256_HASH_DigestCompute(u8* InputMessage, u32 InputMessageLength, u32 *MessageDigest, s32* MessageDigestLength)
{
  SHA256ctx_stt P_pSHA256ctx;
  s32 error_status  = HASH_SUCCESS;

  /* Set the size of the desired hash digest */
  P_pSHA256ctx.mTagSize = CRL_SHA256_SIZE;

  /* Set flag field to default value */
  P_pSHA256ctx.mFlags = E_HASH_DEFAULT;

  error_status = SHA256_Init(&P_pSHA256ctx);

  /* check for initialization errors */
  if (error_status == HASH_SUCCESS) {
    /* Add data to be hashed */
    error_status = SHA256_Append(&P_pSHA256ctx,
                                 InputMessage,
                                 InputMessageLength);

    /* retrieve */
    if (error_status == HASH_SUCCESS) {
      error_status = SHA256_Finish(&P_pSHA256ctx, MessageDigest, MessageDigestLength);
    }
  }

  return error_status;
}


/**************************************************************************************************************************/
/* Description: Compares Expected output which is extracted from server response with the generated Hash digest code      */
/* note 	  : not designed for general buffer comparisons, its specific design for handling the mismatching  			  */
/* 				between the received server format and the generated hex Hash code 										  */
/* Input      : u8 pBuffer[]                                                      									  	  */
/*              Description: Expected output which is extracted from server response as ASCII string array				  */
/* 				Range	   : string of 64 ASCII characters																  */
/* 				u8* pBuffer1																							  */
/* 				Description: pointer to the generated Hash digest code													  */
/* 				Range 	   : 32 bytes of 32 double digit hex number														  */
/* Output     : TestStatus																								  */
/* 				Range: TestStatus																	                	  */
/* 					   PASSED if the two hash codes are the same                                                          */
/* 					   FAILED if the two hash codes are different                                                         */
/* Scope      : Public                                                           								          */
/**************************************************************************************************************************/
TestStatus Buffercmp(u8 pBuffer[], u8* pBuffer1 )
{
	u8 hex_ptr;

	for (int i = 1; i < 32; i += 2) {
		hex_ptr = (pBuffer[i - 1] <= '9') ? ( pBuffer[i - 1] - '0' ) * 16 : (pBuffer[i - 1] - 'a' + 10) * 16;
		hex_ptr += (pBuffer[i] <= '9') ? ( pBuffer[i] - '0' ) : (pBuffer[i] - 'a' + 10) ;
		if ( hex_ptr  != *(pBuffer1++) ) {
			return FAILED;
		}
   }
	return PASSED;
}

/**************************************************************************************************************************/
/********************************************Private Functions************************************************************/
/************************************************************************************************************************/


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
static Error_Status enuFindString2(u8* pu8Buffer, const u8* pu8ExpectedString, u32 u32Size)
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
/* Description: It convert version ID from string form to major, minor and patch values */
/* Input      : const u8 * au8version                                                   */
/*              Description: string which contain file version in the following  	    */
/*  					     form "vmajor.minor.patch" (Ex: "v2.1.5")			        */
/* 				Range: 	pointer to u8 array of characters								*/
/* Output     : void                                                            		*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidGetVersion(const u8 * au8version, u16 *major, u16 *minor, u16 *patch)
{
	int count;
	char temp=0;
	char temp2[10];
	char dotCount=0;

	for(count=0; count<100; count++)
	{
	    if(au8version[count+1]=='.' || au8version[count+1]=='\0')
	    {
	        temp2[temp]='\0';
	        dotCount++;
	        temp=0;
	        count++;
	        if(dotCount == 1)
	        {
	            *major=u32ACIItoInteger(temp2);
	        }
	        else if(dotCount == 2)
	        {
	            *minor=u32ACIItoInteger(temp2);
	        }
	        else if(dotCount == 3)
	        {
	            *patch=u32ACIItoInteger(temp2);
	        }
	    }
	         temp2[temp]=au8version[count+1];
	         temp++;
	    if(au8version[count] == '\0')
	    {
	        break;
	    }

	}
}

/****************************************************************************************/
/* Description: It converts array of ASCII number to its integer value  				*/
/* Input      : const u8 * pu8txt                                                       */
/*              Description: string of number needed to be converted to integer value  	*/
/* 				Range: 	pointer to u8 array of characters								*/
/* Output     : void                                                            		*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
u32 u32ACIItoInteger(u8* pu8txt)
{
    u16 sum,digit,i;
    u8 u8strlength=0;
	sum=0;
	while(pu8txt[u8strlength] != '\0')
	{
		u8strlength++;
	}
	for(i=0; i < u8strlength; i++)
	{
		digit=pu8txt[i]-0x30;
		sum=(sum*10)+digit;
	}
	return sum;
}
/****************************************************************************************/
/* Description: Security Stack function 												*/
/* Input      : void * dest                                                             */
/*              const void *src															*/
/* 				s32 n																	*/
/* Output     : void                                                            		*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/

void __aeabi_memcpy (void *dest, const void *src, s32 n)
{
	memcpy (dest, src, n);
}
