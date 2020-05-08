#ifndef _SysTick_CONFIG_H
#define _SysTick_CONFIG_H

/********************************************
 * 	Description:			Choose clock source			*
 *		Range:					AHB										*
 *										AHB_8									*
 ********************************************/
#define CLK_SRC AHB
#define UNIT	MILLISECOND	// MILLISECOND, MICROSECOND, SECOND

/******************************************************
 * 	Description:		Time unit														*
 *		Range:				MILLISECOND												*
 *									MICROSECOND											*
 *									SECOND														*
 ******************************************************/
#define UNIT	MILLISECOND

#endif	/* _SysTick_CONFIG_H */
