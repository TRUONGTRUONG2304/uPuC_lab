/*
 * led_display.c
 *
 *  Created on: Sep 25, 2021
 *      Author: PHITRUONG
 */
#include "led_display.h"
#include "main.h"

void increaseDisplayLed(int index){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
	switch(index){
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
		break;
	default:
		break;
	}
}
void resetLED(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
}
