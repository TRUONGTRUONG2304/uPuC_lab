/*
 * input_reading.h
 *
 *  Created on: Sep 29, 2021
 *      Author: PHITRUONG
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

void button_reading(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_1s(uint8_t index);
unsigned char is_button_pressed_3s(uint8_t index);

#endif /* INC_INPUT_READING_H_ */
