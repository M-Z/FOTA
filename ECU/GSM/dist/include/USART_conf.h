/*
 * USART_conf.h
 *
 *  Created on: 1 Sep 2019
 *      Author: Mario
 */
#ifndef _USART_CONFIG_H
#define _USART_CONFIG_H

#define BAUDRATE 9600

#define USART1_ENABLE_TRANSMITTER ENABLE
#define USART1_ENABLE_RECEIVER ENABLE
#define USART1_RECEIVE_CALLBACK ENABLE
#define USART1_ENABLE_DMA_RECEIVER ENABLE
#define USART1_ENABLE_DMA_TRANSMITTER ENABLE

#define USART2_ENABLE_TRANSMITTER DISABLE
#define USART2_ENABLE_RECEIVER DISABLE
#define USART2_RECEIVE_CALLBACK DISABLE
#define USART2_ENABLE_DMA_RECEIVER DISABLE

/*
 * STOP_BITS_1, STOP_BITS_1_2, STOP_BITS_2, STOP_BITS_3_2
 */
#ifndef USART1_STOP_BITS
#define USART1_STOP_BITS STOP_BITS_1
#endif
// TODO: Removing comments makes an error with the program file
/*
 * DATA_BITS_8, DATA_BITS_9
 */
#ifndef USART1_WORD_LENGTH
#define USART1_WORD_LENGTH DATA_BITS_8
#endif

/*
 * 	Channel : USARTx_REMAP 	: 	TX 	 : 	RX
 * 	USART1 	:   	0		:	PA9	 :	PA10
 * 			:		1		:	PB6	 :
 * PB7
 *
 * 	USART2	:		0		:	PA2	 : 	PA3
 * 			:		1		:	PD5	 :
 * PD6
 *
 * 	USART3	:		00		:	PB10 :	PB11
 * 			:		01		:	PC10 :	PC11
 * 			:		11		:	PD8	 :
 * PD9
 */

#endif /* _USART_CONFIG_H */
