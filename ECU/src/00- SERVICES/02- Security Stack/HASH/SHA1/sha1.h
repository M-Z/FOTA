/**
  ******************************************************************************
  * @file    sha1.h
  * @author  MCD Application Team
  * @version V2.0.6
  * @date    25-June-2013
  * @brief   Provides SHA1 functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************/

/*! \page Tutorial_SHA1 SHA1 Tutorial
  *
  * Here follows an example of SHA1 functionality.
  * Please remember that before starting to call the Init function the context \b requires user 
  * initialization. The mFlags and mTagSize member must be initialized prior to calling the 
  *  init function. Look at the each function documentation to see what is needed prior of calling.
  *
  * The API functions to be used are:
  *  - \ref SHA1_Init initialize an \ref SHA1ctx_stt context with required digest size and flags.
  *  - \ref SHA1_Append process input buffers.
  *    It can be called multiple times.
  *  - \ref SHA1_Finish can be called only one time for the digest generation process.
  *
  * The following code performs a SHA1 hash of a buffer of size 1024 in 1024 Append calls, each processing 1 byte of the message.
  * \code
  * #include <stdio.h>
  * #include "crypto.h"
  * int32_t main()
  * {
  *   uint8_t message[1024]={...};
  *   uint8_t digest[CRL_SHA1_SIZE]; // 20 byte buffer
  *   // outSize is for digest output size, retval is for return value
  *   int32_t outSize, retval;
  *   SHA1ctx_stt context_st; // The SHA1 context
  *
  *   // Initialize Context Flag with default value
  *   context_st.mFlags = E_HASH_DEFAULT;
  *   // Set the required digest size to be of 20 bytes (the maximum allowed by SHA1)
  *   context_st.mTagSize = CRL_SHA1_SIZE;
  *
  *   // call init function
  *   retval = SHA1_Init(&context_st);
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  *
  *   // Loop to perform 1024 calls to SHA1_Append, each processing a single byte
  *   for (i = 0; i < 1024; i++)
  *   { //Process 1 bytes of the message.
  *     retval = SHA1_Append(&context_st, message+i, 1);
  *     if (retval != HASH_SUCCESS)
  *     {  ... }
  *   }
  *   //Generate the message digest
  *   retval = SHA1_Finish(&context_st, digest, &outSize );
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  * }
  * \endcode
*/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_SHA1_H__
#define __CRL_SHA1_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @ingroup SHA1
  * @{
  */ 
  
#define CRL_SHA1_SIZE 20   /*!<  Number of bytes (uint8_t) to store a SHA-1 digest. */

/** 
  * @brief  Structure for the SHA-1 context 
  */ 
typedef HASHctx_stt SHA1ctx_stt;

/* Initialization of Context */
int32_t SHA1_Init(SHA1ctx_stt *P_pSHA1ctx);
/* Data processing function */
int32_t SHA1_Append(SHA1ctx_stt *P_pSHA1ctx, const uint8_t *P_pInputBuffer, int32_t P_inputSize);
/* Returns digest */
int32_t SHA1_Finish(SHA1ctx_stt *P_pSHA1ctx, uint8_t *P_pOutputBuffer, int32_t *P_pOutputSize);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif   /*__CRL_SHA1_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
