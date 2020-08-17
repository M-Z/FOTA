#include "crypto.h"

void __aeabi_memcpy (void *dest, const void *src, size_t n)
{
    memcpy (dest, src, n);
}


typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

#define HMAC_LENGTH 32
#define HMAC_KEY_MAX_SIZE	1000

/* user Inputs*/
const uint8_t InputData[] = ":ABCS";

uint8_t HMAC_Key_Str[] = "aabbcc";
uint8_t HMAC_Key[HMAC_KEY_MAX_SIZE];
uint32_t KeyLengthtemp;

uint8_t MAC[CRL_SHA256_SIZE];
int32_t MACLength = 0;

const uint8_t Expected_HMAC[HMAC_LENGTH] = "5a68cde2e52250392dae40fc73276197411bf61b4e527118d60a157a0c24b9a0";

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_SHA256_HMAC_Compute(uint8_t* InputMessage,
                                  uint32_t InputMessageLength,
                                  uint8_t *HMAC_key,
                                  uint32_t HMAC_keyLength,
                                  uint8_t *MessageDigest,
                                  int32_t* MessageDigestLength);

TestStatus Buffercmp(u8 pBuffer[], u8* pBuffer1 );

/************************************************************************************************/
/* Description: It converts string to its corresponding hex value                               */
/* 				use case: Server sends all data in string format so, it convert the HMAC        */
/* 				Key in string format to its Hex decimal format		        		         	*/
/* Input      : u8 pBuffer[] is the input string which will be converted                        */
/* 				u8* hex_ptr2 pointer to an Array of the output converted hex decimal values	    */
/*				int size is the size of the input string in bytes                               */
/* 				int * keySize pointer to the variable to put the coverted hex values size in it */
/*  Output    : TestStatus, PASSED if the processing is completed, FAILED if not 		        */
/* Scope      : Public                                                                	    */
/************************************************************************************************/
TestStatus convertToHex(u8 pBuffer[], u8* hex_ptr2, int size, int * keySize);




/*********************************************************************************************************/
/* Description: It Generate HMAC and make the comparison between the generated HMAC and the expected one */
/* Input      : const u8 * InputMessage is the input data to check its HMAC (String Format)				 */
/* 				u32 InputLength is input data length in bytes											 */
/* 				const u8 * HMAC_key is HMAC Secret Key (HEX format)										 */
/* 				u32 KeyLength is secret key length	                                                     */
/* 				u8 * expectedHMAC is pointer to the expected HMAC	(String format)                      */
/* Output     : TestStatus, PASSED if the Expected HMAC and the Generated HMAC are identical             */
/* 				Failed if the Expected HMAC and the Generated HMAC are not identical                     */
/* 					   OR  HMAC computing failed                                                         */
/* Scope      : Public                                                                 					 *//*********************************************************************************************************/

/*********************************************************************************************************/
TestStatus HMAC_SHA256_Handler(const u8 * InputMessage,u32 InputLength, const u8 * HMAC_key, u32 KeyLength, const u8 * expectedHMAC);



int main(void)
{
    TestStatus HMAC_check_Status;
    convertToHex(HMAC_Key_Str,HMAC_Key, sizeof(HMAC_Key_Str), &KeyLengthtemp);
    HMAC_check_Status = HMAC_SHA256_Handler(InputData, 5,HMAC_Key, KeyLengthtemp,Expected_HMAC);

    if(HMAC_check_Status == PASSED)
    {
        asm("NOP");
    }
    else if (HMAC_check_Status == FAILED)
    {
        asm("NOP");
    }


    while (1)
    {}
}

/**
  * @brief  SHA1 HMAC compute example.
  * @param  InputMessage: pointer to input message to be hashed.
  * @param  InputMessageLength: input data message length in byte.
  * @param  HMAC_key: pointer to key used in the HMAC computation
  * @param  HMAC_keyLength: HMAC key length in byte.
  * @param  MessageDigest: pointer to output parameter that will handle message digest
  * @param  MessageDigestLength: pointer to output digest length.
  * @retval error status: can be HASH_SUCCESS if success or one of
  *         HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT,
  *         HASH_ERR_BAD_OPERATION if error occured.
  */
int32_t STM32_SHA256_HMAC_Compute(uint8_t* InputMessage,
                                  uint32_t InputMessageLength,
                                  uint8_t *HMAC_key,
                                  uint32_t HMAC_keyLength,
                                  uint8_t *MessageDigest,
                                  int32_t* MessageDigestLength)
{
    HMAC_SHA256ctx_stt HMAC_SHA256ctx;
    uint32_t error_status = HASH_SUCCESS;

    /* Set the size of the desired MAC*/
    HMAC_SHA256ctx.mTagSize = CRL_SHA256_SIZE;

    /* Set flag field to default value */
    HMAC_SHA256ctx.mFlags = E_HASH_DEFAULT;

    /* Set the key pointer in the context*/
    HMAC_SHA256ctx.pmKey = HMAC_key;

    /* Set the size of the key */
    HMAC_SHA256ctx.mKeySize = HMAC_keyLength;

    /* Initialize the context */
    error_status = HMAC_SHA256_Init(&HMAC_SHA256ctx);

    /* check for initialization errors */
    if (error_status == HASH_SUCCESS)
    {
        /* Add data to be hashed */
        error_status = HMAC_SHA256_Append(&HMAC_SHA256ctx,
                                          InputMessage,
                                          InputMessageLength);

        if (error_status == HASH_SUCCESS)
        {
            /* retrieve */
            error_status = HMAC_SHA256_Finish(&HMAC_SHA256ctx, MessageDigest, MessageDigestLength);
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



TestStatus HMAC_SHA256_Handler(const u8 * InputMessage,u32 InputLength, const u8 * HMAC_key, u32 KeyLength, const u8 * expectedHMAC)
{
    int32_t status = HASH_SUCCESS;

    Crypto_DeInit();
    status = STM32_SHA256_HMAC_Compute((uint8_t*)InputMessage,
                                       InputLength,
                                       HMAC_Key,
                                       KeyLength,
                                       (uint8_t*)MAC,
                                       &MACLength);
    if (status == HASH_SUCCESS)
    {
        asm("NOP");
        /* Copmare the extracted Mac with the generated MAC */
        if (Buffercmp(expectedHMAC, MAC) == PASSED)
        {
            /* Extracted and generated MAC are Identical */
            asm("NOP");
            return PASSED;
        }
        else
        {
            /* Extracted and generated MAC are different */
            asm("NOP");
            return FAILED;
        }
    }
    else
    {
        /* HMAC processing failed */
        return FAILED;
    }


}


TestStatus convertToHex(u8 pBuffer[], u8* hex_ptr2, int size, int * keySize)
{
    u8 hex_ptr;
    u32 j;
    j = 0;
    for (int i = 1; i < size; i += 2) {
        hex_ptr = (pBuffer[i - 1] <= '9') ? ( pBuffer[i - 1] - '0' ) * 16 : (pBuffer[i - 1] - 'a' + 10) * 16;
        hex_ptr += (pBuffer[i] <= '9') ? ( pBuffer[i] - '0' ) : (pBuffer[i] - 'a' + 10) ;
        hex_ptr2[j] = hex_ptr;
        j++;
    }
    *keySize = j;
    return PASSED;
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {}
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

