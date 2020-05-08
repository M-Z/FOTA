#include "config.h"

#if defined(INCLUDE_SHA1) || defined(INCLUDE_SHA224) || defined(INCLUDE_SHA256) || defined(INCLUDE_MD5)
	#define INCLUDE_HASH /*!< Hash functions are included  */
#endif

/*************************************************************************************************
***-*-*-*-*--**- SOME CHECKS, DON'T MODIFY -**--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**
*************************************************************************************************/
#if (defined(INCLUDE_ENCRYPTION) || defined(INCLUDE_DECRYPTION)) && !(defined(INCLUDE_AES) || defined(INCLUDE_DES_CORE) || defined(INCLUDE_ARC4))
#error "Either encryption or decryption has been specified but no AES or DES are present"
#elif (!defined(INCLUDE_ENCRYPTION) && !defined(INCLUDE_DECRYPTION)) && (defined(INCLUDE_AES) || defined(INCLUDE_DES_CORE))
#error "AES or DES are present but without encryption or decryption functionalities!"
#endif

#ifdef CRL_CPU_SUPPORT_MISALIGNED
  #ifndef CRL_ENDIANNESS
    #error "With CRL_CPU_SUPPORT_MISALIGNED=1 a definition for CRL_ENDIANNESS is required!"
  #endif
#endif

#if defined(INCLUDE_GCM) && !defined(INCLUDE_AES)
#error "GCM is currently supported only by AES, but AES has not be included, please include AES or remove GCM"
#endif

#if defined(INCLUDE_CMAC) && !defined(INCLUDE_AES)
#error "CMAC is currently supported only by AES, but AES has not be included, please include AES or remove GCM"
#endif

#if defined(INCLUDE_KEY_WRAP) && !defined(INCLUDE_AES)
#error "KWRAP is currently supported only by AES, but AES has not be included, please include AES or remove KWRAP"
#endif

#if defined(INCLUDE_CTR) && !defined(INCLUDE_AES)
#error "CTR is currently supported only by AES, but AES has not be included, please include AES or remove CTR"
#endif

#if defined(INCLUDE_CCM) && !defined(INCLUDE_AES)
#error "CCM is currently supported only by AES, but AES has not be included, please include AES or remove CCM"
#endif

#if defined(INCLUDE_DRBG_AES128) && !defined(INCLUDE_AES128)
#error "DRBG_AES128 requires INCLUDE_AES_128"
#endif

#if defined(INCLUDE_ECC_SIGN) & !(defined(STM32F21X) || defined(INCLUDE_DRBG_AES128))
#error "To include ECC_SIGN functionalities you need a random generator. If you use an STM32F21X define STM32F21X, otherwise define INCLUDE_DRBG_AES128\n"
#endif

/*************************************************************************************************
***-*-*-*-*--**- CRYPTO LIBRARY INCLUSIONS -**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-***
*************************************************************************************************/
//#include <stdlib.h>
//#include <stdio.h>
//#include "Common/types.h"
//#include "Common/macros.h"
//#include "Common/err_codes.h"
//#include "Common/sk.h"

#ifdef INCLUDE_HASH
	#include "HASH/hash.h"
#endif

void Crypto_DeInit(void);

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
