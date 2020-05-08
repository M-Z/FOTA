/*
 * LCD_conf.h
 *
 *  Created on: 23 Sep 2019
 *      Author: Mario
 */

#ifndef LCD_CONF_H_
#define LCD_CONF_H_

/************************************************************************/
/********************* PORT/PINs configurations for LCD *****************/
/************************************************************************/

/* Description: LCD DATA port configuration */
/* Range      : DIO_u8PORTA ~ DIO_u8PORTD */
#define LCD_DATA_PORT        DIO_u8PORTC

/* Description: LCD Control port configuration */
/* Range      : DIO_u8PORTA ~ DIO_u8PORTD */
#define LCD_CONTROL_PORT	 DIO_u8PORTD

/*Description: LCD RS pin */
/* Range     : DIO_u8PIN0 ~ DIO_u8PIN7 */
#define LCD_RS_PIN			 DIO_u8PIN0

/*Description: LCD RW pin */
/* Range     : DIO_u8PIN0 ~ DIO_u8PIN7 */
#define LCD_RW_PIN		   	 DIO_u8PIN1

/*Description: LCD E pin */
/* Range     : DIO_u8PIN0 ~ DIO_u8PIN7 */
#define LCD_E_PIN			 DIO_u8PIN2



#endif /* LCD_CONF_H_ */
