/*
 * display.h
 *
 *  Created on: Mar 25, 2018
 *      Author: klibby
 */

#ifndef IO_H_
#define IO_H_
void disp_opening();
void disp_cut_req();
void disp_invalid_input();
int get_keypad_input();
void disp_enter_bet();
void display_hand(char hand_length, char* p_hand);
void disp_bets(unsigned int player_bet, unsigned int cpu_bet);
void disp_req_match();
void disp_cpu_matched(char bool_matched);
void disp_player_hand(char *p_hand, char hand_length);
void disp_cpu_hand(char *p_hand, char hand_length);
#endif /* IO_H_ */
