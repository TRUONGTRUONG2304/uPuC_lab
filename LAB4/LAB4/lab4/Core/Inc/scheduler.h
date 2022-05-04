/*
 * scheduler.h
 *
 *  Created on: Oct 15, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#define TIMER_INTERRUPT 10
#define MAX_TOTAL_TASKS 5
#define MAX_TOTAL_WAIT_QUEUE_TASKS 100
typedef struct{
//	Pointer to task
	void (*TaskFunction)(void);
//	Delay (ticks) until the function will be run
	uint32_t Delay_TIME;
//	Interval (ticks) between subsequent runs
	uint32_t Period_TIME;
//	Incremented when task is due to execute
	uint8_t RunMe;
//	Identify of task
	uint8_t sameDelay;

} Tasks;

void SCH_Init();
void Timer_Init();
void Watchdog_Init();
void SCH_Update();
void SCH_Dispatch_Tasks();
uint32_t SCH_Add_Task(void (*pfunction)(void), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);
// Report system status
void SCH_Report_Status();
// The scheduler enters idle mode at this point
void SCH_Go_To_Sleep();
#endif /* INC_SCHEDULER_H_ */
