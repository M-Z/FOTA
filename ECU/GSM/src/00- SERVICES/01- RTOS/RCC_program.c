#include <04- LIB/STD_TYPES.h>
#include <04- LIB/BIT_MATH.h>

#include <01- MCAL/01- RCC/RCC_int.h>
#include <01- MCAL/01- RCC/RCC_conf.h>
#include <01- MCAL/01- RCC/RCC_priv.h>

/**
  * @brief  Initialises the system clock.
  * @note   Options should be set in the _conf.h file
  * @param  void
  * @retval Error_Status
  */
Error_Status RCC_enumInit(void) {

	#if	(SYSTEM_CLOCK_SOURCE ==  RCC_HSE)

		RCC->CR |= 0x00010000; 					// Set High speed enable (HSE) Clock enable

		while ( !( RCC->CR & 0x00020000 ) ){};	// Check for External high-speed clock ready flag

		RCC->CFGR = RCC->CFGR | 0x00000001;		// Select system clock source

		// Check if  System clock switch status is  HSE
		if (SYST_CLK_STATUS != 0x00000004) {
			return NOK;
		} else {
			return OK;
		}

	#elif (SYSTEM_CLOCK_SOURCE ==  RCC_HSI)

		RCC->CR |= 0x00000001;

		while (! (RCC->CR & 0x00000002) ){};

		RCC->CFGR = RCC->CFGR | 0x00000001;

		if (SYST_CLK_STATUS != 0) {
			return NOK;
		} else {
			return OK;
		}

	#elif (SYSTEM_CLOCK_SOURCE ==  RCC_PLL)

		#if	(PLL_SOURCE == PLL_HSE)

			RCC->CR |= 0x00010000;						// PLL ON
			while (! (RCC->CR & 0x00020000) ){};			// Wait for PLL Ready

			// Divide external clock by 2
			#if		(HSE_DIVIDE)
				RCC->CFGR |= 0x00020000
			#else
				RCC->CFGR &= 0xFFFDFFFF;
			#endif

			RCC->CFGR |= 0x00010000;					// HSE oscillator clock selected as PLL input clock
		#elif (PLL_SOURCE  == PLL_HSI_DIV_2)
			RCC->CR |= 0x00000001;
			while (! (RCC->CR & 0x00000002) );
			RCC->CFGR &= 0xFFF0FFFF;
		#endif

		RCC->CFGR &= 0xFFC3FFFF;					// Clear all CFGR register except for PLLMUL
		#if	(PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_2)
			RCC->CFGR &= 0x00000000;
		#elif (PLL_MULTIPLIER ==  PLL_INPUT_CLOCK_X_3)
			RCC->CFGR &= 0x00040000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_4)
			RCC->CFGR &= 0x00080000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_5)
			RCC->CFGR &= 0x000C0000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_6)
			RCC->CFGR &= 0x00100000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_7)
			RCC->CFGR &= 0x00140000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_8)
			RCC->CFGR &= 0x00180000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_9)
			RCC->CFGR &= 0x001C0000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_10)
			RCC->CFGR &= 0x00200000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_11)
			RCC->CFGR &= 0x00240000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_12)
			RCC->CFGR &= 0x00280000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_13)
			RCC->CFGR &= 0x002C0000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_14)
			RCC->CFGR &= 0x00300000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_15)
			RCC->CFGR &= 0x00340000;
		#elif (PLL_MULTIPLIER == PLL_INPUT_CLOCK_X_16)
			RCC->CFGR &= 0x00380000;
		#endif

		RCC->CFGR &= 0x00000002;

		if ( SYST_CLK_STATUS != 0x00000008 ) {
			return NOK;
		} else {
			return OK;
		}

	#endif

	#if	(CLOCK_SECURITY_SYSTEM == DISABLE)
		RCC->CR &= 0xFFF7FFFF;
	#elif	(CLOCK_SECURITY_SYSTEM == ENABLE)
		RCC->CR |= 0x00080000;
	#endif
}

/**
  * @brief  Supplies the processor clock to specified peripheral
  * @param  PeripheralName: x_CLOCK where x is the peripheral name
  * @retval Error_Status
  */
Error_Status RCC_enumEnableClock( u8 PeripheralName ) {
	if (PeripheralName < 94) {
		SET_BIT( *( (volatile u32*) (&RCC->AHBENR + ((u32) PeripheralName / 32) )  ), PeripheralName % 32);
		return OK;
	} else {
		return numberOutOfRange;
	}

}

/**
  * @brief  Removes the processor clock to any specified peripheral.
  * @param  PeripheralName: x_CLOCK where x is the peripheral name
  * @retval Error_Status
  */
Error_Status RCC_enumDisableClock( u8 PeripheralName ) {
	if (PeripheralName < 94) {
		CLEAR_BIT( *( (volatile u32*) (&RCC->AHBENR + ((u32) PeripheralName / 32) )  ), PeripheralName % 32);
		return OK;
	} else {
		return numberOutOfRange;
	}
}
