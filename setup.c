#include <msp430.h>
#include <stdlib.h>
#include "peripherals.h"


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

void shuffle(int cutValue, int cards[])
{
    srand(cutValue);

    int i;
    for(i=0;i<52;i++)
    {
        cards[i] = i+1;
    }

    for(i=0;i<52;i++)
    {
        int random = rand() % 52;

        int temp = cards[i];
        cards[i] = cards[random];
        cards[random] = temp;
    }
}

void getCard(int cards[], int currentCard, unsigned char playerHand[][4], int i)
{
    if((cards[currentCard] % 13) == 11)
    {
        playerHand[i][0] = 'J';
    }
    else if((cards[currentCard] % 13) == 12)
    {
        playerHand[i][0] = 'Q';
    }
    else if((cards[currentCard] % 13) == 0)
    {
        playerHand[i][0] = 'K';
    }
    else if((cards[currentCard] % 13) == 1)
    {
        playerHand[i][0] = 'A';
    }
    else if((cards[currentCard] % 13) == 10)
    {
        playerHand[i][0] = '1';
        playerHand[i][1] = '0';
        playerHand[i][2] = '-';
    }
    else
    {
        playerHand[i][0] = '0'+(cards[currentCard] % 13);
    }

    if((cards[currentCard] % 13) == 10)
    {
        if(cards[currentCard] <= 13)
        {
            playerHand[i][3] = 'S';
        }
        else if((cards[currentCard] > 13) && (cards[currentCard] <= 26))
        {
            playerHand[i][3] = 'C';
        }
        else if((cards[currentCard] > 26) && (cards[currentCard] <= 39))
        {
            playerHand[i][3] = 'H';
        }
        else
        {
            playerHand[i][3] = 'D';
        }
    }
    else if(cards[currentCard] <= 13)
    {
        playerHand[i][2] = 'S';
    }
    else if((cards[currentCard] > 13) && (cards[currentCard] <= 26))
    {
        playerHand[i][2] = 'C';
    }
    else if((cards[currentCard] > 26) && (cards[currentCard] <= 39))
    {
        playerHand[i][2] = 'H';
    }
    else
    {
        playerHand[i][2] = 'D';
    }
}

void dealCard(int cards[], int currentCard, unsigned char playerHand[][4], int i)
{

    getCard(cards, currentCard, playerHand, i);

    if(i == 2)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[2], 4, 80, 25, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
    else if(i == 3)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[3], 4, 20, 35, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
    else if(i == 4)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[4], 4, 50, 35, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
    else if(i == 5)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[5], 4, 80, 35, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
}

void dealCardCPU(int cards[], int currentCard, unsigned char playerHand[][4], int i)
{

    getCard(cards, currentCard, playerHand, i);

    if(i == 2)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[2], 4, 80, 55, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
    else if(i == 3)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[3], 4, 20, 65, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
    else if(i == 4)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[4], 4, 50, 65, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
    else if(i == 5)
    {
        Graphics_drawStringCentered(&g_sContext, playerHand[5], 4, 80, 65, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }
}

void deal(int cards[], int currentCard, unsigned char playerHand[][4], unsigned char cpuHand[][4])
{
    int i;
    for(i=0;i<10;i++)
    {
        playerHand[i][0] = '0';
        cpuHand[i][0] = '0';
    }

    for(i=0;i<10;i++)
    {
    playerHand[i][1] = '-';
    cpuHand[i][1] = '-';
    }

    for(i=0;i<10;i++)
    {
        playerHand[i][3] = 0x00;
        cpuHand[i][3] = 0x00;
    }

    for(i=0; i<2; i++)
    {
        getCard(cards, currentCard, playerHand, i);
        currentCard++;
    }

    for(i=0; i<2; i++)
    {
        getCard(cards, currentCard, cpuHand, i);
        currentCard++;
    }

    Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

    Graphics_drawStringCentered(&g_sContext, "XXX", 4, 20, 55, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
}

void player_bet(unsigned char betValue[])
{
    while(1)
    {
        betValue[0] = getKey();
        if (( betValue[0] == '8')|( betValue[0] == '4')|(betValue[0] == '2')|(betValue[0] == '1'))
        {
            break;
        }
    }

    setLeds(betValue[0] - 0x30);
    Graphics_drawStringCentered(&g_sContext, betValue, 1, 75, 85, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
}

void cpu_bet(unsigned char cpuBetValue[], unsigned char cpuHand[][4])
{
    if((getHandValueLow(cpuHand) < 10)|(getHandValueHigh(cpuHand) < 15))
    {
        cpuBetValue[0] = '1';
    }
    else if(((getHandValueLow(cpuHand) < 17)&&(getHandValueLow(cpuHand) > 14))|((getHandValueHigh(cpuHand) < 17)&&(getHandValueHigh(cpuHand) > 14)))
    {
        cpuBetValue[0] = '2';
    }
    else if(getHandValueHigh(cpuHand) > 19)
    {
        cpuBetValue[0] = '8';
    }
    else
    {
        cpuBetValue[0] = '4';
    }

    Graphics_drawStringCentered(&g_sContext, cpuBetValue, 1, 55, 75, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
}

int getHandValueLow(unsigned char hand[][4])
{
    int value = 0;
    int i;
    for(i=0;i<10;i++)
    {
        if(hand[i][0] == '0')
        {
            break;
        }
        else if((hand[i][0] == 'K')|(hand[i][0] == 'Q')|(hand[i][0] == 'J')|((hand[i][0] == '1')&&(hand[i][1] == '0')))
        {
            value += 10;
        }
        else if(hand[i][0] == 'A')
        {
            value += 1;
        }
        else
        {
            value += (hand[i][0] - 48);
        }
    }
    return value;
}

int getHandValueHigh(unsigned char hand[][4])
{
    int value = 0;
    int i;
    for(i=0;i<10;i++)
    {
        if(hand[i][0] == '0')
        {
            break;
        }
        else if((hand[i][0] == 'K')|(hand[i][0] == 'Q')|(hand[i][0] == 'J')|((hand[i][0] == '1')&&(hand[i][1] == '0')))
        {
            value += 10;
        }
        else if(hand[i][0] == 'A')
        {
            value += 11;
        }
        else
        {
            value += (hand[i][0] - 48);
        }
    }
    return value;
}

int main(void) {

    int currentCard = 0;
    int k;
    int j;
    int cards[52];
    unsigned char betValue[1];
    unsigned char cpuBetValue[1];
    int state = 0;
    unsigned char currKey=0;
    unsigned char cutValueDisplay[2];
    int cutValue = 0;
    unsigned char playerHand[10][4];
    unsigned char cpuHand[10][4];

    WDTCTL = WDTPW | WDTHOLD;

    initLeds();

    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext);

    while(1)
    {
        switch(state)
        {
            case 0:
                welcome_screen();

                wait_for_response(currKey);

                Graphics_clearDisplay(&g_sContext);
                Graphics_flushBuffer(&g_sContext);
                state = 1;

                break;

            case 1:
                Graphics_drawStringCentered(&g_sContext, "Enter 0-15 to cut", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);

                while(1)
                {
                    currKey = getKey();
                    if((currKey == '0') | (currKey == '1'))
                    {
                        cutValueDisplay[0] = currKey;
                        break;
                    }
                }

                swDelay(1);

                while(1)
                {
                    currKey = getKey();
                    if((currKey >= '0') && (currKey <= '9'))
                    {
                        cutValueDisplay[1] = currKey;
                        break;
                    }
                }

                Graphics_drawStringCentered(&g_sContext, cutValueDisplay, 2, 41, 55, OPAQUE_TEXT);
                Graphics_flushBuffer(&g_sContext);

                cutValue = (cutValueDisplay[0] * 10) + cutValueDisplay[1];

                setLeds(cutValue - 0x30);

                wait_for_response(currKey);
                setLeds(0);

                shuffle(cutValue, cards);
                state = 2;
                Graphics_clearDisplay(&g_sContext);
                break;

            case 2:
                deal(cards, currentCard, playerHand, cpuHand);
                currentCard += 4;

                Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);

                player_bet(betValue);

                cpu_bet(cpuBetValue, cpuHand);

                Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);

                if(cpuBetValue[0]>betValue[0])
                {
                    while(1)
                    {
                        currKey = getKey();
                        if(currKey == '0')
                        {
                            Graphics_clearDisplay(&g_sContext);
                            Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, "XXX", 4, 20, 55, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, cpuBetValue, 1, 55, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, cpuBetValue, 1, 75, 85, TRANSPARENT_TEXT);
                            Graphics_flushBuffer(&g_sContext);
                            state = 3;
                            break;
                        }
                        else if(currKey == '*')
                        {
                            state = 0;
                            break;
                        }
                    }
                }
                else
                {
                    state = 3;
                }

                break;
            case 3:

                j=2;
                while(1)
                {
                    currKey = getKey();
                    if(currKey == '#')
                    {
                        if(cpuBetValue[0]<betValue[0])
                        {
                            cpuBetValue[0] = betValue[0];

                            Graphics_clearDisplay(&g_sContext);
                            Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, "XXX", 4, 20, 55, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, betValue, 1, 55, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, betValue, 1, 75, 85, TRANSPARENT_TEXT);
                            Graphics_flushBuffer(&g_sContext);
                        }

                        dealCard(cards, currentCard, playerHand, j);
                        currentCard++;
                        j++;
                    }
                    else if(currKey == '*')
                    {
                        state = 0;
                        break;
                    }
                    else if(currKey == '0')
                    {
                        if(cpuBetValue[0]<betValue[0])
                        {
                            cpuBetValue[0] = betValue[0];

                            Graphics_clearDisplay(&g_sContext);
                            Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, "XXX", 4, 20, 55, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, betValue, 1, 55, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, betValue, 1, 75, 85, TRANSPARENT_TEXT);
                            Graphics_flushBuffer(&g_sContext);
                        }
                        break;
                    }

                    if((getHandValueHigh(playerHand)>21)&&(getHandValueLow(playerHand)>21))
                    {
                        swDelay(3);
                        state = 4;
                        break;
                    }

                }
                if(state == 3)
                {
                    k=2;
                    while(1)
                    {
                        if((getHandValueLow(cpuHand)<17)&&(getHandValueHigh(cpuHand)<17))
                        {
                            dealCardCPU(cards, currentCard, cpuHand, k);
                            swDelay(3);
                            currentCard++;
                            k++;
                        }
                        else if((getHandValueLow(cpuHand)<17)&&(getHandValueHigh(cpuHand)>21))
                        {
                            dealCardCPU(cards, currentCard, cpuHand, k);
                            swDelay(3);
                            currentCard++;
                            k++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if((getHandValueLow(cpuHand)>21)&&(getHandValueHigh(cpuHand)>21))
                    {
                        Graphics_clearDisplay(&g_sContext);
                        Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, cpuHand[0], 4, 20, 55, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, betValue, 1, 55, 75, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, betValue, 1, 75, 85, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);

                        swDelay(3);
                        state = 5;
                        break;
                    }

                    if((getHandValueHigh(cpuHand)<21) && ((getHandValueHigh(cpuHand)>=getHandValueHigh(playerHand))&&(getHandValueHigh(cpuHand)>=getHandValueLow(playerHand))))
                    {
                            Graphics_clearDisplay(&g_sContext);
                            Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, cpuHand[0], 4, 20, 55, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);

                            Graphics_drawStringCentered(&g_sContext, betValue, 1, 55, 75, TRANSPARENT_TEXT);
                            Graphics_drawStringCentered(&g_sContext, betValue, 1, 75, 85, TRANSPARENT_TEXT);
                            Graphics_flushBuffer(&g_sContext);

                            swDelay(3);
                            state = 4;
                            break;
                    }
                    else if((getHandValueLow(cpuHand)>=getHandValueHigh(playerHand))&&(getHandValueLow(cpuHand)>=getHandValueLow(playerHand)))
                    {
                        Graphics_clearDisplay(&g_sContext);
                        Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, cpuHand[0], 4, 20, 55, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, betValue, 1, 55, 75, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, betValue, 1, 75, 85, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);

                        swDelay(3);
                        state = 4;
                        break;
                    }
                    else
                    {
                        Graphics_clearDisplay(&g_sContext);
                        Graphics_drawStringCentered(&g_sContext, "CPU BET:", AUTO_STRING_LENGTH, 25, 75, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, "PLAYER BET:", AUTO_STRING_LENGTH, 35, 85, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "FOLD* CALL0 HIT#", AUTO_STRING_LENGTH, 50, 5, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "Player 1:", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, playerHand[0], 4, 20, 25, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, playerHand[1], 4, 50, 25, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, "CPU:", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, cpuHand[0], 4, 20, 55, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, cpuHand[1], 4, 50, 55, TRANSPARENT_TEXT);

                        Graphics_drawStringCentered(&g_sContext, betValue, 1, 55, 75, TRANSPARENT_TEXT);
                        Graphics_drawStringCentered(&g_sContext, betValue, 1, 75, 85, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);

                        swDelay(3);
                        state = 5;
                    }
                }


                break;

            case 4: //lose
                setLeds(8);
                Buzz(4);

                swDelay(1);
                setLeds(4);
                Buzz(3);

                swDelay(1);
                setLeds(2);
                Buzz(2);

                swDelay(1);
                setLeds(0);
                Buzz(1);

                swDelay(1);
                BuzzerOff();
                setLeds(0);

                Graphics_clearDisplay(&g_sContext);

                Graphics_drawStringCentered(&g_sContext, "LOSE", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);

                wait_for_response(currKey);
                state = 0;
                break;

            case 5: //win

                setLeds(0);
                Buzz(1);

                swDelay(1);
                setLeds(2);
                Buzz(2);

                swDelay(1);
                setLeds(4);
                Buzz(3);

                swDelay(1);
                setLeds(8);
                Buzz(4);

                swDelay(1);
                BuzzerOff();
                setLeds(0);

                Graphics_clearDisplay(&g_sContext);

                Graphics_drawStringCentered(&g_sContext, betValue, 1, 40, 45, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "WININNGS: ", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "WIN", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);

                wait_for_response(currKey);
                state = 0;

                break;
        }
    }
    return 0;
}
