/*
 * deck.h
 *
 *  Created on: Mar 24, 2018
 *      Author: klibby
 */

#ifndef DECK_H_
#define DECK_H_
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
typedef enum state state;
enum state{
	start,
	deal,
	enter_bet,
	match_bet,
	play,
	cpu_hit,
	find_winner,
};
typedef enum face face;
enum face{
	heart,
	club,
	spade,
	diamond
};
static const short HAND_LENGTH=9;
static const short CARD_NULL=99;
static const short DECK_LENGTH=52;
char deck[52];
char player_hand[HAND_LENGTH];
char cpu_hand[HAND_LENGTH];
void shuffle_deck(int cut);
face get_face(int card);
int get_val(int card);

#endif /* DECK_H_ */

