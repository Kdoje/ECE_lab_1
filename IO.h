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
void clear_keypad_buffer(); //this sets the buffer to 0
void store_keypad_input(char input);//input is the char form eg '1' not 1
int get_keypad_input(); //this returns the string as an int
void print_keypad_string_input();
unsigned char *get_keypad_string_input();
void disp_enter_bet();
void display_hand(char hand_length, char* p_hand, int pos);
void disp_bets(unsigned int player_bet, unsigned int cpu_bet);
void disp_req_match();
void disp_cpu_matched(char bool_matched);
void disp_totals(int player_winnings, int cpu_winnings);
void disp_player_hand(char *p_hand, char hand_length);
void disp_cpu_hand(char *p_hand, char hand_length);
static const unsigned char buffer_length;
#endif /* IO_H_ */
