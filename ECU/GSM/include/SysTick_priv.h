#ifndef _SysTick_PRIV_H
#define _SysTick_PRIV_H

#define SysTick_CTRL 	*((volatile u32 *) 0xE000E010)
#define SysTick_LOAD 	*((volatile u32 *) 0xE000E014)
#define SysTick_VAL 	*((volatile u32 *) 0xE000E018)

/*
 * Units declaration
 */
#define SECOND						1
#define MILLISECOND					0.001
#define MICROSECOND					0.000001

#define AHB							0
#define AHB_8						1

#define RCC_HSE 					0
#define RCC_HSI 					1
#define RCC_PLL 					2

#define PLL							0
#define PLL_HSE						1
#define PLL_HSI_DIV_2				2

#define PLL_INPUT_CLOCK_X_2 		0
#define PLL_INPUT_CLOCK_X_3 		1
#define PLL_INPUT_CLOCK_X_4 		2
#define PLL_INPUT_CLOCK_X_5 		3
#define PLL_INPUT_CLOCK_X_6 		4
#define PLL_INPUT_CLOCK_X_7 		5
#define PLL_INPUT_CLOCK_X_8 		6
#define PLL_INPUT_CLOCK_X_9 		7
#define PLL_INPUT_CLOCK_X_10 		8
#define PLL_INPUT_CLOCK_X_11 		9
#define PLL_INPUT_CLOCK_X_12 		10
#define PLL_INPUT_CLOCK_X_13 		11
#define PLL_INPUT_CLOCK_X_14 		12
#define PLL_INPUT_CLOCK_X_15 		13
#define PLL_INPUT_CLOCK_X_16 		14
#endif
