/*
 * SCH_prog.c
 *
 *  Created on: Oct 12, 2018
 *      Author: sondo
 */

#include "STD_Types.h"
#include "util.h"
#include "SYSTICK_int.h"
#include "SCH_priv.h"
#include "SCH_cfg.h"
#include "SCH_int.h"


/* Tasks Array */
static task* task_arr[MAX_TASKS_NUM];


/****************************************************************************************/
/* Description: Start Executing the Scheduler				   			              	*/
/* Input      : Void                                                     		     	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidStart(void)
{
	SYSTICK_vidSetCallback(&Scheduler);
	SYSTICK_vidInit(OVF_COUNT);
}


/****************************************************************************************/
/* Description: Create New Task				   			           	                   	*/
/* Input      : u8 u8index                                                          	*/
/* 				Description:	index and priority of the task							*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* 										                                                */
/* 				u8 u8periodicity                   		                              	*/
/*              Description: 	Periodicity of the function                             */
/* 				Range: 			0 -> 256                                                */
/*             																		    */
/*				u8 u8firstdelay 													   	*/
/*				Description: 	first delay of the task in the begining of the scheduler*/
/*				Range: 			0 -> 256                                                */
/*                																	  	*/
/*				task_state taskstate                                                   	*/
/*				Description: 	state of the task running if it's active, and pasused   */
/* 							 	paused if inactive 	                                   	*/
/*				Range: 			RUNNING, PAUSED											*/
/*																						*/
/*	       		void (*task_pointer)(void)												*/
/*				Description: 	Pointer the function of the task					 	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidCreateTask(u8 u8index, task* temp_task)
{
	task_arr[u8index] = temp_task;
}


/****************************************************************************************/
/* Description: Delete an existing Task				   			   	                   	*/
/* Input      : u8 u8index	                                                        	*/
/* 				Description:	index of the task										*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidDeleteTask(u8 index)
{
	task_arr[index]->state = PAUSED;
}


/****************************************************************************************/
/* Description: Stop an existing task from running			     	                   	*/
/* Input      : u8 u8index                                                          	*/
/* 				Description:	index of the task										*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidStopTask(u8 u8index)
{
	task_arr[u8index]->state = PAUSED;
}

/****************************************************************************************/
/* Description: Restart an existing paused task 			     	                   	*/
/* Input      : u8 u8index                                                          	*/
/* 				Description:	index of the task										*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidStartTask(u8 u8index)
{
	task_arr[u8index]->state = RUNNING;
}


/***************************************************************************************/
/* Description: Scheduler Function							                           */
/* Input      : Void                                                                   */
/* Output     : Void                                                                   */
/* Scope      : Private                                                                */
/***************************************************************************************/
void Scheduler(void)
{
	u8 u8TaskNumber = 0;
	/* Loop on all tasks */
	for (u8TaskNumber=0; u8TaskNumber<MAX_TASKS_NUM; u8TaskNumber++)
	{
		/* Check the task is enabled */
		if (task_arr[u8TaskNumber]->state == RUNNING)
		{
			/* Check if first delay equals 0 to execute the function */
			if (task_arr[u8TaskNumber]->first_delay == 0)
			{
				/* Call the task */
				(task_arr[u8TaskNumber]->task_ptr)();

				/* Reload first delay */
				task_arr[u8TaskNumber]->first_delay = task_arr[u8TaskNumber]->periodicity -1;
			}
			/* If first delay isn't 0 */
			else
			{
				/* Decrement fisr_delay */
				task_arr[u8TaskNumber]->first_delay --;
			}
		}
	}
}


///***************************************************************************************/
///* Description: Systick Interrupt Handler Function							           */
///* Input      : Void                                                                   */
///* Output     : Void                                                                   */
///* Scope      : Private                                                                */
///***************************************************************************************/
//void SystickInterruptHandler(void)
//{
//	static u16 u16OverflowCounter = 0;
//	if (u16OverflowCounter == OVF_COUNT)
//	{
//		Scheduler();
//		u16OverflowCounter = 0;
//	}
//	else
//	{
//		u16OverflowCounter++;
//	}
//}






