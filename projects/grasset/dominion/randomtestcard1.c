/*
 * Name:        randomtestcard1.c
 * Description: Runs the automated tests for processBaronCard.c 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "test_helpers.h"

void randomizeStructure(struct gameState *state)
{
    int players = rand() % MAX_PLAYERS + 1;
    if (players < 2)
    {
        players = 2;
    }
    int currentPlayer = rand() % players;
    state->numPlayers = players;
    if (players > 2)
    {
        state->supplyCount[estate] = rand() % 12;
    }
    else 
    {
        state->supplyCount[estate] = rand() % 8;
    }
    state->whoseTurn = currentPlayer;
    state->numBuys = 1;
    state->discardCount[currentPlayer] = rand() % MAX_DECK;
    state->handCount[currentPlayer] = rand() % MAX_HAND;
    for (int i = 0; i < state->handCount[currentPlayer]; i++)
    {
        state->hand[currentPlayer][i] = rand() % treasure_map + 1;
    }
}

int main(void)
{
    int result;
    int handPos;
    struct gameState state, prevState;
    int player;

    srand(time(0));

    printf("*** Baron Testing - Not Discarding Estate Selected ***\n");
    // First test the baron card with discardEstate values of 0
    for (int j = 0; j < 10000; j++)
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
            state.hand[player][handPos] = baron;
        }

        result = processBaronCard(0, handPos, &state);

        if (prevState.supplyCount[estate] == 0)
        {
            testAssert("No cards to gain, expect failure.", result, ERROR);
            testAssert("Hand still the same", state.handCount[player], prevState.handCount[player]);
        }
        else
        {
            testAssert("Cards to gain, test should pass", result, SUCCESS);
            testAssert("Hand is one less", state.handCount[player], prevState.handCount[player] - 1);
            testAssert("Discard Count 1 greater", state.discardCount[player], prevState.discardCount[player] + 1);
        }

        testAssert("Buy ability increase", state.numBuys, prevState.numBuys + 1);
    }
    
    printf("*** Baron Testing - Discarding Estate Selected ***\n");
    // Next test the baron card with discardEstate values of 1
    for (int j = 0; j < 10000; j++)
    {
        int foundEstate = 0;

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
            state.hand[player][handPos] = baron;
        }
        result = processBaronCard(1, handPos, &state);
        
        for(int m = 0; m < prevState.handCount[player]; m++)
        {
            if (prevState.hand[player][m] == estate)
            {
                foundEstate = 1;
                break;
            }
        }

        if (foundEstate)
        {
            testAssert("Increased Coins", state.coins, (prevState.coins + 4));

            testAssert("Hand Count Decreased by 2", 
                    state.handCount[state.whoseTurn], 
                    (prevState.handCount[prevState.whoseTurn] - 2));
        }
        else
        {
            testAssert("Hand Count Decreased", 
                    state.handCount[state.whoseTurn], 
                    (prevState.handCount[prevState.whoseTurn] - 1));

            if (prevState.handCount[prevState.whoseTurn] == 0)
            {
                testAssert("No cards to gain, test will fail.", result, ERROR);    
            }
            else
            {
                testAssert("Cards to gain, test should pass", result, SUCCESS);
            }
        }

        testAssert("Buy ability increase", state.numBuys, prevState.numBuys + 1);
    }
}