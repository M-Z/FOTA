/**
  ******************************************************************************
  * @file    hmac_sha224.h
  * @author  MCD Application Team
  * @version V2.0.6
  * @date    25-June-2013
  * @brief   Provides HMAC-SHA224 functions
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

/*! \page Tutorial_HMACSHA224 HMAC-SHA224 Tutorial
  *
  * Here follows an example of HMAC-SHA224 functionality.
  * Please remember that before starting to call the Init function the context \b requires user 
  * initialization. \n 
  *  The mFlags, mTagSize, pmKey and mKeySize members must be initialized prior to calling the 
  *  init function. Look at the each function documentation to see what is needed prior of calling.
  *
  * The API functions to be used are:
  *  - \ref HMAC_SHA224_Init initialize an \ref HMAC_SHA224ctx_stt context with required tag size, pointer to the key, key size and flags.
  *  - \ref HMAC_SHA224_Append process input buffers.
  *    It can be called multiple times.
  *  - \ref HMAC_SHA224_Finish can be called only one time for the tag generation process.
  *
  * The following code performs a HMAC-SHA224 authentication of an empty buffer.
  * \code
  * #include <stdio.h>
  * #include "crypto.h"
  * int32_t main()
  * {
  *   uint8_t message[1024]={...};
  *   uint8_t key[12]={...};
  *   uint8_t tag[CRL_SHA224_SIZE]; // 28 byte buffer
  *   // outSize is for digest output size, retval is for return value
  *   int32_t outSize, retval;
  *   HMAC_SHA224ctx_stt context_st; // The HMAC-SHA224 context
  *
  *   // Initialize Context Flag with default value
  *   context_st.mFlags = E_HASH_DEFAULT;
  *   // Set the required digest size to be of 28 bytes (the maximum allowed by SHA224)
  *   context_st.mTagSize = CRL_SHA224_SIZE;
  *   // Set the pointer to the Key to be used for the authentication 
  *   context_st.pmKey = key;
  *   // Set the key size
  *   context_st.mKeySize = sizeof(key);
  *
  *   // call init function
  *   retval = HMAC_SHA224_Init(&context_st);
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  *
  *   //Process the message
  *   retval = HMAC_SHA224_Append(&context_st, message, 0);
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  *   
  *   //Generate the message digest
  *   retval = HMAC_SHA224_Finish(&context_st, tag, &outSize );
  *   if (retval != HASH_SUCCESS)
  *   {  ... }
  * }
  * \endcode
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_HMAC_SHA224_H__
#define __CRL_HMAC_SHA224_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @ingroup HMAC_SHA224
  * @{
  */ 

/** 
  * @brief  HMAC-SHA-224 Context Structure 
  */
typedef HMACctx_stt HMAC_SHA224ctx_stt;

  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

int32_t HMAC_SHA224_Init(HMAC_SHA224ctx_stt *P_pHMAC_SHA224ctx);
int32_t HMAC_SHA224_Append(HMAC_SHA224ctx_stt *P_pHMAC_SHA224ctx, const uint8_t *P_pInputBuffer, int32_t P_inputSize);
int32_t HMAC_SHA224_Finish(HMAC_SHA224ctx_stt *P_pHMAC_SHA224ctx, uint8_t *P_pOutputBuffer, int32_t *P_pOutputSize);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif   /* __CRL_HMAC_SHA224_H__ */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
