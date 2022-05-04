/*
 * input_processing.c
 *
 *  Created on: Sep 25, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "input_processing.h"

enum ButtonState buttonState = BUTTON_RELEASED;
void fsm_for_input_processing(void){
	switch(buttonState){
	case BUTTON_RELEASED :
		if(get_button_value(0) == GPIO_PIN_RESET){
			buttonState = BUTTON_PRESSED ;
			// INCREASE VALUE OF PORT A BY ONE UNIT
		}
		break;
	case BUTTON_PRESSED :
		if(get_button_value(0) == GPIO_PIN_SET){
			buttonState = BUTTON_RELEASED ;
		}
		else {
			if(get_flag_for_button_press_1s(0) == 1){
				buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND :
		if(get_button_value(0) == GPIO_PIN_SET){
			buttonState = BUTTON_RELEASED;
		}
		break;
	}
}

enum ButtonState getBtnState(){
	return buttonState;
}
