/*
 * LCD_program.c
 *
 *  Created on: 23 Sep 2019
 *      Author: Mario
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <01- MCAL/02- GPIO/GPIO_int.h>
#include <02- HAL/01- LCD/LCD_int.h>
#include <02- HAL/01- LCD/LCD_conf.h>

void LCD_vidInit(void) {
	_delay_ms(30);								// Delay 30 ms to ensure the initialization of the LCD driver
	LCD_vidSendCommand(LCD_FUNCSET_8BIT);		// Function set command
	_delay_ms(1);
	LCD_vidSendCommand(LCD_DISPON_CURSON); 		// Display ON OFF control
	_delay_ms(1);
	LCD_vidSendCommand(LCD_HOME);				// Return Home
	_delay_ms(15);
	LCD_vidSendCommand(LCD_CLR);				// Clear LCD Screen
	_delay_ms(15);
	LCD_vidSendCommand(LCD_ENTRYMODE);			// Entry Mode Set
	_delay_ms(2);

}

void LCD_vidSendCommand(u8 u8CmdCpy) {
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8LOW);	// Reset RS pin
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8LOW);	// Reset R/W pin
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8HIGH);	// Set E to HIGH
	DIO_SetPortValue(LCD_DATA_PORT, u8CmdCpy);					// Load command on data bus
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8LOW);
	_delay_ms(5);
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8HIGH);
	_delay_ms(10);												// Delay for 10ms to let the LCD execute command

}

void LCD_vidWriteData(u8 u8DataCpy) {
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8HIGH);	// Reset RS pin
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8LOW);	// Reset R/W pin
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8HIGH);	// Set E to HIGH
	DIO_SetPortValue(LCD_DATA_PORT, u8DataCpy);					// Load command on data bus
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8LOW);
	_delay_ms(5);
	DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8HIGH);
	_delay_ms(10);												// 	Delay for 10ms to let the LCD execute command
}

void LCD_vidWriteString(u8* pu8StringCpy) {
	u8 i = 0;
	while (pu8StringCpy[i] != '\0') {
		LCD_vidWriteData(pu8StringCpy[i++]);
	}
}


void LCD_vidStoreCustomChar(u8* pu8CharCpy, u8 u8CharLocCpy) {
	u8 index;
	LCD_vidSendCommand(LCD_WRITECGRAMADD + (u8CharLocCpy * 8) );

	for (index = 0; index < 8; index++) {
		LCD_vidWriteData(pu8CharCpy[index]);
	}

	LCD_vidSendCommand(LCD_u8LINE1_LOC0);
}

void LCD_vidWriteCustomChar(u8 u8CharLocCpy) {
	LCD_vidWriteData(u8CharLocCpy);
}

void LCD_vidGotoXY(u8 u8ColCpy, u8 u8RowCpy) {
	switch (u8RowCpy){
		case 1:
			switch (u8ColCpy) {
				case 1:
					LCD_vidSendCommand(LCD_u8LINE1_LOC0);
					break;
				case 2:
					LCD_vidSendCommand(LCD_u8LINE1_LOC1);
					break;
				case 3:
					LCD_vidSendCommand(LCD_u8LINE1_LOC2);
					break;
				case 4:
					LCD_vidSendCommand(LCD_u8LINE1_LOC3);
					break;
				case 5:
					LCD_vidSendCommand(LCD_u8LINE1_LOC4);
					break;
				case 6:
					LCD_vidSendCommand(LCD_u8LINE1_LOC5);
					break;
				case 7:
					LCD_vidSendCommand(LCD_u8LINE1_LOC6);
					break;
				case 8:
					LCD_vidSendCommand(LCD_u8LINE1_LOC7);
					break;
				case 9:
					LCD_vidSendCommand(LCD_u8LINE1_LOC8);
					break;
				case 10:
					LCD_vidSendCommand(LCD_u8LINE1_LOC9);
					break;
				case 11:
					LCD_vidSendCommand(LCD_u8LINE1_LOC10);
					break;
				case 12:
					LCD_vidSendCommand(LCD_u8LINE1_LOC11);
					break;
				case 13:
					LCD_vidSendCommand(LCD_u8LINE1_LOC12);
					break;
				case 14:
					LCD_vidSendCommand(LCD_u8LINE1_LOC13);
					break;
				case 15:
					LCD_vidSendCommand(LCD_u8LINE1_LOC14);
					break;
				case 16:
					LCD_vidSendCommand(LCD_u8LINE1_LOC15);
					break;
			}
			break;
		case 2:
			switch (u8ColCpy) {
				case 1:
					LCD_vidSendCommand(LCD_u8LINE2_LOC0);
					break;
				case 2:
					LCD_vidSendCommand(LCD_u8LINE2_LOC1);
					break;
				case 3:
					LCD_vidSendCommand(LCD_u8LINE2_LOC2);
					break;
				case 4:
					LCD_vidSendCommand(LCD_u8LINE2_LOC3);
					break;
				case 5:
					LCD_vidSendCommand(LCD_u8LINE2_LOC4);
					break;
				case 6:
					LCD_vidSendCommand(LCD_u8LINE2_LOC5);
					break;
				case 7:
					LCD_vidSendCommand(LCD_u8LINE2_LOC6);
					break;
				case 8:
					LCD_vidSendCommand(LCD_u8LINE2_LOC7);
					break;
				case 9:
					LCD_vidSendCommand(LCD_u8LINE2_LOC8);
					break;
				case 10:
					LCD_vidSendCommand(LCD_u8LINE2_LOC9);
					break;
				case 11:
					LCD_vidSendCommand(LCD_u8LINE2_LOC10);
					break;
				case 12:
					LCD_vidSendCommand(LCD_u8LINE2_LOC11);
					break;
				case 13:
					LCD_vidSendCommand(LCD_u8LINE2_LOC12);
					break;
				case 14:
					LCD_vidSendCommand(LCD_u8LINE2_LOC13);
					break;
				case 15:
					LCD_vidSendCommand(LCD_u8LINE2_LOC14);
					break;
				case 16:
					LCD_vidSendCommand(LCD_u8LINE2_LOC15);
					break;
			}
			break;
	}
}


void LCD_vidWriteInt(s32 val)
{
	u8 str[5]={0};
	u8 i=4;
	u8 j=0;
	u8 sign_flag= 0;
	if (val < 0) {
		sign_flag = 1;
		val *= -1;
	}

	do
	{
		str[i] = (val % 10) + '0';
		val = val/10;
		i--;
	} while (val);

	while (str[j] == 0) {
		j++;
	}

	if (sign_flag == 1) {
		str[j-1] = '-';
	}

	for (i=j; i<5; i++) {
		LCD_vidWriteData(str[i]);
	}

	for (i=0; i<j; i++) {
		LCD_vidWriteData(' ');
	}

}
