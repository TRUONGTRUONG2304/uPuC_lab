/*
 * input_processing.h
 *
 *  Created on: Sep 26, 2021
 *      Author: PHITRUONG
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_
enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};

void fsm_for_input_processing(void);
enum ButtonState getBtnState();

#endif /* INC_INPUT_PROCESSING_H_ */
