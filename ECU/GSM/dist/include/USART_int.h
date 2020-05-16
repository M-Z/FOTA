/*
 * USART_int.h
 *
 *  Created on: 1 Sep 2019
 *      Author: Mario
 */
#ifndef _USART_INT_H
#define _USART_INT_H

/**
  * @brief  Sets the BAUDRATE and enables USART transmitter and/or receiver
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @retval Error_Status
  */
Error_Status USART_enumInit(u8);

/**
  * @brief  Sets the Callback function when the RXNE Handler gets called
  * @param  @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param  void (*x)(u16): The function that takes 16 bits argument and returns void
  * @retval Error_Status
  */
Error_Status USART_enumSetCallback(u8 Channel, void (*x)(u16));

/**
  * @brief  Sends a character
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param	letter: ASCII letter
  * @retval void
  */
void USART_voidSendChar(u8, u16);

/**
  * @brief  Sends a string ended by the null terminator "\0"
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param	Message: The String to be sent
  * @retval void
  */
void USART_voidSendATCommand(u8, const char*);

/**
  * @brief  Sends a string ended CR and NL
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param	Message: The String to be sent
  * @retval void
  */
void USART_voidSendString(u8, const char*);

/**
 * @brief  (POLLING) Waits for character receive and returns it
 * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
 * @retval u8: the 8/9 bits received in the data register
 */
u16 USART_u16Receive(u8);

/**
 * @brief  Waits for character receive and puts it into a buffer by DMA
 * @param  @param  Channel:	Number of the UART Channel to use.
 * 							Can be USART_CHANNEL_x where x is from 1 to 5
 * @param  Channel:	Number of the DMA Channel to use.
 * 					Can be DMA_CHANNEL_x where x is from 1 to 6
 * @param  buffer: Pointer to a 32-bit array to hold the received data
 * @param  Count: The number of data units anticipated
 * @retval u8 the 8/9 bits received in the data register
 */
Error_Status USART_enumDMAReceive(u8, u8, volatile u32*, u32);



Error_Status USART_enumDMASend(u8 UART_Channel, u8 DMA_Channel, volatile u8* buffer, u32 Count);

u8 USART_u8CheckTxComplete(u8 UART_Channel);

#define USART_CHANNEL_1 		1
#define USART_CHANNEL_2 		2
#define USART_CHANNEL_3 		3
#define USART_CHANNEL_4 		4
#define USART_CHANNEL_5 		5

#endif	/* _USART_INT_H */
