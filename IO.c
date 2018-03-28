/*
 * display.c
 *
 *  Created on: Mar 25, 2018
 *      Author: klibby and cwagner
 */
#include <stdio.h>
#include "IO.h"
#include "deck.h"
#include "peripheral.h"


void wait_for_response(currKey)
{
    while(1)
    {
        currKey = getKey();
        if (currKey == '*')
        {
            break;
        }
    }
}

void swDelay(char numLoops)
{
    volatile unsigned int i,j;


    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;
        while (i > 0)
           i--;
    }
}

void welcome_screen(void)
{
    Graphics_clearDisplay(&g_sContext);

    Graphics_drawStringCentered(&g_sContext, "MSP430 Blackjack", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "Press * to start", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);

    Graphics_flushBuffer(&g_sContext);
}

//replace this with a text display thing
void disp_opening(){
	Graphics_clearDisplay(&g_sContext);

	Graphics_drawStringCentered(&g_sContext, "MSP430 Blackjack", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, "Press * to start", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);

	Graphics_flushBuffer(&g_sContext);
}
void disp_cut_req(){
	Graphics_drawStringCentered(&g_sContext, "Enter 0-15 to cut", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
	Graphics_flushBuffer(&g_sContext);
}
void disp_invalid_input(){
	Graphics_drawStringCentered(&g_sContext, "Please enter a valid number", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
	Graphics_flushBuffer(&g_sContext);
	swDelay(1);
	Graphics_drawStringCentered(&g_sContext, "                           ", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT); //clear display
	Graphics_flushBuffer(&g_sContext);
}

int get_keypad_input(){
	return getKey();
}
void disp_enter_bet(){
	Graphics_drawStringCentered(&g_sContext, "Please enter a bet of 1, 2, 4, 8", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
	Graphics_flushBuffer(&g_sContext);
}

void diplay_hand(char hand_length, char* p_hand) {
	char card[2];
	for (int i = 0; i < hand_length; i++) {
		//makes sure only real cards are printed
		if (p_hand[i] != CARD_NULL) {
			//this will take 0-12 and make it a 0
			switch (p_hand[i] / 13) {
			case heart: {
				card[0] = "H";
				break;
			}
			case club: {
				card[0] = "C";
				break;
			}
			case spade: {
				card[0] = "S";
				break;
			}
			case diamond: {
				card[0] = "D";
				break;
			}
			}
			//prints the suit number with 0-8 being nos.
			if (p_hand[i] % 13 <= 8) {
				card[1] = p_hand[i] % 13 + 2);
			} else if (p_hand[i] % 13 == 9) {
				card[1] = "J";
			} else if (p_hand[i] % 13 == 10) {
				card[1] = "Q";
			} else if (p_hand[i] % 13 == 11) {
				card[1] = "K";
			} else if (p_hand[i] % 13 == 12) {
				card[1] = "A";
			}
		}
	}
	Graphics_drawStringCentered(&g_sContext, card[0], 4, 20, 25, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, card[1], 4, 50, 25, TRANSPARENT_TEXT);
	Graphics_flushBuffer(&g_sContext);
}

void disp_player_hand(char *p_hand, char hand_length) {
	diplay_hand(hand_length, p_hand);
}
void disp_bets(unsigned int player_bet, unsigned int cpu_bet){
	Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

	setLeds(player_bet - 0x30);
	Graphics_drawStringCentered(&g_sContext, player_bet, 1, 75, 85, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, cpu_bet, 1, 55, 75, TRANSPARENT_TEXT);

}
void disp_cpu_hand(char *p_hand, char hand_length){
	//need cast to print first card only
	char start_card=2;
	diplay_hand((char) start_card, p_hand);
	for(int i=(int) start_card; i<hand_length; i++){
		if(p_hand[i]!=CARD_NULL){
			Graphics_drawStringCentered(&g_sContext, "XXX", 4, 20, 55, TRANSPARENT_TEXT);
			Graphics_flushBuffer(&g_sContext);
		}
	}
}
void disp_req_match(){
	Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);
	Graphics_flushBuffer(&g_sContext);
}

void disp_cpu_matched(char bool_matched){
	if(bool_matched){
		Graphics_drawStringCentered(&g_sContext, "The cpu has matched your bet", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
		Graphics_flushBuffer(&g_sContext);
	}
	else{
		Graphics_drawStringCentered(&g_sContext, "The cpu has folded", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
		Graphics_flushBuffer(&g_sContext);
	}
}

void disp_totals(int player_winnings, int cpu_winnings){
	Graphics_clearDisplay(&g_sContext);
	Graphics_drawStringCentered(&g_sContext, player_winnings, 1, 40, 45, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, "WININNGS: ", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
	Graphics_drawStringCentered(&g_sContext, "WIN!", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
	Graphics_flushBuffer(&g_sContext);
}

void disp_results(unsigned char bool_cpuWinner){
	Graphics_clearDisplay(&g_sContext);
	if(bool_cpuWinner){
		Graphics_drawStringCentered(&g_sContext, "LOSE", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);

	}
	else{
		Graphics_drawStringCentered(&g_sContext, "WIN!", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
	}
	Graphics_flushBuffer(&g_sContext);

}
