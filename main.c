/*
 * main.c
 *
 *  Created on: Mar 24, 2018
 *      Author: klibby
 */

#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "IO.h"

state game_state = start;
int main(void) {
	unsigned int player_bet=0;
	unsigned int cpu_bet=0;
	int player_winnings=0;
	int cpu_winnings=0;
	extern char player_hand[9];
	extern char cpu_hand[9];
	unsigned int next_card=0;
	while (1) {
		switch (game_state) {
		case start:{
			disp_opening();
			//replace with input stuff
			if (getchar() == '*') {
				game_state++;
			}
			break;
		}
		case deal:{
			disp_cut_req();
			int cut_val;
			char bool_valid = 0;
			while (!bool_valid) {
				//gets the cut val into a var
				cut_val=get_keypad_input();
				//validate
				if (cut_val!=-1) {
					if (cut_val >= 1 && cut_val <= 15) {
						bool_valid = 1;
						shuffle_deck(cut_val);
						game_state++;
					}
					else{
						disp_invalid_input();
					}
				} else {
					disp_invalid_input();
				}
			}
			//deal the cards
			for(int i=0; i<HAND_LENGTH; i++){
				player_hand[i]=CARD_NULL;
				cpu_hand[i]=CARD_NULL;
			}
			for(int i=0; i<2;i++){
				player_hand[i]=deck[next_card];
				next_card++;
			}
			//this is the starting hand size
			for(int i=0; i<2; i++){
				cpu_hand[i]=deck[next_card];
				next_card++;
			}
			break;
		}
		case enter_bet:{
			char bool_valid_bet=0;
			disp_player_hand(player_hand, HAND_LENGTH);
			disp_cpu_hand(cpu_hand, HAND_LENGTH);
			disp_enter_bet();
			while(!bool_valid_bet){
				//sets the player bet
				player_bet=get_keypad_input();
				//replace this with the bit1 stuff
				if(player_bet==1||player_bet==2||player_bet==4||player_bet==8){
					//printf("%d",player_bet);
					bool_valid_bet=1;
					game_state++;
				}
				else{
					disp_invalid_input();
				}
				char cpu_card_val=0;
				for(int i=0; i<HAND_LENGTH; i++){
					if(cpu_hand[i]!=CARD_NULL){
						cpu_card_val+=get_val(cpu_hand[i]);
					}
				}
				//set up the cpu_bet
				if(cpu_card_val<3){
					cpu_bet=1;
				}
				else if(cpu_card_val<9){
					cpu_bet=2;
				}
				else if(cpu_card_val<16){
					cpu_bet=4;
				}
				else{
					cpu_bet=8;
				}
			}
			disp_bets(player_bet, cpu_bet);
			if(player_bet!=cpu_bet){
				game_state=match_bet;
			}
			else{
				game_state=play;
			}
			break;
		}
		case match_bet:{
			char match_chosen=0;
			if(player_bet<cpu_bet){
				disp_req_match();
				while (!match_chosen) {
					//sets the player bet
					char match = get_keypad_input();
					//replace this with the bit1 stuff
					if (match==1) {
						printf("match confirmed\n");
						match_chosen = 1;
						game_state++;
					}
					else if(match==0){
						printf("match declined\n");
						match_chosen=1;
						cpu_winnings+=player_bet;
						player_winnings-=player_bet;
						disp_totals(player_winnings, cpu_winnings);
						game_state=deal;
					}
				}
			}
			else if (player_bet > cpu_bet) {
				char cpu_card_val = 0;
				for (int i = 0; i < HAND_LENGTH; i++) {
					if (cpu_hand[i] != CARD_NULL) {
						cpu_card_val += get_val(cpu_hand[i]);
					}
				}
				if(cpu_card_val<get_val(player_hand[0])){
					game_state=deal;
					cpu_winnings-=cpu_bet;
					player_winnings+=cpu_bet;
					//the cpu declines
					disp_cpu_matched((char)0);
					disp_totals(player_winnings, cpu_winnings);
				}
				else{
					//the cpu accepts
					disp_cpu_matched((char)1);
					game_state++;
				}
			}
			break;
		}
		case play:{
			//print hit or nah

			break;
		}
		}
	}
	//printf("%d of %d", (int)get_face(deck[0]), get_val(deck[0]));
	return 0;
}

