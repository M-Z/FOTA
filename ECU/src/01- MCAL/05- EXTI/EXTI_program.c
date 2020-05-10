#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "01- MCAL/05- EXTI/EXTI_int.h"
#include "01- MCAL/05- EXTI/EXTI_conf.h"
#include "01- MCAL/05- EXTI/EXTI_priv.h"

void (*CallbackFunction[7])(void);			// Not stored in memory at startup

void EXTI_Stub (void) {
	__asm__("NOP");
}

Error_Status EXTI_SetCallback(void (*x)(void), u8 Idx) {
	switch (Idx) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			CallbackFunction[Idx] = x;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			CallbackFunction[5] = x;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			CallbackFunction[6] = x;
			break;
		default:
			return indexOutOfRange;
	}

	return OK;
}

void EXTI_voidInit(void) {
	EXTI->IMR  = 	EXTI_INT_MASK;
	EXTI->EMR  = 	EXTI_EVENT_MASK;
	EXTI->RTSR = 	EXTI_RISING_EDGES;
	EXTI->FTSR = 	EXTI_FALLING_EDGES;

	for (int i = 0; i < 7; i++) {
		CallbackFunction[i] = EXTI_Stub;
	}
}

Error_Status EXTI_enumSetPending(u8 Idx) {
	if (Idx > 18) {
		return numberOutOfRange;
	} else {
		EXTI->SWIER |= 1 << Idx;
		return OK;
	}
}

Error_Status EXTI_enumClearPending(u8 Idx) {
	if (Idx > 18) {
		return numberOutOfRange;
	} else {
		EXTI->PR |= 1 << Idx;
		return OK;
	}
}

void EXTI0_IRQHandler(void) {
	(*CallbackFunction[0])();
}

void EXTI1_IRQHandler(void) {
	(*CallbackFunction[1])();
}

void EXTI2_IRQHandler(void) {
	(*CallbackFunction[2])();
}

void EXTI3_IRQHandler(void) {
	(*CallbackFunction[3])();
}

void EXTI4_IRQHandler(void) {
	(*CallbackFunction[4])();
}

void EXTI9_5_IRQHandler(void) {
	(*CallbackFunction[5])();
}

void EXTI15_10_IRQHandler(void) {
	(*CallbackFunction[6])();
}
