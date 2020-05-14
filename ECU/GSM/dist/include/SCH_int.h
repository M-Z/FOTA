/*
 * SCHEDULER_int.h
 *
 *  Created on: Oct 12, 2018
 *      Author: sondo
 */

#ifndef SCH_INT_H_
#define SCH_INT_H_


/***************************************/
/********** Public Definitions *********/
/***************************************/
/* Task State Enum Definition */
typedef enum
{
	RUNNING,
	PAUSED
}task_state;


/* Task Struct Definition */
typedef struct
{
	u16 periodicity;
	u16 first_delay;
	task_state state;
	void (*task_ptr)(void);
}task;



/***************************************/
/********* Public Functions ************/
/***************************************/

/****************************************************************************************/
/* Description: Start Executing the Scheduler				   			              	*/
/* Input      : Void                                                     		     	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidStart(void);


/****************************************************************************************/
/* Description: Create New Task				   			           	                   	*/
/* Input      : u8 u8index                                                          	*/
/* 				Description:	index and priority of the task							*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* 																						*/
/*				task* temp_task 				                                        */
/*				Description: 	Pointer the task									 	*/
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidCreateTask(u8 u8index, task* temp_task);


/****************************************************************************************/
/* Description: Delete an existing Task				   			   	                   	*/
/* Input      : u8 u8index	                                                        	*/
/* 				Description:	index of the task										*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidDeleteTask(u8 index);

/****************************************************************************************/
/* Description: Stop an existing task from running			     	                   	*/
/* Input      : u8 u8index                                                          	*/
/* 				Description:	index of the task										*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidStopTask(u8 u8index);

/****************************************************************************************/
/* Description: Restart an existing paused task 			     	                   	*/
/* Input      : u8 u8index                                                          	*/
/* 				Description:	index of the task										*/
/* 				Range: 			0 -> MAX_TASKS_NUM	                                    */
/* Output     : Void                                                                   	*/
/* Scope      : Public                                                                 	*/
/****************************************************************************************/
void SCH_vidStartTask(u8 u8index);




#endif /* SCH_INT_H_ */
