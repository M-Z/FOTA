/**
  ******************************************************************************
  * @file    stm32_crypto_version.h
  * @author  MCD Application Team
  * @version V2.0.6
  * @date    25-June-2013
  * @brief   Provides the library version and Crypto Type.
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
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_CRYPTO_VERSION_H_
#define __STM32_CRYPTO_VERSION_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include <stdint.h>

/** @addtogroup STM32_Crypto_Driver
  * @{
  */

/** @addtogroup Version
  * @{
  */ 

/** 
  * @brief  Structure that contains STM32 Crypto verion and Crypto Type: HW or FW
  */  
typedef struct
{
  uint8_t X;     /*!< Used to get the X parametre of the current STM32 crypto library verion */
  uint8_t Y;     /*!< Used to get the Y parametre of the current STM32 crypto library verion */
  uint8_t Z;     /*!< Used to get the Z parametre of the current STM32 crypto library verion */
  uint8_t T[2];  /*!< Used to get the Type of the verion. This parametre can be "HW" or "FW" */
  uint8_t CortexConf ;
  uint8_t MicroConf ;
  uint8_t EndiannessConf ;
  uint8_t MisalignedConf ;
  uint8_t EncDecConf;
  uint16_t SymKeyConf  ; 
  uint16_t SymKeyModesConf ;
  uint16_t AsymKeyConf ;
  uint16_t HashConf ;
  uint8_t DrbgConf ;
  uint8_t AesConf ;
  uint8_t RsaConf ;
  uint8_t GcmConf ;  
  
}STM32CryptoLibVer_TypeDef;

void STM32_CryptoLibraryVersion(STM32CryptoLibVer_TypeDef * LibVersion);

#ifdef __cplusplus
}
#endif

#endif /* __STM32_CRYPTO_VERSION_H_ */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
