/*
 * SysTick_int.h
 *
 *  Created on: 21 Aug 2019
 *      Author: Mario
 */
#ifndef _SysTick_INT_H
#define _SysTick_INT_H

/**
  * @brief 		 Initialises the system tick.
  * @param  	void
  * @retval 	Error_Status
  */
Error_Status SysTick_enumInit(void);

/**
  * @brief  			Sets the callback function to execute in the handler.
  * @param  		void (*x)(void): The callback function which gives and returns a void
  * @retval 		void
  */
void SysTick_SetCallback(void (*x)(void));

/**
  * @brief  			Delays the system
  * @note			The delay unit is specified in the config file
  * @param  		time: the amount of time to delay with
  * @retval 		void
  */
void SysTick_delay( u32 );

#endif	/* _SysTick_INT_H */
