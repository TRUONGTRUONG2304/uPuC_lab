/*
 * timer.c
 *
 *  Created on: Sep 29, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "input_reading.h"
#include "input_processing.h"
#include "led_display.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim){
	if(htim->Instance == TIM2){
		button_reading();
		timer_run();
		timer_run_proc();
	}
}

