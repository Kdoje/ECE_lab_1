/*
 * display.c
 *
 *  Created on: Mar 25, 2018
 *      Author: klibby
 */
#include <stdio.h>
#include "IO.h"
#include "deck.h"

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

void diplay_hand(char hand_length, char* p_hand) {
	for (int i = 0; i < hand_length; i++) {
		//makes sure only real cards are printed
		if (p_hand[i] != CARD_NULL) {
			//this will take 0-12 and make it a 0
			switch (p_hand[i] / 13) {
			case heart: {
				printf("H");
				break;
			}
			case club: {
				printf("C");
				break;
			}
			case spade: {
				printf("S");
				break;
			}
			case diamond: {
				printf("D");
				break;
			}
			}
			//prints the suit number with 0-8 being nos.
			if (p_hand[i] % 13 <= 8) {
				printf("-%d ", p_hand[i] % 13 + 2);
			} else if (p_hand[i] % 13 == 9) {
				printf("-J ");
			} else if (p_hand[i] % 13 == 10) {
				printf("-Q ");
			} else if (p_hand[i] % 13 == 11) {
				printf("-K ");
			} else if (p_hand[i] % 13 == 12) {
				printf("-A ");
			}
		}
	}
}

void disp_player_hand(char *p_hand, char hand_length) {
	diplay_hand(hand_length, p_hand);
	printf("\n");
}
void disp_bets(unsigned int player_bet, unsigned int cpu_bet){
	printf("CPU bet: %d\nPlayer bet: %d ", cpu_bet, player_bet);
}
void disp_cpu_hand(char *p_hand, char hand_length){
	//need cast to print first card only
	char start_card=2;
	diplay_hand((char) start_card, p_hand);
	for(int i=(int) start_card; i<hand_length; i++){
		if(p_hand[i]!=CARD_NULL){
			printf("XX-XX ");
		}
	}
	printf("\n");
}
void disp_req_match(){
	printf("Please enter 1 to match, 0 to fold\n");
}
void disp_cpu_matched(char bool_matched){
	if(bool_matched){
		printf("The cpu has matched your bet\n");
	}
	else{
		printf("The cpu has folded\n");
	}
}
void disp_totals(int player_winnings, int cpu_winnings){
	printf("Player has%d$\nCPU has %d$\n",player_winnings, cpu_winnings);
}
