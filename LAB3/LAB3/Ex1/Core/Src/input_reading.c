/*
 * input_reading.c
 *
 *  Created on: Sep 25, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "input_reading.h"

#define NO_OF_BUTTONS 2
#define DURATION_FOR_1s 100
#define DURATION_FOR_3s 300
// the buffer that the final result is stored after deboucing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];

static uint16_t counterForButtonPress3s[NO_OF_BUTTONS];
static uint8_t flagForButtonPress3s[NO_OF_BUTTONS];

void button_reading(void){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		if(i == 0)	debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
		if(i == 1)	debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];
		if(buttonBuffer[i] == GPIO_PIN_RESET){
			if(counterForButtonPress1s[i] < DURATION_FOR_1s){
				counterForButtonPress1s[i]++;
			}
			else {
				flagForButtonPress1s[i] = 1;
			}
			if(counterForButtonPress3s[i] < DURATION_FOR_3s){
				counterForButtonPress3s[i]++;
			}
			else {
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

GPIO_PinState get_button_value(uint8_t index){
	if(index >= NO_OF_BUTTONS) return 0xff;
	return buttonBuffer[index];
}

unsigned char get_flag_for_button_press_1s(unsigned char index ){
	if(index >= NO_OF_BUTTONS) return 0xff;
	return flagForButtonPress1s[index];
}
unsigned char get_flag_for_button_press_3s(unsigned char index ){
	if(index >= NO_OF_BUTTONS) return 0xff;
	return flagForButtonPress3s[index];
}
