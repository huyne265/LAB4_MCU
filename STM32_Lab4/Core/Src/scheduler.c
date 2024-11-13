/*
 * scheduler.c
 *
 *  Created on: Oct 21, 2024
 *      Author: ADMIN
 */


#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;
uint32_t SCH_time = 0;

void SCH_Init(void) {
    current_index_task = 0;
    SCH_time = 0;
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
    if (current_index_task < SCH_MAX_TASKS) {
        SCH_tasks_G[current_index_task].pTask = pFunction;
        SCH_tasks_G[current_index_task].Delay = DELAY / TICK;
        SCH_tasks_G[current_index_task].Period = PERIOD / TICK;
        SCH_tasks_G[current_index_task].RunMe = 0;
        SCH_tasks_G[current_index_task].TaskID = current_index_task;

        current_index_task++;
    }
}

void SCH_Update(void) {
	SCH_time++;
    if(SCH_time > UINT32_MAX) SCH_time = 0;
}

void SCH_Dispatch_Tasks(void) {
    for(int i = 0; i < current_index_task; i++){
        if(SCH_time >= SCH_tasks_G[i].Delay){
            SCH_tasks_G[i].RunMe++;
            if(SCH_tasks_G[i].Period > 0){
            	if(SCH_time + SCH_tasks_G[i].Period <= UINT32_MAX) SCH_tasks_G[i].Delay += SCH_tasks_G[i].Period;
            	else{
            		SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period - (UINT32_MAX - SCH_tasks_G[i].Delay);
            		SCH_tasks_G[i].RunMe--;
            	}
            }
            else SCH_Delete_Task(i);
        }
        if(SCH_tasks_G[i].RunMe > 0){
            SCH_tasks_G[i].RunMe--;
            (*SCH_tasks_G[i].pTask)();
        }
    }
}

void SCH_Delete_Task(uint32_t ID) {
    if( ID < current_index_task) {
        for(int i = ID; i < current_index_task - 1; i++) {
            SCH_tasks_G[i] = SCH_tasks_G[i + 1];
        }
        SCH_tasks_G[current_index_task - 1].pTask = 0x0000;
       	SCH_tasks_G[current_index_task - 1].Delay = 0;
       	SCH_tasks_G[current_index_task - 1].Period = 0;
       	SCH_tasks_G[current_index_task - 1].RunMe = 0;
       	SCH_tasks_G[current_index_task - 1].TaskID = 0;
        current_index_task--;
    }
}
