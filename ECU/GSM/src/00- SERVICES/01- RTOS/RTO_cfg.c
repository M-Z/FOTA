#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "00- SERVICES/01- RTOS/RTO_int.h"
#include "00- SERVICES/01- RTOS/RTO_conf.h"

#include <01- MCAL/01- RCC/RCC_int.h>
#include <01- MCAL/02- GPIO/GPIO_int.h>

void test1() {
	GPIO_enumSetPinValue(0, 0);
	GPIO_enumSetPinValue(3, 1);
}

void test2() {
	GPIO_enumSetPinValue(3, 0);
	GPIO_enumSetPinValue(0, 1);
}

Task newTasksArray[TASKS_NUM] = {
	{0, 0, 1000, 1, run, test1},
	{1, 0, 2000, 1, run, test2}
};
