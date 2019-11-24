/*
 * Name:        randomtestcard2.c
 * Description: Runs the automated tests for processMinionCard.c 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"

void randomizeStructure(struct gameState *state)
{
    int players = rand() % MAX_PLAYERS + 1;
    if (players < 2)
    {
        players = 2;
    }
    else if (players > 4)
    {
        players = 4;
    }
    int currentPlayer = rand() % players;
    state->numPlayers = players;
    state->whoseTurn = currentPlayer;
    state->coins = rand() % 5000;   // setting coins to a potentially high value
    state->discardCount[currentPlayer] = rand() % 200;
    for (int j = 0; j < players; j++)
    {
        state->handCount[j] = rand() % 200;
        state->deckCount[j] = rand() % 200;
        for (int i = 0; i < state->handCount[j]; i++)
        {
            state->hand[j][i] = rand() % treasure_map + 1;
        }
        for (int h = 0; h < state->deckCount[j]; h++)
        {
            state->deck[j][h] = rand() % treasure_map + 1;
        }
    }
    state->playedCardCount = 0;
    memset(&state->playedCards[0], 0, MAX_DECK);
}

int main(void)
{
    int result;
    int handPos;
    int player;
    int chooseCoins = 1;
    int chooseCards = 0;
    struct gameState state, prevState;

    srand(time(0));

    printf("*** Minion Testing - Choose Coins Selected ***\n");
    // first run for 1000 iterations with chooseCoins being selected
    for (int i = 0; i < 10000; i++)
    {
        memset(&state, 0, sizeof(struct gameState));
        memset(&prevState, 0, sizeof(struct gameState));

        randomizeStructure(&state);

        memcpy(&prevState, &state, sizeof(struct gameState));
        player = state.whoseTurn;

        int numCards = state.handCount[player];
        if (numCards == 0)
        {
            handPos = 0;
        }
        else 
        {
            handPos = rand() % numCards;
            state.hand[player][handPos] = minion;
        }

        result = cardEffectMinion(chooseCoins, chooseCards, &state, handPos, 0);

        testAssert("NumActions incremented", state.numActions, prevState.numActions + 1);
        testAssert("Coins increased by 2", state.coins, prevState.coins + 2);
        testAssert("Hand is decreased", state.handCount[player], 
                    (prevState.handCount[player] - 1));
        testAssert("Successful result", result, SUCCESS);
    }

    chooseCoins = 0;
    chooseCards = 1;

    printf("*** Minion Testing - Choose Cards Selected ***\n");
    // next run for 1000 iterations with choseCards being selected
    for (int k = 0; k < 10000; k++)
    {
        memset(&state, 0, sizeof(struct gameState));
        memset(&prevState, 0, sizeof(struct gameState));

        randomizeStructure(&state);

        memcpy(&prevState, &state, sizeof(state));
        player = state.whoseTurn;

        result = cardEffectMinion(chooseCoins, chooseCards, &state, 0, 0);

        testAssert("NumActions incremented", state.numActions, prevState.numActions + 1);
        testAssert("Proper hand count", state.handCount[player], 4);
        testAssert("4 cards drawn", state.deckCount[player], prevState.deckCount[player] - 4);
        
        for (int n = 0; n < state.numPlayers; n++)
        {
            if (n != player)
            {
                if (prevState.handCount[n] >= 5)
                {
                    testAssert("Other Player Hand Count", state.handCount[n], 4);
                }
                else 
                {
                    testAssert("Other Player Hand Count", state.handCount[n], prevState.handCount[n]);
                }
            }
        }
    }
}
