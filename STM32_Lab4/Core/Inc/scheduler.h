/*
 * scheduler.h
 *
 *  Created on: Oct 21, 2024
 *      Author: ADMIN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#define SCH_MAX_TASKS 40
#define TICK 10
#define ERROR_SCH_TOO_MANY_TASKS 99
#define ERROR_SCH_CANNOT_DELETE_TASK 999

#include <stdint.h>

typedef struct{
	void (*pTask)(void);
	int Delay;
	int Period;
	int RunMe;

	int TaskID;
}sTasks;

void SCH_Init(void);
void SCH_Add_Task(void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(uint32_t ID);


#endif /* INC_SCHEDULER_H_ */
