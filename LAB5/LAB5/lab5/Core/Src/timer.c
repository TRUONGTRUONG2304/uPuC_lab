/*
 * timer.c
 *
 *  Created on: Nov 27, 2021
 *      Author: PHITRUONG
 */
#include "timer.h"

int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;


void setTimer0 (int duration ){
	timer0_counter = duration / TIMER_CYCLE ;
	timer0_flag = 0;
}
void timer_run (){
	if(timer0_counter > 0){
		timer0_counter--;
		if(timer0_counter == 0) timer0_flag = 1;
	}
}

uint8_t getTimerOut(){
	return timer0_flag;
}

void offTimer(){
	timer0_counter = 0;
	timer0_flag = 0;
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim){
	timer_run();
// YOUR OTHER CODE
}

