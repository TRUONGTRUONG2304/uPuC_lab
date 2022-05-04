/*
 * input_reading.c
 *
 *  Created on: Sep 29, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "input_reading.h"
// we aim to work with more than one buttons
#define NO_OF_BUTTONS 3
// timer interrupt duration is 10ms , so to pass 1 second,
// we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_1s 100
#define DURATION_FOR_3s 300
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET
#define FIRST_BUTTON GPIO_PIN_0
#define SECOND_BUTTON GPIO_PIN_1
#define THIRD_BUTTON GPIO_PIN_2

// the buffer that the final result is stored after debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
//we define two buffers for debouncing

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];

static uint16_t counterForButtonPress3s[NO_OF_BUTTONS];
static uint8_t flagForButtonPress3s[NO_OF_BUTTONS];

void button_reading(void){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		switch(i){
		case 0:
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, FIRST_BUTTON);
			break;
		case 1:
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, SECOND_BUTTON);
			break;
		case 2:
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, THIRD_BUTTON);
			break;
		}
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
				buttonBuffer[i] = debounceButtonBuffer1[i];
				if(buttonBuffer[i] == BUTTON_IS_PRESSED){
					if(counterForButtonPress1s[1] < DURATION_FOR_1s){
						counterForButtonPress1s[i]++;
					}
					else{
						flagForButtonPress1s[i] = 1;
					}
					if(counterForButtonPress3s[1] < DURATION_FOR_3s){
						counterForButtonPress1s[i]++;
					}
					else{
						flagForButtonPress3s[i] = 1;
					}
				}
				else{
					counterForButtonPress1s[i] = 0;
					flagForButtonPress1s[i] = 0;
					counterForButtonPress3s[i] = 0;
					flagForButtonPress3s[i] = 0;
				}
		}
	}
}

unsigned char is_button_pressed(uint8_t index){
	if(index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED)?1:0;
}
unsigned char is_button_pressed_1s(uint8_t index){
	if(index >= NO_OF_BUTTONS) return 0;
	return flagForButtonPress1s[index];;
}
unsigned char is_button_pressed_3s(uint8_t index){
	if(index >= NO_OF_BUTTONS) return 0;
	return flagForButtonPress3s[index];
}
