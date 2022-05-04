/*
 * led_display.h
 *
 *  Created on: Sep 29, 2021
 *      Author: PHITRUONG
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

void displayMode(int mode);
void displayRow7SEG(uint8_t num);
void displayCol7SEG(uint8_t num);
void display12LED(int row, int col);
void setTimerRED(int timer);
void setTimerYELLOW(int timer);
void setTimerGREEN(int timer);
void timer_run();


#endif /* INC_LED_DISPLAY_H_ */
