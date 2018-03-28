/*
 * main.c
 *
 *  Created on: Mar 24, 2018
 *      Author: klibby
 */

#include <stdio.h>
#include <stdlib.h>
#include <msp430.h>
#include "deck.h"
#include "IO.h"
#include "peripherals.h"


state game_state = start;

int main(void) {
    bool refreshed=false;
	unsigned int player_bet=0;
	unsigned int cpu_bet=0;
	unsigned char cur_key=0;
	int player_winnings=0;
	int cpu_winnings=0;
	extern char player_hand[HAND_LENGTH];
	extern char cpu_hand[HAND_LENGTH];
	unsigned int next_card=0;
    WDTCTL = WDTPW | WDTHOLD;

    initLeds();

    configDisplay();
    configKeypad();
    Graphics_clearDisplay(&g_sContext); // Clear the display

      // Write some text to the display
      Graphics_drawStringCentered(&g_sContext, "Sup boii", AUTO_STRING_LENGTH,
                                  48, 15, TRANSPARENT_TEXT);
      Graphics_drawStringCentered(&g_sContext, "to", AUTO_STRING_LENGTH, 48, 25,
                                  TRANSPARENT_TEXT);
      Graphics_drawStringCentered(&g_sContext, "ECE204-C18!", AUTO_STRING_LENGTH,
                                  48, 35, TRANSPARENT_TEXT);

      // Draw a box around everything because it looks nice
      Graphics_Rectangle box = { .xMin = 5, .xMax = 91, .yMin = 5, .yMax = 91 };
      Graphics_drawRectangle(&g_sContext, &box);
      Graphics_flushBuffer(&g_sContext);
	while (1) {
		switch (game_state) {
		case start:{
		    if(!refreshed){
		        disp_opening();
		        refreshed=true;
		    }
			//replace with input stuff
			if (getKey()== '*') {
			    refreshed=false;
			    Graphics_clearDisplay(&g_sContext);
				game_state++;
				clear_keypad_buffer();//sets up buffer for next stage
			}
			break;
		}
		case deal:{
		    if(!refreshed){
		        disp_cut_req();
		        refreshed=true;
		    }
			int cut_val;
			bool valid = false;
			while (!valid) {
				//gets the cut val into a var
			    cur_key =getKey();
				//converts to int;
				if((cur_key >= '0') && (cur_key <= '9')){
				   store_keypad_input(cur_key);
				   swDelay(1);
				   //TODO fix the integer not printing
				   print_keypad_string_input();

				}
				//validate
                if (cur_key == '*')
                {
                    cut_val = get_keypad_input();
                    if (cut_val >= 0 && cut_val <= 15)
                    {
                        valid = true;
                        shuffle_deck(cut_val);
                        Graphics_clearDisplay(&g_sContext);
                        Graphics_flushBuffer(&g_sContext);
                    }
                    else
                    {
                        disp_invalid_input();
                        Graphics_flushBuffer(&g_sContext);
                    }
                    clear_keypad_buffer();
                    Graphics_drawStringCentered(&g_sContext, "     ",
                                                AUTO_STRING_LENGTH, 48, 45,
                                                OPAQUE_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                }
			}
			//deal the cards
			int i;
			for(i=0; i<HAND_LENGTH; i++){
				player_hand[i]=CARD_NULL;
				cpu_hand[i]=CARD_NULL;
			}
			for(i=0; i<2;i++){
				player_hand[i]=deck[next_card];
				next_card++;
			}
			//this is the starting hand size
			for(i=0; i<2; i++){
				cpu_hand[i]=deck[next_card];
				next_card++;
			}
			game_state++;
			break;
		}
		case enter_bet:{
            char bool_valid_bet = 0;
            disp_player_hand(player_hand, HAND_LENGTH);
            disp_cpu_hand(cpu_hand, HAND_LENGTH);
            disp_enter_bet();
            while (!bool_valid_bet)
            {
                //sets the player bet

                cur_key = getKey();
                //converts to int;
                if ((cur_key >= '0') && (cur_key <= '9'))
                {
                    player_bet = cur_key - 0x30;
                    //replace this with the bit1 stuff
                    if (player_bet == 1 || player_bet == 2 || player_bet == 4
                            || player_bet == 8)
                    {
                        //printf("%d",player_bet);
                        clear_invalid_input();
                        bool_valid_bet = 1;
                    }
                    else
                    {
                        disp_invalid_input();
                    }
                }
            }
            char cpu_card_val = 0;
            int i;
            for (i = 0; i < HAND_LENGTH; i++)
            {
                if (cpu_hand[i] != CARD_NULL)
                {
                    cpu_card_val += get_val(cpu_hand[i]);
                }
            }
            //set up the cpu_bet
            if (cpu_card_val < 3)
            {
                cpu_bet = 1;
            }
            else if (cpu_card_val < 9)
            {
                cpu_bet = 2;
            }
            else if (cpu_card_val < 16)
            {
                cpu_bet = 4;
            }
            else
            {
                cpu_bet = 8;
            }
            disp_bets(player_bet, cpu_bet);
            if (player_bet != cpu_bet)
            {
                game_state = match_bet;
            }
            else
            {
                game_state = play;
            }
            break;
        }
		case match_bet:{
			char match_chosen=0;
			if(player_bet<cpu_bet){
				disp_req_match();
				while (!match_chosen) {
					//sets the player bet
					unsigned char cur_key;
                    //replace this with the bit1 stuff
                    cur_key = getKey();
                    //converts to int;
                    if ((cur_key == '#'))
                    {
						//printf("match confirmed\n");
						match_chosen = 1;
						game_state++;
					}
					else if(cur_key=='*'){
						//printf("match declined\n");
						match_chosen=1;
						cpu_winnings+=player_bet;
						player_winnings-=player_bet;
	                    disp_results(1); //1 because cpu won
						game_state=deal;
					}
				}
			}
			else if (player_bet > cpu_bet) {
				char cpu_card_val = 0;
				int i;
				for (i = 0; i < HAND_LENGTH; i++) {
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
					disp_results(0);
				}
				else{
					//the cpu accepts
					disp_cpu_matched((char)1);
					game_state++;
				}
			}
			break;
		}
        case play:
        {
            disp_hit_req();
            bool still_hitting = true;
            while (still_hitting)
            {
                //sets the player bet
                unsigned char cur_key;
                //replace this with the bit1 stuff
                cur_key = getKey();
                //converts to int;
                if ((cur_key == '#'))
                {
                    //test add
                    player_hand[2]=32;
                    disp_player_hand(player_hand, HAND_LENGTH);
                    //printf("match confirmed\n");
                }
                else if (cur_key == '*')
                {
                    //printf("match declined\n");
                    still_hitting = false;
                    game_state = cpu_hit;
                }
            }
            break;
        }
		case cpu_hit:{
		    cpu_hand[2]=50;
		    disp_cpu_hand(cpu_hand, HAND_LENGTH);
		    break;
		}
		}
	}
	//printf("%d of %d", (int)get_face(deck[0]), get_val(deck[0]));
	return 0;
}

