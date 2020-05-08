/*
 * LCD_int.h
 *
 *  Created on: 23 Sep 2019
 *      Author: Mario
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_


/******************** Driver information ****************/
/* this driver is meant for 16x2 character LCD and it supports 8 bit mode*/

/********************************************************/
/*******************Public Definitions*******************/
/********************************************************/
/*Comment!: LCD control commands*/

#define LCD_CLR           		0x01          /* replace all characters with ASCII 'space'                       */
#define LCD_HOME          		0x02          /* return cursor to first position on first line                   */
#define LCD_ENTRYMODE     		0x06          // shift cursor from left to right on read/write
#define LCD_DISPOFF       		0x08          // turn display off
#define LCD_DISPON_CURSON 		0x0E          // display on, cursor off, don't blink character
#define LCD_FUNCRESET     		0x30          // reset the LCD
#define LCD_FUNCSET_8BIT  		0x38          // 8-bit data, 2-line display, 5 x 7 font
#define LCD_SETCURSOR     		0x80          // set cursor position
#define LCD_DISPON_CURSBLINK	0x0F //display on , cursor blinking
#define LCD_DISPON_CURSOFF		0x0C //display on ,cursor off
#define LCD_WRITECGRAMADD       0x40
#define LCD_ENTRYMODELEFT       0x04



/* Comment!: LCD displaying locations commands */
#define LCD_u8LINE1_LOC0		0x80 // line 1 character 0
#define LCD_u8LINE1_LOC1		0x81 // line 1 character 1
#define LCD_u8LINE1_LOC2		0x82 // line 1 character 2
#define LCD_u8LINE1_LOC3		0x83 // line 1 character 3
#define LCD_u8LINE1_LOC4		0x84 // line 1 character 4
#define LCD_u8LINE1_LOC5		0x85 // line 1 character 5
#define LCD_u8LINE1_LOC6		0x86 // line 1 character 6
#define LCD_u8LINE1_LOC7		0x87 // line 1 character 7
#define LCD_u8LINE1_LOC8		0x88 // line 1 character 8
#define LCD_u8LINE1_LOC9		0x89 // line 1 character 9
#define LCD_u8LINE1_LOC10		0x8A // line 1 character 10
#define LCD_u8LINE1_LOC11		0x8B // line 1 character 11
#define LCD_u8LINE1_LOC12		0x8C // line 1 character 12
#define LCD_u8LINE1_LOC13		0x8D // line 1 character 13
#define LCD_u8LINE1_LOC14		0x8E // line 1 character 14
#define LCD_u8LINE1_LOC15		0x8F // line 1 character 15

#define LCD_u8LINE2_LOC0		0xC0 //line 2 character 0
#define LCD_u8LINE2_LOC1		0xC1 //line 2 character 1
#define LCD_u8LINE2_LOC2		0xC2 //line 2 character 2
#define LCD_u8LINE2_LOC3		0xC3 //line 2 character 3
#define LCD_u8LINE2_LOC4		0xC4 //line 2 character 4
#define LCD_u8LINE2_LOC5		0xC5 //line 2 character 5
#define LCD_u8LINE2_LOC6		0xC6 //line 2 character 6
#define LCD_u8LINE2_LOC7		0xC7 //line 2 character 7
#define LCD_u8LINE2_LOC8		0xC8 //line 2 character 8
#define LCD_u8LINE2_LOC9		0xC9 //line 2 character 9
#define LCD_u8LINE2_LOC10		0xCA //line 2 character 10
#define LCD_u8LINE2_LOC11		0xCB //line 2 character 11
#define LCD_u8LINE2_LOC12		0xCC //line 2 character 12
#define LCD_u8LINE2_LOC13		0xCD //line 2 character 13
#define LCD_u8LINE2_LOC14		0xCE //line 2 character 14
#define LCD_u8LINE2_LOC15		0xCF //line 2 character 15

/********************************************************/
/*******************Public Functions *******************/
/********************************************************/
/***************************************************************************************/
/* Description: Apply initialization sequence for LCD module                           */
/* Input      : Void                                                                   */
/* Output     : Void                                                                   */
/* Scope      : Public                                                                 */
/***************************************************************************************/
void LCD_vidInit(void);

void LCD_vidSendCommand(u8 u8CmdCpy);

void LCD_vidWriteData( u8 u8DataCpy);

void LCD_vidWriteString(u8* pu8StringCpy);
//
void LCD_vidStoreCustomChar(u8* pu8CharCpy, u8 u8CharLocCpy);
//
void LCD_vidWriteCustomChar(u8 u8CharLocCpy);

void LCD_vidGotoXY(u8 u8ColCpy, u8 u8RowCpy);

void LCD_vidWriteInt(s32 val);


#endif /* LCD_INT_H_ */
