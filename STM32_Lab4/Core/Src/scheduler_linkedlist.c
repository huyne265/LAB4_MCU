///*
// * scheduler.c
// *
// *  Created on: Oct 21, 2024
// *      Author: ADMIN
// */
/*
 * scheduler.c
 *
 *  Created on: Oct 21, 2024
 *      Author: ADMIN
 */
#include "scheduler.h"
sTasks SCH_tasks_G[SCH_MAX_TASKS];
int current_index_task = 0;
int Error_code_G = 0;

void SCH_Init(void){
	current_index_task = 0;
	Error_code_G = 0;
}

void SCH_Add_Task (void (*pFunction)() , int DELAY, int PERIOD){
	if( current_index_task >= SCH_MAX_TASKS) return;
	sTasks newTask = {pFunction, DELAY/TICK, PERIOD/TICK, 0, current_index_task};
	if( current_index_task == 0){
		SCH_tasks_G[0] = newTask;
		current_index_task++;
		return;
	}
	int i = 0;
	while( i < current_index_task && SCH_tasks_G[i].Delay <= newTask.Delay ){
		newTask.Delay -= SCH_tasks_G[i].Delay;
		i++;
	}
	for(int j = current_index_task; j > i ; j--){
		SCH_tasks_G[j] = SCH_tasks_G[j - 1];
		if(SCH_tasks_G[j].Delay >= newTask.Delay) SCH_tasks_G[j].Delay -= newTask.Delay;
	}
	SCH_tasks_G[i] = newTask;
	current_index_task++;
}

void SCH_Update(void){
	if(SCH_tasks_G[0].pTask){
		if( SCH_tasks_G[0].Delay > 0 ) SCH_tasks_G[0].Delay--;
		else SCH_tasks_G[0].RunMe++;
	}
}

void SCH_Dispatch_Tasks(void){
		if(SCH_tasks_G[0].RunMe > 0){
			SCH_tasks_G[0].RunMe--;
			(*SCH_tasks_G[0].pTask)();
			if(SCH_tasks_G[0].Period > 0){
				SCH_Add_Task(SCH_tasks_G[0].pTask, SCH_tasks_G[0].Period*TICK, SCH_tasks_G[0].Period*TICK);
			}
			SCH_Delete(0);
		}
}
void SCH_Delete(int ID){
	if(SCH_tasks_G[ID].pTask == 0 || ID >= SCH_MAX_TASKS){
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		return;
	}
	for(int i = ID; i < current_index_task - 1; i++ ){
			SCH_tasks_G[i] = SCH_tasks_G[i + 1];
	}
	SCH_tasks_G[current_index_task - 1].pTask = 0x0000;
	SCH_tasks_G[current_index_task - 1].Delay = 0;
	SCH_tasks_G[current_index_task - 1].Period = 0;
	SCH_tasks_G[current_index_task - 1].RunMe = 0;
	SCH_tasks_G[current_index_task - 1].TaskID = 0;
	current_index_task--;
}
