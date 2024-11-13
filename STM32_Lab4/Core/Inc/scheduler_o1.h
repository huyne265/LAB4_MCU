/*
 * scheduler_o1.h
 *
 *  Created on: Nov 3, 2024
 *      Author: admin
 */

#ifndef INC_SCHEDULER_O1_H_
#define INC_SCHEDULER_O1_H_

#define SCH_MAX_TASKS 40
#define TICK 10
#define ERROR_SCH_TOO_MANY_TASKS 99
#define ERROR_SCH_CANNOT_DELETE_TASK 999

#include <stdint.h>

typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;

	uint32_t TaskID;
}sTasks;

void SCH_Init(void);
void SCH_Add_Task (void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete(uint32_t ID);
void swapTasks(int i, int j);
void heapifyDown(int index);
void heapifyUp(int index);

#endif /* INC_SCHEDULER_O1_H_ */
