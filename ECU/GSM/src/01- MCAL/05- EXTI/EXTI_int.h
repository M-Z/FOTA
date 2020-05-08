#ifndef _EXTI_INT_H
#define _EXTI_INT_H

void EXTI_voidInit();
Error_Status EXTI_enumSetPending(u8 Idx);
Error_Status EXTI_enumClearPending(u8 Idx);
Error_Status EXTI_SetCallback(void (*x)(void), u8 Idx);
void EXTI_Stub (void);

#endif
