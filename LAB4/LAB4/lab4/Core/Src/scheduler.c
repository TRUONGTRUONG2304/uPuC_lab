/*
 * scheduler.c
 *
 *  Created on: Oct 14, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "scheduler.h"

Tasks SCH_tasks_G[MAX_TOTAL_TASKS];
Tasks SCH_waiting_queue[MAX_TOTAL_TASKS];

tByte Error_code_G;
tWord Error_tick_count_G;
tByte Last_error_code_G;
void SCH_Init(){
	for(int i = 0; i < MAX_TOTAL_TASKS; i++){
		SCH_Delete_Task(i);
	}
	// Reset the global error variable
	// − SCH_Delete_Task () will generate an error code ,
	// ( because the task array is empty)
	Error_code_G = 0;
	Watchdog_Init();
}
void SCH_Update(){
	if(SCH_tasks_G[0].TaskFunction){
		SCH_tasks_G[0].Delay_TIME--;
		if(SCH_tasks_G[0].Delay_TIME <= 0){
			//This task is due to run, increase RunMe
			SCH_tasks_G[0].RunMe++;
		}
	}
}
void SCH_Dispatch_Tasks(){
	if(SCH_tasks_G[0].RunMe > 0){
		//Run task
		(*SCH_tasks_G[0].TaskFunction)();
		//Reset/Reduce RunMe flag
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
		SCH_tasks_G[0].RunMe--;
		if(SCH_tasks_G[0].sameDelay == 1){
			SCH_tasks_G[1].RunMe++;
		}
		//If this task is 'one shot' task, remove it from the array
		if(SCH_tasks_G[0].Period_TIME == 0){
			SCH_Delete_Task(0);
		}
		else{
			//Schedule preriodic task to run again
			SCH_tasks_G[0].Delay_TIME = SCH_tasks_G[0].Period_TIME;
			Tasks taskTemp = SCH_tasks_G[0];
			SCH_Delete_Task(0);
			SCH_Add_Task(taskTemp.TaskFunction, taskTemp.Delay_TIME, taskTemp.Period_TIME);
		}

	}
	// Report system status
	SCH_Report_Status();
	// The scheduler enters idle mode at this point
	SCH_Go_To_Sleep();
}
uint32_t SCH_Add_Task(void (*pfunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint32_t Index = 0, slot = 0;
	uint32_t Delay_temp = 0;
	unsigned char check = 0;
	while((SCH_tasks_G[Index].TaskFunction != 0) && (Index < MAX_TOTAL_TASKS)){
		if(!check){
			Delay_temp += SCH_tasks_G[Index].Delay_TIME;
		}
		if(Delay_temp > DELAY && !check){
			slot = Index;
			check = 1;
			Delay_temp -= SCH_tasks_G[slot].Delay_TIME;
		}
		if(Delay_temp == DELAY){
			SCH_tasks_G[Index].sameDelay = 1;
		}
		Index++;
	}
	if(Index == MAX_TOTAL_TASKS){
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		return Index;
	}
	if(check == 0){
		SCH_tasks_G[Index].Delay_TIME = DELAY - Delay_temp;
		SCH_tasks_G[Index].Period_TIME = PERIOD;
		SCH_tasks_G[Index].RunMe = 0;
		SCH_tasks_G[Index].TaskFunction = pfunction;
		SCH_tasks_G[Index].sameDelay = 0;
	}
	else{
		Tasks taskTemp;
		for(int i = slot; i < Index; i++){
			taskTemp = SCH_tasks_G[i+1];
			SCH_tasks_G[i+1] = SCH_tasks_G[slot];
			SCH_tasks_G[slot] = taskTemp;
		}
		SCH_tasks_G[slot].Delay_TIME = DELAY - Delay_temp;
		SCH_tasks_G[slot].Period_TIME = PERIOD;
		SCH_tasks_G[slot].RunMe = 0;
		SCH_tasks_G[slot].sameDelay = 0;
		SCH_tasks_G[slot].TaskFunction = pfunction;
		SCH_tasks_G[slot+1].Delay_TIME -= SCH_tasks_G[slot].Delay_TIME;
	}
	return Index;
}
uint8_t SCH_Delete_Task(uint32_t taskID){
	unsigned char returnCode;
	if(SCH_tasks_G[taskID].TaskFunction == 0){
		//No task at this location
		//Set the global error variable
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		returnCode = RETURN_ERROR;
	}
	else{
		returnCode = RETURN_NORMAL;
	}
	while((SCH_tasks_G[taskID].TaskFunction != 0) && (taskID+1 < MAX_TOTAL_TASKS)){
		SCH_tasks_G[taskID] = SCH_tasks_G[taskID+1];
		taskID++;
		if(SCH_tasks_G[taskID+1].TaskFunction == 0){
			break;
		}
	}
	SCH_tasks_G[taskID].Delay_TIME = 0;
	SCH_tasks_G[taskID].Period_TIME = 0;
	SCH_tasks_G[taskID].TaskFunction = 0x0000;
	SCH_tasks_G[taskID].RunMe = 0;
	SCH_tasks_G[taskID].sameDelay = 0;
	return returnCode;
}
void Watchdog_Init(){

}
void SCH_Report_Status(){
#ifdef SCH_REPORT_ERRORS
   // ONLY APPLIES IF WE ARE REPORTING ERRORS
   // Check for a new error code
   if (Error_code_G != Last_error_code_G)
      {
      // Negative logic on LEDs assumed
      Error_port = 255 - Error_code_G;

      Last_error_code_G = Error_code_G;

      if (Error_code_G != 0)
         {
         Error_tick_count_G = 60000;
         }
      else
         {
         Error_tick_count_G = 0;
         }
      }
   else
      {
      if (Error_tick_count_G != 0)
         {
         if (--Error_tick_count_G == 0)
            {
            Error_code_G = 0; // Reset error code
            }
         }
      }
#endif
}
void SCH_Go_To_Sleep(){

}
