#include <STD_TYPES.h>
#include <BIT_MATH.h>

#include "USART_priv.h"
#include "USART_int.h"
#include "USART_conf.h"

//#include "01- MCAL/01- RCC/RCC_int.h"
#include "DMA_int.h"

// Not stored in memory at startup
void (*CallbackFunction1)(u16);
void (*CallbackFunction2)(u16);
void (*CallbackFunction3)(u16);

static void USART_Stub (u16 x) {
	__asm__("NOP");
}

/**
  * @brief  Sets the BAUDRATE and enables USART transmitter and/or receiver
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @retval Error_Status
  */
Error_Status USART_enumInit(u8 Channel) {
	Error_Status returnVal = OK;

	if (Channel >= CHANNEL_MIN && Channel <= CHANNEL_MAX) {
//		RCC_enumEnableClock( USART1_CLOCK );

		volatile UART_REG * selectedChannel = USART1;

		switch(Channel) {
			case 1:
				CallbackFunction1 = &USART_Stub;

				#ifdef USART1_WORD_LENGTH
					USART1->CR1 |= USART1_WORD_LENGTH << 12;
				#endif

				#ifdef USART1_STOP_BITS
					USART1->CR2 |= USART1_STOP_BITS << 12;
				#endif

				#if USART1_ENABLE_TRANSMITTER == ENABLE
					SET_BIT(USART1->CR1, 3);
				#endif

				#if USART1_ENABLE_RECEIVER == ENABLE
					SET_BIT(USART1->CR1, 2);
				#endif

				#if	USART1_RECEIVE_CALLBACK == ENABLE
					SET_BIT(USART1->CR1, 5);					// RXNE interrupt enable
				#endif

				#if USART1_ENABLE_DMA_RECEIVER == ENABLE
					SET_BIT(USART1->CR3, 6);					// DMA ENABLE RECEIVER
				#endif

				#if USART1_ENABLE_DMA_TRANSMITTER == ENABLE
					SET_BIT(USART1->CR3, 7);					// DMA ENABLE TRANSMITTER
				#endif

				break;
			case 2:
				selectedChannel = USART2;
				CallbackFunction2 = &USART_Stub;

				#ifdef USART2_WORD_LENGTH
					USART2->CR1 |= USART2_WORD_LENGTH << 12;
				#endif

				#ifdef USART2_STOP_BITS
					USART2->CR2 |= USART2_STOP_BITS << 12;
				#endif

				#if USART2_ENABLE_TRANSMITTER == ENABLE
					SET_BIT(USART2->CR1, 3);
				#endif

				#if USART2_ENABLE_RECEIVER == ENABLE
					SET_BIT(USART2->CR1, 2);
				#endif

				#if	USART2_RECEIVE_CALLBACK == ENABLE
					SET_BIT(USART2->CR1, 5);									// RXNE interrupt enable
				#endif

				#if USART2_ENABLE_DMA_RECEIVER == ENABLE
					SET_BIT(USART2->CR3, 6);					// DMA ENABLE RECEIVER
				#endif

				#if USART2_ENABLE_DMA_TRANSMITTER == ENABLE
					SET_BIT(USART2->CR3, 7);					// DMA ENABLE TRANSMITTER
				#endif

				break;
			case 3:
				selectedChannel = USART3;

				#ifdef USART3_WORD_LENGTH
					USART3->CR1 |= USART3_WORD_LENGTH << 12;
				#endif

				#ifdef USART3_STOP_BITS
					USART3->CR2 |= USART3_STOP_BITS << 12;
				#endif

				#if USART3_ENABLE_TRANSMITTER == ENABLE
					SET_BIT(USART3->CR1, 3);
				#endif

				#if USART3_ENABLE_RECEIVER == ENABLE
					SET_BIT(USART3->CR1, 2);
				#endif

				#if	USART3_RECEIVE_CALLBACK == ENABLE
					SET_BIT(USART3->CR1, 5);									// RXNE interrupt enable
				#endif

				#if USART3_ENABLE_DMA_RECEIVER == ENABLE
					SET_BIT(USART3->CR3, 6);					// DMA ENABLE RECEIVER
				#endif

				#if USART3_ENABLE_DMA_TRANSMITTER == ENABLE
					SET_BIT(USART3->CR3, 7);					// DMA ENABLE TRANSMITTER
				#endif

				CallbackFunction3 = &USART_Stub;
				break;
			default:
				returnVal = NOK;			// Shouldn't reach this part
		}

		u32 freq = 72000000;												// APB2 Bus Fck

		if (Channel > 1) {
			freq = 36000000;												// APB1 bus Fck
		}

		u16 Mantissa = freq / (16 * BAUDRATE);								// Mantissa (whole part)
		u8 Fraction = freq / (16.0 * BAUDRATE) * 100.0 - Mantissa * 100;	// Fractional part
		selectedChannel->BRR  = (Mantissa << 4) + Fraction;					// Set BAUDRATE

		SET_BIT(selectedChannel->CR1, 13);									// USART enable
	} else {
		returnVal = numberOutOfRange;
	}

	return returnVal;
}

/**
  * @brief  Sets the Callback function when the RXNE Handler gets called
  * @param  @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param  void (*x)(u16): The function that takes 16 bits argument and returns void
  * @retval Error_Status
  */
Error_Status USART_enumSetCallback(u8 Channel, void (*x)(u16)) {
	Error_Status returnVal = OK;

	if (Channel >= CHANNEL_MIN && Channel <= CHANNEL_MAX) {
		switch (Channel) {
			case 1:
				CallbackFunction1 = x;
				break;
			case 2:
				CallbackFunction2 = x;
				break;
			case 3:
				CallbackFunction3 = x;
				break;
			default:
				returnVal = NOK;
		}
	} else {
		returnVal = numberOutOfRange;
	}

	return returnVal;
}

/**
  * @brief  Sends an 8/9-bits to the selected channel pin
  * @param  UART_REG*: Pointer to the UART channel register
  * @param  Char: the 8/9-bits to send
  * @retval void
  */
static void USART_voidSend(volatile UART_REG * selectedChannel, u16 Char) {
	while (!GET_BIT(selectedChannel->SR, 7));	// TXE: The next data can be written in the USART_DR register without overwriting the previous data.
	selectedChannel->DR = Char;
	while (!GET_BIT(selectedChannel->SR, 6));	// TC: Wait for transfer complete
}

/**
  * @brief  Sends a character
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param	letter: ASCII letter
  * @retval void
  */
void USART_voidSendChar(u8 Channel, u16 letter) {
	volatile UART_REG * selectedChannel = USART1;

	switch(Channel) {
		case 1:
			;
			break;
		case 2:
			selectedChannel = USART2;
			break;
		case 3:
			selectedChannel = USART3;
			break;
		case 4:
			selectedChannel = USART4;
			break;
		case 5:
			selectedChannel = USART5;
			break;
		default:
			return;
	}

	USART_voidSend(selectedChannel, letter);
}

/**
  * @brief  Sends a string ended by the null terminator "\0"
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param	Message: The String to be sent
  * @retval void
  */
void USART_voidSendATCommand(u8 Channel, const char* Message) {
	volatile UART_REG * selectedChannel = USART1;

	switch(Channel) {
		case 1:
			;
			break;
		case 2:
			selectedChannel = USART2;
			break;
		case 3:
			selectedChannel = USART3;
			break;
		case 4:
			selectedChannel = USART4;
			break;
		case 5:
			selectedChannel = USART5;
			break;
		default:
			return;
	}

	u8 currentPos = 0;
	while (Message[currentPos] != '\0') {
		USART_voidSend(selectedChannel, Message[currentPos++]);
	}

	// Terminate by /r/n
	USART_voidSend(selectedChannel, '\r');
	USART_voidSend(selectedChannel, '\n');
	while(!GET_BIT(selectedChannel->SR, 6));	// Wait transmission is not completed
}

/**
  * @brief  Sends a string ended CR and NL
  * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
  * @param	Message: The String to be sent
  * @retval void
  */
void USART_voidSendString(u8 Channel, const char* Message) {
	volatile UART_REG * selectedChannel = USART1;

	switch(Channel) {
		case 1:
			;
			break;
		case 2:
			selectedChannel = USART2;
			break;
		case 3:
			selectedChannel = USART3;
			break;
		case 4:
			selectedChannel = USART4;
			break;
		case 5:
			selectedChannel = USART5;
			break;
		default:
			return;
	}

	u8 currentPos = 0;
	while (Message[currentPos] != '\0') {
		USART_voidSend(selectedChannel, Message[currentPos++]);
	}

	while(!GET_BIT(selectedChannel->SR, 6));	// Wait transmission is not completed
}

/**
 * @brief  (POLLING) Waits for character receive and returns it
 * @param  Channel:	Number of the UART Channel to use.
  * 					Can be USART_CHANNEL_x where x is from 1 to 5
 * @retval u8: the 8/9 bits received in the data register
 */
u16 USART_u16Receive(u8 Channel) {
	volatile UART_REG * selectedChannel = USART1;

	switch(Channel) {
		case 1:
			;
			break;
		case 2:
			selectedChannel = USART2;
			break;
		case 3:
			selectedChannel = USART3;
			break;
		case 4:
			selectedChannel = USART4;
			break;
		case 5:
			selectedChannel = USART5;
			break;
		default:
			return 0;
	}

	while (!GET_BIT(selectedChannel->SR, 5));	// Data has been received and can be read
	return selectedChannel->DR;
}

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
Error_Status USART_enumDMAReceive(u8 UART_Channel, u8 DMA_Channel, volatile u32* buffer, u32 Count) {
	UART_REG * selectedChannel = USART1;

	switch(UART_Channel) {
 		case 1:
 			;
			break;
 		case 2:
			selectedChannel = USART2;
 			break;
 		case 3:
			selectedChannel = USART3;
			break;
 		case 4:
 			selectedChannel = USART4;
 			break;
 		case 5:
 			selectedChannel = USART5;
 			break;
 		default:
 			return NOK;
 	}

	DMA_Transfer(DMA_Channel, buffer, &(selectedChannel->DR), Count);
	return OK;
}

void USART1_IRQHandler(void) {
	// Received something
	if (GET_BIT(USART1->SR, 5)) {
		CallbackFunction1(USART1->DR);
	}
}

void USART2_IRQHandler(void) {
	// Received something
	if (GET_BIT(USART2->SR, 5)) {
		CallbackFunction2(USART2->DR);
	}
}

void USART3_IRQHandler(void) {
	// Received something
	if (GET_BIT(USART3->SR, 5)) {
		CallbackFunction3(USART3->DR);
	}
}
