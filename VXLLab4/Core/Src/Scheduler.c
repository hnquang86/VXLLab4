/*
 * Scheduler.c
 *
 *  Created on: Nov 29, 2024
 *      Author: PC
 */
#include "Scheduler.h"


// declare variable:
sTask SCH_task_G[SCH_MAX_TASKS];

// define functions:
void SCH_Init(){
	uint32_t i;
	for (i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}

	//add code here:


}

void SCH_Add_Task(void (*pFunction)(),
				  uint32_t DELAY,
				  uint32_t PERIOD){
	//
	uint32_t index = 0;
	while(SCH_task_G[index].pTask != 0 && index < SCH_MAX_TASKS){
		index++;
	}

	if(index == SCH_MAX_TASKS){

		return;
	}
	SCH_task_G[index].pTask = pFunction;
	SCH_task_G[index].Delay = DELAY / TICK;
	SCH_task_G[index].Period = PERIOD / TICK;
	SCH_task_G[index].RunMe = 0;
	SCH_task_G[index].TaskID = index;

}

void SCH_Update(){
	uint32_t index;
	for(index = 0; index < SCH_MAX_TASKS; index++){
		//check whether task is exist
		if(SCH_task_G[index].pTask){
			if(SCH_task_G[index].Delay == 0){
				// turn on flag to run task
				SCH_task_G[index].RunMe++;

				if(SCH_task_G[index].Period){
					// assign delay = period
					SCH_task_G[index].Delay = SCH_task_G[index].Period;
				}
			}else{
				SCH_task_G[index].Delay--;
			}
		}
	}
}

void SCH_Dispatch_Tasks(){
	uint32_t index;
	for(index = 0; index < SCH_MAX_TASKS; index++){
		if(SCH_task_G[index].RunMe > 0){

			(*SCH_task_G[index].pTask)(); // run task

			SCH_task_G[index].RunMe--;

			// delete task if period = 0
			if(SCH_task_G[index].Period == 0){
				SCH_Delete_Task(index);
			}
		}
	}
}

void SCH_Delete_Task(uint32_t index){
	if(SCH_task_G[index].pTask == 0){
		return;
	}
	SCH_task_G[index].pTask = 0x000;
	SCH_task_G[index].Delay = 0;
	SCH_task_G[index].Period = 0;
	SCH_task_G[index].TaskID = 0;
	SCH_task_G[index].RunMe = 0;

}










