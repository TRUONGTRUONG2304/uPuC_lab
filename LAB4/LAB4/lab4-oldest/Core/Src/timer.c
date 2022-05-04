/*
 * timer.c
 *
 *  Created on: Oct 18, 2021
 *      Author: PHITRUONG
 */
#include "scheduler.h"
#include "timer.h"
#include "main.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){

		SCH_Update();

	}
}
