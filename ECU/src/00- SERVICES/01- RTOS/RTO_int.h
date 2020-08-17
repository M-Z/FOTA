#ifndef _RTO_INT_H
#define _RTO_INT_H

typedef struct {
	u8 ID;
	u16 CurrentDelay;
	u16 Periodicity;
	u8 Priority;
	enum {
		run,
		wait
	} state;
	void (*CallbackFunction)(void);
} Task;

#define TASKS_NUM 2

extern Task newTasksArray[];

void RTO_voidStartOS();
void RTO_voidInit(Task[]);
Error_Status RTO_enumCreateTask(Task*);
Error_Status RTO_enumDeleteTask(u8);
Error_Status RTO_enumStopTask(u8);
Error_Status RTO_enumRunTask(u8);

#endif
