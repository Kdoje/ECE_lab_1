/*
 * display.c
 *
 *  Created on: Mar 25, 2018
 *      Author: klibby
 */
#include <stdio.h>
#include "IO.h"

//replace this with a text display thing
void disp_opening(){
	printf("hello press * to begin\n");
}
void disp_cut_req(){
	printf("enter a number between 1 and 15\n");
}
void disp_invalid_input(){
	printf("please enter a valid number\n");
}

int get_keypad_input(){
	int return_val;
	if(scanf("%d", &return_val)==1){
		return return_val;
	}
	return -1;
}
void disp_enter_bet(){
	printf("please enter a bet of 1, 2, 4, 8\n");
}


