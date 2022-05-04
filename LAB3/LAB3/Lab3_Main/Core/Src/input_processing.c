/*
 * input_processing.c
 *
 *  Created on: Sep 29, 2021
 *      Author: PHITRUONG
 */
#include "main.h"
#include "input_reading.h"
#include "led_display.h"

enum BUTTON{BUTTON_FIRST, BUTTON_SECOND, BUTTON_THIRD};
enum ModeState{MODE_FIRST, MODE_SECOND, MODE_THIRD, MODE_FOURTH};
enum ModeState mode = MODE_FIRST;
int realse = 0;
int RED = 0, YELLOW = 0, GREEN = 0;
int timer = 0, flag = 1;
int TIMER_CYCLE_1 = 10;

void setTimer(int duration){
	timer = duration/TIMER_CYCLE_1;
	flag = 0;
}
void timer_run_proc(){
	timer--;
	if(timer <= 0){
		flag = 1;
	}
}

void fsm_for_input_processing(void){
	switch(mode){
	case MODE_FIRST:
		if(!is_button_pressed(BUTTON_FIRST) && !is_button_pressed(BUTTON_SECOND) && !is_button_pressed(BUTTON_THIRD)){
			realse = 1;
		}
		if(is_button_pressed(BUTTON_FIRST)){
			if(realse == 1) {
				mode = MODE_SECOND;
				//set gia tri thoi gian RED thuc te vao RED tam thoi
				RED = 0;
				//hien thi thoi gian RED len tren 7seg
				displayCol7SEG(RED);
				realse = 0;
			}
		}
		break;
	case MODE_SECOND:
		if(!is_button_pressed(BUTTON_FIRST) && !is_button_pressed(BUTTON_SECOND) && !is_button_pressed(BUTTON_THIRD)){
			realse = 1;
		}
		//Chuyen trang thai mode neu button 1 duoc nhan
		if(is_button_pressed(BUTTON_FIRST)){
			if(realse == 1){
			//chuyen trang thai sang mode 3
				mode = MODE_THIRD;
			//set gia tri thoi gian YELLOW thuc te vao YELLOW tam thoi
				YELLOW = 0;
		    //hien thi thoi gian YELLOW len tren 7seg
				displayCol7SEG(YELLOW);
				realse = 0;
			}
		}
		//neu button 2 duoc nhan
		if(is_button_pressed(BUTTON_SECOND)){
			if(realse == 1){
			    //tang thoi gian RED tam thoi len 1
			    //hien thi thoi gian RED tam thoi tren 7 SEG
				displayCol7SEG(++RED);
				realse = 0;
			}
		}
		//neu button 3 duoc nhan
		if(is_button_pressed(BUTTON_THIRD)){
			if(realse == 1){
			//set thoi gian RED tam thoi cho thoi gian RED thuc te
				setTimerRED(RED);
				realse = 0;
			}
		}
		//Neu button 2 duoc nhan hon 1s thi tang gia tri RED 1 don vi moi 0.5s
		if(is_button_pressed_1s(BUTTON_SECOND)){
			if(flag == 1){
				displayCol7SEG(++RED);
				setTimer(500);
			}
		}
		//Neu button 2 duoc nhan hon 3s thi tang gia tri RED 1 don vi moi 0.2s
		if(is_button_pressed_3s(BUTTON_SECOND)){
			if(flag == 1){
				displayCol7SEG(++RED);
				setTimer(50);
			}
		}
		break;
	case MODE_THIRD:
		if(!is_button_pressed(BUTTON_FIRST) && !is_button_pressed(BUTTON_SECOND) && !is_button_pressed(BUTTON_THIRD)){
			realse = 1;
		}
		//Chuyen trang thai mode neu button 1 duoc nhan
		if(is_button_pressed(BUTTON_FIRST)){
			if(realse == 1){
			//chuyen trang thai sang mode 4
				mode = MODE_FOURTH;
			//set gia tri thoi gian GREEN thuc te vao GREEN tam thoi
				GREEN = 0;
		    //hien thi thoi gian GREEN len tren 7seg
				displayCol7SEG(GREEN);
				realse = 0;
			}
		}
		//neu button 2 duoc nhan
		if(is_button_pressed(BUTTON_SECOND)){
			if(realse == 1){
			    //tang thoi gian YELLOW tam thoi len 1
			    //hien thi thoi gian YELLOW tam thoi tren 7 SEG
				displayCol7SEG(++YELLOW);
				realse = 0;
			}
		}
		//neu button 3 duoc nhan
		if(is_button_pressed(BUTTON_THIRD)){
			if(realse == 1){
			//set thoi gian YELLOW tam thoi cho thoi gian YELLOW thuc te
				setTimerYELLOW(YELLOW);
				realse = 0;
			}
		}
		//Neu button 2 duoc nhan hon 1s thi tang gia tri YELLOW 1 don vi moi 0.5s
		if(is_button_pressed_1s(BUTTON_SECOND)){
			if(flag == 1){
				displayCol7SEG(++YELLOW);
				setTimer(500);
			}
		}
		//Neu button 2 duoc nhan hon 3s thi tang gia tri RED 1 don vi moi 0.2s
		if(is_button_pressed_3s(BUTTON_SECOND)){
			if(flag == 1){
				displayCol7SEG(++YELLOW);
				setTimer(50);
			}
		}
		break;
	case MODE_FOURTH:
		if(!is_button_pressed(BUTTON_FIRST) && !is_button_pressed(BUTTON_SECOND) && !is_button_pressed(BUTTON_THIRD)){
			realse = 1;
		}
		//Chuyen trang thai mode neu button 1 duoc nhan
		if(is_button_pressed(BUTTON_FIRST)){
			if(realse == 1){
			//chuyen trang thai sang mode 1
				mode = MODE_FIRST;
				realse = 0;
			}
		}
		//neu button 2 duoc nhan
		if(is_button_pressed(BUTTON_SECOND)){
			if(realse == 1){
			    //tang thoi gian GREEN tam thoi len 1
			    //hien thi thoi gian GREEN tam thoi tren 7 SEG
				displayCol7SEG(++GREEN);
				realse = 0;
			}
		}
		//neu button 3 duoc nhan
		if(is_button_pressed(BUTTON_THIRD)){
			if(realse == 1){
			//set thoi gian GREEN tam thoi cho thoi gian GREEN thuc te
				setTimerGREEN(GREEN);
				realse = 0;
			}
		}
		//Neu button 2 duoc nhan hon 1s thi tang gia tri GREEN 1 don vi moi 0.5s
		if(is_button_pressed_1s(BUTTON_SECOND)){
			if(flag == 1){
				displayCol7SEG(++GREEN);
				setTimer(500);
			}
		}
		//Neu button 2 duoc nhan hon 3s thi tang gia tri GREEN 1 don vi moi 0.2s
		if(is_button_pressed_3s(BUTTON_SECOND)){
			if(flag == 1){
				displayCol7SEG(++GREEN);
				setTimer(50);
			}
		}
		break;
	default:
		break;
	}
}
int getMode(){
	return mode;
}
