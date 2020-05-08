/**
  ******************************************************************************
  * @file    hash.h
  * @author  MCD Application Team
  * @version V2.0.6
  * @date    25-June-2013
  * @brief   Container for the HASH functionalities
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.hom/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************/
/*!
* \page Tutorial_Hash Hash Tutorials
*
*  In this tutorial there will be described the high level functions for the different HASH and HMAC functions.
*  The API is composed by separate functions for doing Initialization, Data Processing, Finalization. \n
*  To correctly use these API
*    the user should call once the Init function, which initialize a context, then the user can call the data
*    processing (Append) function as many times as it needs, to process different input, and at the end he should
*    call, once, the finalization function, to finish the processing and output the hash digest or hmac tag. \n
*    Please refer to the following tutorials according to actual hash functions:
*    - \subpage Tutorial_MD5
*    - \subpage Tutorial_SHA1
*    - \subpage Tutorial_SHA224
*    - \subpage Tutorial_SHA256
*
*   And the analogous HMAC functions:
*    - \subpage Tutorial_HMACMD5
*    - \subpage Tutorial_HMACSHA1
*    - \subpage Tutorial_HMACSHA224
*    - \subpage Tutorial_HMACSHA256
*
*
*/
#include "Common/hash_common.h"

/** @ingroup HASH
  * @{
  */
  
#ifdef INCLUDE_MD5
#include "MD5/md5.h"
#ifdef INCLUDE_HMAC
#include "MD5/hmac_md5.h"
#endif
#endif

#ifdef INCLUDE_SHA1
#include "SHA1/sha1.h"
#ifdef INCLUDE_HMAC
#include "SHA1/hmac_sha1.h"
#endif
#endif

#ifdef INCLUDE_SHA224
#include "SHA224/sha224.h"
#include "Common/sha256_sha224_transform.h"
#ifdef INCLUDE_HMAC
#include "SHA224/hmac_sha224.h"
#endif
#endif

#ifdef INCLUDE_SHA256
#include "SHA256/sha256.h"
#include "Common/sha256_sha224_transform.h"
#ifdef INCLUDE_HMAC
#include "SHA256/hmac_sha256.h"
#endif
#endif

 /**
  * @} HASH
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
