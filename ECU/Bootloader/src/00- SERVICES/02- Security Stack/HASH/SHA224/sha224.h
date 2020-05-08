/**
  ******************************************************************************
  * @file    sha224.h
  * @author  MCD Application Team
  * @version V2.0.6
  * @date    25-June-2013
  * @brief   Provides SHA224 functions
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

/*! \page Tutorial_SHA224 SHA224 Tutorial
  *
  * Here follows an example of SHA224 functionality.
  * Please remember that before starting to call the Init function the context \b requires user 
  * initialization. The mFlags and mTagSize member must be initialized prior to calling the 
  *  init function. Look at the each function documentation to see what is needed prior of calling.
  *
  * The API functions to be used are:
  *  - \ref SHA224_Init initialize an \ref SHA224ctx_stt context with required digest size and flags.
  *  - \ref SHA224_Append process input buffers.
  *    It can be called multiple times.
  *  - \ref SHA224_Finish can be called only one time for the digest generation process.
  *
  * The following code performs a SHA224 hash of a buffer of size 1024 in a single Append call
  * \code
  * #include <stdio.h>
  * #include "crypto.h"
  * int32_t main()
  * {
  *   uint8_t message[1024]={...};
  *   uint8_t digest[CRL_SHA224_SIZE]; // 28 byte buffer
  *   // outSize is for digest output size, retval is for return value
  *   int32_t outSize, retval;
  *   SHA224ctx_stt context_st; // The SHA224 context
  *
  *   // Initialize Context Flag with default value
  *   context_st.mFlags = E_HASH_DEFAULT;
  *   // Set the required digest size to be only of 4 bytes (while the maximum allowed by SHA224 is 28)
  *   context_st.mTagSize = 4;
  *
  *   // call init function
  *   retval = SHA224_Init(&context_st);
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  *
  *   retval = SHA224_Append(&context_st, message, 1024);
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  *
  *   //Generate the message digest
  *   //Note that only the requested number of bytes of the digest will be written, in this case 4.
  *   retval = SHA224_Finish(&context_st, digest, &outSize );
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  * }
  * \endcode
*/
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_SHA224_H__
#define __CRL_SHA224_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @ingroup SHA224
  * @{
  */ 
#define CRL_SHA224_SIZE 28 /*!<  Number of bytes (uint8_t) to store a SHA-224 digest. */

/**  Structure for the SHA-224 context */ 
typedef HASHctx_stt SHA224ctx_stt;
/* Initialization of Context */
int32_t SHA224_Init(SHA224ctx_stt *P_pSHA224ctx);
/* Data processing function */
int32_t SHA224_Append(SHA224ctx_stt *P_pSHA224ctx, const uint8_t *P_pInputBuffer, int32_t P_inputSize);
/* Returns digest */
int32_t SHA224_Finish(SHA224ctx_stt *P_pSHA224ctx, uint8_t *P_pOutputBuffer, int32_t *P_pOutputSize);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif   /*__CRL_SHA224_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
