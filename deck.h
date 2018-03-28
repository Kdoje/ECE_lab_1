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
};
typedef enum face face;
enum face{
	heart,
	club,
	spade,
	diamond
};
static const short HAND_LENGTH;
static const short CARD_NULL;
static const short DECK_LENGTH;
char deck[52];
char player_hand[9];
char cpu_hand[9];
void shuffle_deck(int cut);
face get_face(int card);
int get_val(int card);

#endif /* DECK_H_ */

