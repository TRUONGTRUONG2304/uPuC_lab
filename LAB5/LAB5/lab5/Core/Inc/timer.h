/*
 * timer.h
 *
 *  Created on: Nov 27, 2021
 *      Author: PHITRUONG
 */
#include "main.h"

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void setTimer0 (int duration);
void timer_run ();
uint8_t getTimerOut();
void offTimer();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim);


#endif /* INC_TIMER_H_ */
