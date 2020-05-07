#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "01- MCAL/08- FPEC/FPEC_int.h"
#include "01- MCAL/08- FPEC/FPEC_priv.h"
#include "01- MCAL/08- FPEC/FPEC_conf.h"

void FPEC_voidUnlock(void) {
	if (GET_BIT(FPEC->CR, 7) == 1) {
		FPEC->KEYR = KEY1;

	} else {}
}

void FPEC_voidMassErase(void) {
	FPEC_voidUnlock();
	while (GET_BIT(FPEC->SR, 0) == 1);	// Check that no main Flash memory operation is ongoing
	SET_BIT(FPEC->CR, 2);				// Erase of all user pages chosen
	SET_BIT(FPEC->CR, 6);				// Triggers an ERASE operation when set

	while (GET_BIT(FPEC->SR, 0) == 1);	// Wait for the BSY bit to be reset
	// Read all the pages and verify
}


void FPEC_voidErasePage(u32 FlashAddress) {
	FPEC_voidUnlock();
	while (GET_BIT(FPEC->SR, 0) == 1);	// Check that no main Flash memory operation is ongoing

	SET_BIT(FPEC->CR, 1);				// Page Erase chosen

	FPEC->AR = FlashAddress;			// Select a page to erase
	SET_BIT(FPEC->CR, 6);				// Triggers an ERASE operation when set


	while (GET_BIT(FPEC->SR, 0) == 1);	// Wait for the BSY bit to be reset

	// Read the erased page and verify
}


void FPEC_voidProgram(u32 Address, u32 Data) {
	FPEC_voidUnlock();
	while (GET_BIT(FPEC->SR, 0) == 1);	// Check that no main Flash memory operation is ongoing

	SET_BIT(FPEC->CR, 0);				// Flash programming chosen
	* ((u32* ) (MAIN_MEMORY_BASE_ADDRESS + Address)) = Data;

	//Perform the data write (half-word) at the desired address.

	while (GET_BIT(FPEC->SR, 0) == 1);	// Wait for the BSY bit to be reset

	// Read the programmed value and verify
}
