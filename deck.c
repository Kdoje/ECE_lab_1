/*
 * deck.c
 *
 *  Created on: Mar 24, 2018
 *      Author: klibby
 */

#include "deck.h"
extern const short HAND_LENGTH;
extern const short CARD_NULL;
extern const short DECK_LENGTH;
void shuffle_deck(int cut) {
	const int DECK_LENGTH = 52;
	extern char deck[52];
	srand(time(0) + cut);
	int i;
	for (i = 0; i < DECK_LENGTH; i++) {
		deck[i] = i;
		//printf("%3d ", deck[i]);
		if ((i+1) % 13 == 0) {
			//printf("\n");
		}
	}
//	printf("\n");
	for (i = 0; i < DECK_LENGTH; i++) {
		int toSwitch = rand() % DECK_LENGTH;
		int temp = deck[i];
		deck[i] = deck[toSwitch];
		deck[toSwitch] = temp;
	}
	//printf("\n");
	for (i = 0; i < DECK_LENGTH; i++) {
		//printf("%3d ", deck[i]);
		if ((i+1) % 13 == 0) {
			//printf("\n");
		}
	}
}
face get_face(int card){
	return card/13;
}

int get_val(int card){
    if (card % 13 <= 8)
    {
        return (card % 13 + 2);
    }
    else if (card % 13 <= 11)
    {
        return 10;
    }
    else{
        return 11;
    }
}
