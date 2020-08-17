#ifndef SYSTICK_PRIV_H
#define SYSTICK_PRIV_H

/********************************************/
/***********Private Definitions**************/
/********************************************/

#define SYSTICK_CTRL *((volatile u32 *)0xE000E010)
#define SYSTICK_LOAD *((volatile u32 *)0xE000E014)
#define SYSTICK_VAL *((volatile u32 *)0xE000E018)

#define ENABLE 0
#define TICKINT 0
#define CLKSOURCE 0
#define COUNTFLAG 0

/******************************************/
/***********Private Functions**************/
/******************************************/
void vidInterruptStub(void);
#endif
