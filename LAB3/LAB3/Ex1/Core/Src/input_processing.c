/*
 * input_processing.c
 *
 *  Created on: Sep 25, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "input_processing.h"

enum ButtonState buttonFirstState = BUTTON_RELEASED;
enum ButtonState buttonSecondState = BUTTON_RELEASED;
void fsm_for_input_processing(void){
	switch(buttonFirstState){
	case BUTTON_RELEASED:
		if(get_button_value(0) == GPIO_PIN_RESET){
			buttonFirstState = BUTTON_PRESSED ;
			// INCREASE VALUE OF PORT A BY ONE UNIT
		}
		break;
	case BUTTON_PRESSED:
		if(get_button_value(0) == GPIO_PIN_SET){
			buttonFirstState = BUTTON_RELEASED ;
		}
		else {
			if(get_flag_for_button_press_1s(0) == 1){
				buttonFirstState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if(get_button_value(0) == GPIO_PIN_SET){
			buttonFirstState = BUTTON_RELEASED;
		}
		else {
			if(get_flag_for_button_press_3s(0) == 1){
				buttonFirstState = BUTTON_PRESSED_MORE_THAN_3_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_3_SECOND:
		if(get_button_value(0) == GPIO_PIN_SET){
			buttonFirstState = BUTTON_RELEASED;
		}
		break;
	default:
		break;
	}
	switch(buttonSecondState){
	case BUTTON_RELEASED:
		if(get_button_value(1) == GPIO_PIN_RESET){
			buttonSecondState = BUTTON_PRESSED ;
			// INCREASE VALUE OF PORT A BY ONE UNIT
		}
		break;
	case BUTTON_PRESSED:
		if(get_button_value(1) == GPIO_PIN_SET){
			buttonSecondState = BUTTON_RELEASED ;
		}
		else {
			if(get_flag_for_button_press_1s(1) == 1){
				buttonSecondState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if(get_button_value(1) == GPIO_PIN_SET){
			buttonSecondState = BUTTON_RELEASED;
		}
		else {
			if(get_flag_for_button_press_3s(1) == 1){
				buttonSecondState = BUTTON_PRESSED_MORE_THAN_3_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_3_SECOND:
		if(get_button_value(1) == GPIO_PIN_SET){
			buttonSecondState = BUTTON_RELEASED;
		}
		break;
	default:
		break;
	}
}

enum ButtonState getBtnFirstState(){
	return buttonFirstState;
}
enum ButtonState getBtnSecondState(){
	return buttonSecondState;
}
