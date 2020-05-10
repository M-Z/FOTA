/*
 * Application.h
 *
 *  Created on: 13 Mar 2020
 *      Author: Michael
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

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
Update_Status serverResponseHandling(u8 * pu8ServerResponse);

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
Update_Status updateVersioncheck(u8* pu8ServerResponse, u8* pu8CurrentECUVersion);

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
s32 STM32_SHA256_HASH_DigestCompute(u8* InputMessage, u32 InputMessageLength, u32 *MessageDigest, s32* MessageDigestLength);

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
TestStatus Buffercmp(u8 pBuffer[], u8* pBuffer1 );


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
static Error_Status enuFindString2(u8* pu8Buffer, const u8* pu8ExpectedString, u32 u32Size);

/****************************************************************************************/
/* Description: It convert version ID from string form to major, minor and patch values */
/* Input      : const u8 * au8version                                                   */
/*              Description: string which contain file version in the following  	    */
/*  					     form "vmajor.minor.patch" (Ex: "v2.1.5")			        */
/* 				Range: 	pointer to u8 array of characters								*/
/* Output     : void                                                            		*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
void vidGetVersion(const u8 * au8version, u16 *major, u16 *minor, u16 *patch);

/****************************************************************************************/
/* Description: It converts array of ASCII number to its integer value  				*/
/* Input      : const u8 * pu8txt                                                       */
/*              Description: string of number needed to be converted to integer value  	*/
/* 				Range: 	pointer to u8 array of characters								*/
/* Output     : void                                                            		*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/
u32 u32ACIItoInteger(u8* pu8txt);

/****************************************************************************************/
/* Description: Security Stack function 												*/
/* Input      : void * dest                                                             */
/*              const void *src															*/
/* 				s32 n																	*/
/* Output     : void                                                            		*/
/* Scope      : Private                                                                	*/
/****************************************************************************************/

void __aeabi_memcpy (void *dest, const void *src, s32 n);

#endif /* APPLICATION_H_ */
