/*
 * scheduler.c
 *
 *  Created on: Oct 14, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "scheduler.h"

Tasks SCH_tasks_G[MAX_TOTAL_TASKS];
Tasks SCH_waiting_queue[MAX_TOTAL_WAIT_QUEUE_TASKS];

tByte Error_code_G;
tWord Error_tick_count_G;
tByte Last_error_code_G;
void SCH_Init(){
	for(int i = 0; i < MAX_TOTAL_TASKS; i++){
		SCH_tasks_G[i].Delay_TIME = 0;
		SCH_tasks_G[i].Period_TIME = 0;
		SCH_tasks_G[i].TaskFunction = 0x0000;
		SCH_tasks_G[i].RunMe = 0;
		SCH_tasks_G[i].sameDelay = 0;
	}
	for(int i = 0; i < MAX_TOTAL_WAIT_QUEUE_TASKS; i++){
		SCH_waiting_queue[i].Delay_TIME = 0;
		SCH_waiting_queue[i].Period_TIME = 0;
		SCH_waiting_queue[i].TaskFunction = 0x0000;
		SCH_waiting_queue[i].RunMe = 0;
		SCH_waiting_queue[i].sameDelay = 0;
	}
	// Reset the global error variable
	// − SCH_Delete_Task () will generate an error code ,
	// ( because the task array is empty)
//	Error_code_G = 0;
//	Watchdog_Init();
}
void SCH_Update(){
//	If SCH_tasks_G has tasks
	if(SCH_tasks_G[0].TaskFunction){
//		Decrease delay of task
		SCH_tasks_G[0].Delay_TIME--;
//		If The task is due to run set RunMe = 1
		if(SCH_tasks_G[0].Delay_TIME <= 0){
			//This task is due to run, increase RunMe
			SCH_tasks_G[0].RunMe = 1;
		}
	}
}
void SCH_Dispatch_Tasks(){
	if(SCH_tasks_G[0].RunMe > 0){

		while(SCH_tasks_G[0].sameDelay == 1){
			enqueue(SCH_tasks_G[0]);
			SCH_Delete_Task(0);
		}
		enqueue(SCH_tasks_G[0]);
		SCH_Delete_Task(0);

	}
	//Nếu có task cần thực thi
	if(SCH_waiting_queue[0].TaskFunction != 0){
		//Run task
		(*SCH_waiting_queue[0].TaskFunction)();

		dequeue();
	}
	// Report system status
	//SCH_Report_Status();
	// The scheduler enters idle mode at this point
	//SCH_Go_To_Sleep();
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
	//If task didn't exist
	if(SCH_tasks_G[taskID].TaskFunction == 0){
		//No task at this location
		//Set the global error variable
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		returnCode = RETURN_ERROR;
	}
	else{
		returnCode = RETURN_NORMAL;
	}
	while((SCH_tasks_G[taskID].TaskFunction != 0) && (taskID + 1 < MAX_TOTAL_TASKS)){
		SCH_tasks_G[taskID] = SCH_tasks_G[taskID+1];
		taskID++;
	}
	//reset
	SCH_tasks_G[taskID].Delay_TIME = 0;
	SCH_tasks_G[taskID].Period_TIME = 0;
	SCH_tasks_G[taskID].TaskFunction = 0x0000;
	SCH_tasks_G[taskID].RunMe = 0;
	SCH_tasks_G[taskID].sameDelay = 0;
	return returnCode;
}
void enqueue(Tasks taskToAdd){
	uint32_t index_queue = 0;
	while(SCH_waiting_queue[index_queue].TaskFunction != 0 ){
		index_queue++;
	}
	SCH_waiting_queue[index_queue] = taskToAdd;
}
void dequeue(){
	if(SCH_waiting_queue[0].Period_TIME){
		SCH_Add_Task(SCH_waiting_queue[0].TaskFunction, SCH_waiting_queue[0].Period_TIME, SCH_waiting_queue[0].Period_TIME);
	}
	uint32_t index_queue = 0;
	while((SCH_waiting_queue[index_queue].TaskFunction != 0) && (index_queue + 1 < MAX_TOTAL_WAIT_QUEUE_TASKS)){
		SCH_waiting_queue[index_queue] = SCH_waiting_queue[index_queue+1];
		index_queue++;
	}
	SCH_waiting_queue[index_queue].Delay_TIME = 0;
	SCH_waiting_queue[index_queue].Period_TIME = 0;
	SCH_waiting_queue[index_queue].TaskFunction = 0x0000;
	SCH_waiting_queue[index_queue].RunMe = 0;
	SCH_waiting_queue[index_queue].sameDelay = 0;
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
