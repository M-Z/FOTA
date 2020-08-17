#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <01- MCAL/04- SysTick/SysTick_int.h>
#include <01- MCAL/04- SysTick/SysTick_conf.h>
#include <01- MCAL/04- SysTick/SysTick_priv.h>

#include <01- MCAL/01- RCC/RCC_conf.h>

void (*CallbackFunction)(void);			// Not stored in memory at startup

static void SysTick_Stub (void) {
	__asm__("NOP");
}

/**
  * @brief  Initialises the system tick.
  * @param  void
  * @retval Error_Status
  */
void SysTick_enumInit(void) {
	SysTick_VAL = 0;				// Reinitialise clock counter

	u32 val = 79990;				// Initial static value for HSI
	#if	(SYSTEM_CLOCK_SOURCE 	==	RCC_HSE)
		val = F_CPU * 1000000;
	#elif (SYSTEM_CLOCK_SOURCE 	==  RCC_HSI)
		val = 8000000;
	#elif (SYSTEM_CLOCK_SOURCE 	==  RCC_PLL)

		#if	(PLL_SOURCE == PLL_HSE)
			val = F_CPU * 500000;
		#elif (PLL_SOURCE  == PLL_HSI_DIV_2)
			val = 4000000;
		#endif

		#if	(PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_2)
			val *= 2;
		#elif (PLL_MULTIPLIER ==  PLL_INPUT_CLOCK_X_3)
			val *= 3;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_4)
			val *= 4;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_5)
			val *= 5;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_6)
			val *= 6;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_7)
			val *= 7;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_8)
			val *= 8;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_9)
			val *= 9;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_10)
			val *= 10;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_11)
			val *= 11;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_12)
			val *= 12;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_13)
			val *= 13;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_14)
			val *= 14;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_15)
			val *= 15;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_16)
			val *= 16;
		#endif
	#endif

	#if	(CLK_SRC == AHB)			// AHB clock speed
		SysTick_CTRL |= 0x00000004;
	#elif	(CLK_SRC == AHB_8) 		// AHB/8 clock speed
		val /= 8;
		SysTick_CTRL &= 0xFFFFFFFB;
	#endif

	SysTick_LOAD = UNIT * val - 1;	// (1ms, 1mms, 1s) * clock speed

	SysTick_CTRL |= 3; 				// Counter enable and SysTick exception request enable

	CallbackFunction = SysTick_Stub;
}

void SysTick_SetCallback(void (*x)(void)) {
	CallbackFunction = x;
}

void __attribute__ ((section(".after_vectors"), weak))
SysTick_Handler (void) {
	CallbackFunction();
}
