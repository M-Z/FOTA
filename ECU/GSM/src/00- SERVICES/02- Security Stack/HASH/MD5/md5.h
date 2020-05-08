/**
  ******************************************************************************
  * @file    md5.h
  * @author  MCD Application Team
  * @version V2.0.6
  * @date    25-June-2013
  * @brief   Provides MD5 functions
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

/*! \page Tutorial_MD5 MD5 Tutorial
  *
  * Here follows an example of MD5 functionality.
  * Please remember that before starting to call the Init function the context \b requires user 
  * initialization. The mFlags and mTagSize member must be initialized prior to calling the 
  *  init function. Look at the each function documentation to see what is needed prior of calling.
  *
  * The API functions to be used are:
  *  - \ref MD5_Init initialize an \ref MD5ctx_stt context with required digest size and flags.
  *  - \ref MD5_Append process input buffers.
  *    It can be called multiple times.
  *  - \ref MD5_Finish can be called only one time for the digest generation process.
  *
  * The following code performs a MD5 hash of a buffer of size 1024 in 4 Append calls.
  * \code
  * #include <stdio.h>
  * #include "crypto.h"
  * int32_t main()
  * {
  *   uint8_t message[1024]={...};
  *   uint8_t digest[CRL_MD5_SIZE]; // 16 byte buffer
  *   // outSize is for digest output size, retval is for return value
  *   int32_t outSize, retval;
  *   MD5ctx_stt context_st; // The MD5 context
  *
  *   // Initialize Context Flag with default value
  *   context_st.mFlags = E_HASH_DEFAULT;
  *   // Set the required digest size to be of 16 bytes (the maximum allowed by MD5)
  *   context_st.mTagSize = CRL_MD5_SIZE;
  *
  *   // call init function
  *   retval = MD5_Init(&context_st);
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  *
  *   // Loop to perform four calls to MD5_Append, each processing 256 bytes
  *   for (i = 0; i < 1024; i += 256)
  *   { //Process i bytes of the message.
  *     retval = MD5_Append(&context_st, message+i, 256);
  *     if (retval != HASH_SUCCESS)
  *     {  ... }
  *   }
  *   //Generate the message digest
  *   retval = MD5_Finish(&context_st, digest, &outSize );
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  * }
  * \endcode
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_MD5_H__
#define __CRL_MD5_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @ingroup MD5
  * @{
  */ 
  
#define CRL_MD5_SIZE  16   /*!< Number of bytes (uint8_t) to store a MD5 digest. */

/** 
  * @brief  Structure for the MD5 context 
  */ 
typedef HASHctx_stt MD5ctx_stt;

/* Initialization of Context */
int32_t MD5_Init(MD5ctx_stt *P_pMD5ctx);
/* Data processing function */
int32_t MD5_Append(MD5ctx_stt *P_pMD5ctx, const uint8_t *P_pInputBuffer, int32_t P_inputSize);
/* Returns digest */
int32_t MD5_Finish(MD5ctx_stt *P_pMD5ctx, uint8_t *P_pOutputBuffer, int32_t *P_pOutputSize);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif   /*__CRL_MD5_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
