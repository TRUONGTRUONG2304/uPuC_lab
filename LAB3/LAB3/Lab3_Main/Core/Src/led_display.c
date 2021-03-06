/*
 * led_display.c
 *
 *  Created on: Sep 29, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "input_reading.h"

#define LED_RED_COL  GPIO_PIN_1
#define LED_RED_ROW  GPIO_PIN_4
#define LED_YELLOW_COL  GPIO_PIN_2
#define LED_YELLOW_ROW  GPIO_PIN_5
#define LED_GREEN_COL  GPIO_PIN_3
#define LED_GREEN_ROW  GPIO_PIN_6

int TIMER_CYCLE = 10;
int FREQUENCE_BLINK_LED = 2; //f = 2Hz
static int TIMER_ROW = 9;
static int TIMER_COL = 7;
static int RED_TIMER = 9;
static int YELLOW_TIMER = 2;
static int GREEN_TIMER = 7;
int flag_timer0 = 0;
int timer_counter = 0;
int flagRow = 0, flagCol = 2;
int blink = 0;

enum ModeState{MODE_FIRST, MODE_SECOND, MODE_THIRD, MODE_FOURTH};
enum lightTraffic{RED, YELLOW, GREEN, OFF};
//set timer with f = 2Hz
void setTimer2Hz(){
	int duration = 1000/FREQUENCE_BLINK_LED;
	duration = duration/2;
	timer_counter = duration/TIMER_CYCLE;
	flag_timer0 = 0;
}
void setTimer0(int duration){
	timer_counter = duration/TIMER_CYCLE;
	flag_timer0 = 0;
}
void timer_run(){
	timer_counter--;
	if(timer_counter <= 0){
		flag_timer0 = 1;
	}
}
void display12LED(int row, int col){
	switch(row){
	case RED: // RED
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		break;
	case YELLOW: // YELLOW
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		break;
	case GREEN: // GREEN
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
		break;
	case OFF:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		break;
	}
	switch(col){
	case RED: // RED
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
		break;
	case YELLOW: // YELLOW
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
		break;
	case GREEN: // GREEN
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		break;
	case OFF:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
		break;
	}

}
void blinkRedLED(){
	if(flag_timer0){
		if(!blink) {
			display12LED(RED, RED);
			blink = 1;
		}
		else {
			display12LED(OFF, OFF);
			blink = 0;
		}
		setTimer2Hz();
	}
}
void blinkYellowLED(){
	if(flag_timer0){
		if(!blink) {
			display12LED(YELLOW, YELLOW);
			blink = 1;
		}
		else {
			display12LED(OFF, OFF);
			blink = 0;
		}
		setTimer2Hz();
	}
}
void blinkGreenLED(){
	if(flag_timer0){
		if(!blink) {
			display12LED(GREEN, GREEN);
			blink = 1;
		}
		else {
			display12LED(OFF, OFF);
			blink = 0;
		}
		setTimer2Hz();
	}
}
void displayRow7SEG(uint8_t num){
	uint8_t unit = num%10;
	uint8_t dozen = (num/10)%10;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, ((unit>>0)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, ((unit>>1)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, ((unit>>2)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, ((unit>>3)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, ((dozen>>0)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, ((dozen>>1)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, ((dozen>>2)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, ((dozen>>3)&0x01));
}
void displayCol7SEG(uint8_t num){
	uint8_t unit = num%10;
	uint8_t dozen = (num/10)%10;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, ((unit>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, ((unit>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, ((unit>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, ((unit>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, ((dozen>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, ((dozen>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, ((dozen>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, ((dozen>>3)&0x01));
}
void trafficLight(){
	  if(flag_timer0){
	  display12LED(flagRow, flagCol);
	  switch(flagRow){
		  case RED:
			  TIMER_ROW--;
			  displayRow7SEG(TIMER_ROW);
			  if(TIMER_ROW == 0){
				  flagRow = 2;
				  TIMER_ROW = GREEN_TIMER;
			  }
			  break;
		  case YELLOW:
			  TIMER_ROW--;
			  displayRow7SEG(TIMER_ROW);
			  if(TIMER_ROW == 0){
				  flagRow = 0;
				  TIMER_ROW = RED_TIMER;
			  }
			  break;
		  case GREEN:
			  TIMER_ROW--;
			  displayRow7SEG(TIMER_ROW);
			  if(TIMER_ROW == 0){
				  flagRow = 1;
				  TIMER_ROW = YELLOW_TIMER;
			  }
			  break;
		  }
		  switch(flagCol){
		  case RED:
			  TIMER_COL--;
			  displayCol7SEG(TIMER_COL);
			  if(TIMER_COL == 0){
				  flagCol = 2;
				  TIMER_COL = GREEN_TIMER;
			  }
			  break;
		  case YELLOW:
			  TIMER_COL--;
			  displayCol7SEG(TIMER_COL);
			  if(TIMER_COL == 0){
				  flagCol = 0;
				  TIMER_COL = RED_TIMER;
			  }
			  break;
		  case GREEN:
			  TIMER_COL--;
			  displayCol7SEG(TIMER_COL);
			  if(TIMER_COL == 0){
				  flagCol = 1;
				  TIMER_COL = YELLOW_TIMER;
			  }
			  break;
		  }
		  setTimer0(500);
	  }
}
void checkTimer(){
	if(RED_TIMER < (GREEN_TIMER + YELLOW_TIMER)){
		RED_TIMER = GREEN_TIMER + YELLOW_TIMER;
	}
	else {
		int temp = RED_TIMER - (GREEN_TIMER + YELLOW_TIMER);
		while(temp > 2){
			GREEN_TIMER += 2;
			YELLOW_TIMER += 1;
			temp -= 3;
		}
		if(temp == 1){
			GREEN_TIMER++;
		}
	}
}
void displayMode(int mode){
	switch(mode){
	case MODE_FIRST:
		checkTimer();
		trafficLight();
		break;
	case MODE_SECOND:
		blinkRedLED();
		displayRow7SEG(MODE_SECOND + 1);
		break;
	case MODE_THIRD:
		blinkYellowLED();
		displayRow7SEG(MODE_THIRD + 1);
		break;
	case MODE_FOURTH:
		blinkGreenLED();
		displayRow7SEG(MODE_FOURTH + 1);
		break;
	default:
		break;
	}
}
void resetTraffic(){
	flagRow = 0;
	flagCol = 2;
	TIMER_ROW = RED_TIMER;
	TIMER_COL = GREEN_TIMER;
}
void setTimerRED(int timer){
	RED_TIMER = timer;
	resetTraffic();
}
void setTimerYELLOW(int timer){
	YELLOW_TIMER = timer;
	resetTraffic();
}
void setTimerGREEN(int timer){
	GREEN_TIMER = timer;
	resetTraffic();
}
