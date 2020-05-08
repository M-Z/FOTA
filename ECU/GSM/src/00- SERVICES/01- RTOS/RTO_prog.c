#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "01- MCAL/04- SysTick/SysTick_int.h"

#include "00- SERVICES/01- RTOS/RTO_int.h"
#include "00- SERVICES/01- RTOS/RTO_priv.h"

Task TaskQueue[QUEUE_LENGTH];		// All the tasks including empty ones
MAX_LENGTH_TYPE currentLength;		// Current queue length
u8 globalFlag;						// Global SysTick flag

/**
  * @brief  Starts a super-loop to check for system ticks
  * @note	This function is to avoid a heavy Systick_handler critical section
  * @param  void
  * @retval void
  */
void RTO_voidStartOS(void) {
	globalFlag = 0;

	RTO_voidInit(newTasksArray);

	while(1) {

		// Check if System tick occurred
		if (globalFlag) {
			globalFlag = 0;
			RTO_voidSchedular();		// Call Scheduler
		}
	}
}

static void setFlag(void) {
	globalFlag = 1;
}

/**
  * @brief 	Initialises the SysTick and puts the initial tasks list
  * @param  Task newTasks[]: The tasks array list
  * @retval void
  */
void RTO_voidInit(Task newTasks[]) {
	#ifdef TASKS_NUM
		#if TASKS_NUM <= QUEUE_LENGTH
			SysTick_enumInit();
			SysTick_SetCallback(setFlag);

			currentLength = TASKS_NUM;

			u8 x;

			// Mark all of the queue as empty
			for (x = 0; x < QUEUE_LENGTH; x++) {
				TaskQueue[x].Periodicity = 0;
				TaskQueue[x].Priority = 0;
			}

			// Assign tasks to the queue
			for (x = 0; x < TASKS_NUM; x++) {
				if (newTasks[x].Priority > TaskQueue[x].Priority) {
					TaskQueue[x] = newTasks[x];
				}
			}
		#endif
	#endif
}

static void RTO_voidSchedular(void) {

	// Loop through current queue length
	for (u8 currentLocation = 0; currentLocation < currentLength; currentLocation++) {

		// Task exists
		if(TaskQueue[currentLocation].Periodicity != 0) {

			// Current task's tick is now
			if(TaskQueue[currentLocation].CurrentDelay == 0) {

				// Has highest priority
				if(TaskQueue[currentLocation].state == run) {
					TaskQueue[currentLocation].CallbackFunction(); // Execute
				} else {}

				// Reset delay
				TaskQueue[currentLocation].CurrentDelay = TaskQueue[currentLocation].Periodicity - 1;

			} else {
				TaskQueue[currentLocation].CurrentDelay--;
			}

		} else {}
	}
}

/**
  * @brief  Creates a new task and puts it in the current queue
  * @param  Task* newTask: the new specified task to be added
  * @retval Error_Status
  */
Error_Status RTO_enumCreateTask(Task* newTask) {
	Error_Status returnVal = NOK;

	// Still have space to add
	if (currentLength < QUEUE_LENGTH) {
		Task* tempTask;
		_Bool swapped = 0;

		// Linear search for the ID
		for (u8 x = 0; x < currentLength; x++) {

			// If the current task has higher priority
			if (newTask->ID >= TaskQueue[x].Priority) {
				// Swap with the temp value
				tempTask = &TaskQueue[x];
				TaskQueue[x] = *newTask;
				newTask = tempTask;

				if (!swapped) {
					swapped = 1;
					currentLength++;		// New element added
					returnVal = OK;
				}
			}
		}
	} else {
		returnVal = limitReached;
	}


	return returnVal;
}

/**
  * @brief  Creates a new task and puts it in the current queue
  * @param  Task* newTask: the new specified task to be added
  * @retval Error_Status
  */
Error_Status RTO_enumDeleteTask(u8 TaskID) {
	Error_Status returnVal = elementNotFound;
	_Bool removed = 0;

	// Linear search for the IDs
	for (u8 x = 0; x < currentLength; x++) {

		// Mark if not used
		if (TaskQueue[x].ID == TaskID) {
			TaskQueue[x] = TaskQueue[x + 1];
			x--;
			removed = 1;
			currentLength--;
			returnVal = OK;
		}
	}

	// If any removal happened
	if (removed) {
		TaskQueue[currentLength - 1].Periodicity = 0;
	} else {}

	return returnVal;
}

/**
  * @brief  Marks specified task as waiting
  * @param  u8 TaskID: the unique task ID
  * @retval Error_Status
  */
Error_Status RTO_enumStopTask(u8 TaskID){
	Error_Status returnVal = elementNotFound;

	// Linear search for the ID
	for (u8 x = 0; x < currentLength; x++) {
		if (TaskID == TaskQueue[x].ID) {
			TaskQueue[x].state = wait;
			returnVal = OK;
		}
	}

	return returnVal;
}

/**
  * @brief  Make the task run in the next interation
  * @param  u8 TaskID: the unique task ID
  * @note	The task ID should be unique and specified by the user at runtime
  * @retval Error_Status
  */
Error_Status RTO_enumRunTask(u8 TaskID) {
	Error_Status returnVal = elementNotFound;

	// Linear search for the ID
	for (u8 x = 0; x < currentLength; x++) {
		if (TaskID == TaskQueue[x].ID) {
			TaskQueue[x].state = run;
			returnVal = OK;
		}
	}

	return returnVal;
}
