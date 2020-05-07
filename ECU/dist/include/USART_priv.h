/*
 * USART_priv.h
 *
 *  Created on: 1 Sep 2019
 *      Author: Mario
 */
#ifndef _USART_PRIV_H
#define _USART_PRIV_H

// Base Address
#define USART1_BASE_ADDRESS           0x40013800
#define USART2_BASE_ADDRESS           0x40004400
#define USART3_BASE_ADDRESS           0x40004800
#define USART4_BASE_ADDRESS           0x40004C00
#define USART5_BASE_ADDRESS           0x40005000

typedef struct {
	u32	SR;			// Status register
	u32	DR;			// Data register
	u32 BRR;		// Baud rate register
	u32 CR1;		// Control register 1
	u32 CR2;		// Control register 2
	u32 CR3;		// Control register 3
	u32 GTPR;		// Guard time and prescaler register
} UART_REG;

#define USART1 ((UART_REG *) USART1_BASE_ADDRESS)
#define USART2 ((UART_REG *) USART2_BASE_ADDRESS)
#define USART3 ((UART_REG *) USART3_BASE_ADDRESS)
#define USART4 ((UART_REG *) USART4_BASE_ADDRESS)
#define USART5 ((UART_REG *) USART5_BASE_ADDRESS)

//static volatile  UART_REG * USART1 = ( volatile UART_REG * ) USART1_BASE_ADDRESS;
//static volatile  UART_REG * USART2 = ( volatile UART_REG * ) USART2_BASE_ADDRESS;
//static volatile  UART_REG * USART3 = ( volatile UART_REG * ) USART3_BASE_ADDRESS;
//static volatile  UART_REG * USART4 = ( volatile UART_REG * ) USART4_BASE_ADDRESS;
//static volatile  UART_REG * USART5 = ( volatile UART_REG * ) USART5_BASE_ADDRESS;

#define CHANNEL_MIN			1
#define CHANNEL_MAX			3

#define STOP_BITS_1			0b00
#define STOP_BITS_1_2 		0b01
#define STOP_BITS_2 		0b10
#define STOP_BITS_3_2 		0b11

#define DATA_BITS_8			0
#define DATA_BITS_9			1

#endif	/* _USART_PRIV_H */
