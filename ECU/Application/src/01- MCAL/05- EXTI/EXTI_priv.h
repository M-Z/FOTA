#ifndef _EXTI_PRIV_H
#define _EXTI_PRIV_H

#define EXTI_BASE_ADDRESS           0x40010400 // Base Address

typedef struct {
	u32	IMR;			// Interrupt mask register: masks the interrupt number so it won't be listened to
	u32	EMR;			// Event mask register
	u32 RTSR;			// Rising trigger selection register
	u32 FTSR;			// Falling trigger selection register
	u32 SWIER;			// Software interrupt event register: generates a software interrupt simualtion
	u32 PR;				// Pending register: This bit is set when the selected edge event arrives on the external interrupt line. This bit is cleared by writing a ‘1’ into the bit.
} EXTI_REG;

#define EXTI ((EXTI_REG *) EXTI_BASE_ADDRESS)
//static volatile  EXTI_REG * EXTI = ( volatile EXTI_REG * ) EXTI_BASE_ADDRESS ;

#define CONC_BIT(bit18,bit17,bit16,bit15,bit14,bit13,bit12,bit11,bit10,bit9,bit8,bit7,bit6,bit5,bit4,bit3,bit2,bit1,bit0) CONC_HELP(bit18,bit17,bit16,bit15,bit14,bit13,bit12,bit11,bit10,bit9,bit8,bit7,bit6,bit5,bit4,bit3,bit2,bit1,bit0)
#define CONC_HELP(bit18,bit17,bit16,bit15,bit14,bit13,bit12,bit11,bit10,bit9,bit8,bit7,bit6,bit5,bit4,bit3,bit2,bit1,bit0) 0b0000000000000##bit18##bit17##bit16##bit15##bit14##bit13##bit12##bit11##bit10##bit9##bit8##bit7##bit6##bit5##bit4##bit3##bit2##bit1##bit0

#define  EXTI_INT_MASK CONC_BIT(EXTI_INT_18,EXTI_INT_17,EXTI_INT_16,EXTI_INT_15,EXTI_INT_14,EXTI_INT_13,EXTI_INT_12,EXTI_INT_11,EXTI_INT_10,EXTI_INT_9,EXTI_INT_8,EXTI_INT_7,EXTI_INT_6,EXTI_INT_5,EXTI_INT_4,EXTI_INT_3,EXTI_INT_2,EXTI_INT_1,EXTI_INT_0)
#define  EXTI_EVENT_MASK CONC_BIT(EXTI_EVENT_18,EXTI_EVENT_17,EXTI_EVENT_16,EXTI_EVENT_15,EXTI_EVENT_14,EXTI_EVENT_13,EXTI_EVENT_12,EXTI_EVENT_11,EXTI_EVENT_10,EXTI_EVENT_9,EXTI_EVENT_8,EXTI_EVENT_7,EXTI_EVENT_6,EXTI_EVENT_5,EXTI_EVENT_4,EXTI_EVENT_3,EXTI_EVENT_2,EXTI_EVENT_1,EXTI_EVENT_0)
#define  EXTI_RISING_EDGES CONC_BIT(EXTI_RISING_18,EXTI_RISING_17,EXTI_RISING_16,EXTI_RISING_15,EXTI_RISING_14,EXTI_RISING_13,EXTI_RISING_12,EXTI_RISING_11,EXTI_RISING_10,EXTI_RISING_9,EXTI_RISING_8,EXTI_RISING_7,EXTI_RISING_6,EXTI_RISING_5,EXTI_RISING_4,EXTI_RISING_3,EXTI_RISING_2,EXTI_RISING_1,EXTI_RISING_0)
#define  EXTI_FALLING_EDGES CONC_BIT(EXTI_FALLING_18,EXTI_FALLING_17,EXTI_FALLING_16,EXTI_FALLING_15,EXTI_FALLING_14,EXTI_FALLING_13,EXTI_FALLING_12,EXTI_FALLING_11,EXTI_FALLING_10,EXTI_FALLING_9,EXTI_FALLING_8,EXTI_FALLING_7,EXTI_FALLING_6,EXTI_FALLING_5,EXTI_FALLING_4,EXTI_FALLING_3,EXTI_FALLING_2,EXTI_FALLING_1,EXTI_FALLING_0)

#endif
