/*
 * Name:        randomtestcard3.c
 * Description: Runs the automated tests for processTributeCard.c 
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
    else if (players > 4)
    {
        players = 4;
    }

    int currentPlayer = rand() % players;

    state->numPlayers = players + 1;
    state->whoseTurn = currentPlayer;
    state->coins = 0;
    state->numActions = 0;

    for (int j = 0; j < players; j++)
    {
        state->discardCount[j] = rand() % 200;
        state->deckCount[j] = rand() % 200;
        state->handCount[j] = rand() % 200;
        //printf("Hand Count %d = %d\n", j, state->handCount[j]);

        for (int a = 0; a < state->discardCount[j]; a++)
        {
            state->discard[j][a] = rand() % treasure_map + 1;
        }
        
        for (int b = 0; b < state->deckCount[j]; b++)
        {
            state->deck[j][b] = rand() % treasure_map + 1;
        }
        
        for (int c = 0; c < state->handCount[j]; c++)
        {
            state->hand[j][c] = rand() % treasure_map + 1;
        }
    }

    state->playedCardCount = 0;
    //memset(&state->playedCards[0], 0, MAX_DECK);
}

void checkDiscardCards(struct gameState *state, struct gameState *prevState, int player, int nextPlayer)
{
    if (state->playedCardCount >= 3)
    {
        int firstCompareCard = state->playedCards[state->playedCardCount - 3];
        int secondCompareCard = state->playedCards[state->playedCardCount - 2];

        if (firstCompareCard == secondCompareCard)
        {
            testAssert("No coins added", state->coins, prevState->coins);
            testAssert("No actions added", state->numActions, prevState->numActions);
            testAssert("No cards added", state->handCount[player], prevState->handCount[player] - 1);
        }
        else
        {
            int coins = 0;
            int actions = 0;
            int cards = 0;

            if (firstCompareCard == copper || firstCompareCard == silver || firstCompareCard == gold)
            {
                coins += 2;
            }
            else if (firstCompareCard == estate || firstCompareCard == duchy || firstCompareCard == province)
            {
                cards += 2;
            }
            else if ((firstCompareCard >= adventurer) && (firstCompareCard <= treasure_map))
            {
                actions += 2;
            }
            
            if (secondCompareCard == copper || secondCompareCard == silver || secondCompareCard == gold)
            {
                coins += 2;
            }
            else if (secondCompareCard == estate || secondCompareCard == duchy || secondCompareCard == province)
            {
                cards += 2;
            }
            else if ((secondCompareCard >= adventurer) && (secondCompareCard <= treasure_map))
            {
                actions += 2;
            }

            if (coins)
            {
                testAssert("Coins added", state->coins, prevState->coins + coins);
            }
            if (actions)
            {
                testAssert("Actions added", state->numActions, prevState->numActions + actions);
            }
            if (cards)
            {
                testAssert("Cards added", state->handCount[player], prevState->handCount[player] + cards - 1);
            }
        }
    }
    
}

int main(void)
{
    int result;
    int handPos;
    struct gameState state, prevState;

    srand(time(0));

    printf("*** Tribute Testing ***\n");
    for (int j = 0; j < 20000; j++)
    {
        int player;
        int nextPlayer;
        int numCards;

        memset(&state, 0, sizeof(struct gameState));
        memset(&prevState, 0, sizeof(struct gameState));

        randomizeStructure(&state);
        
        memcpy(&prevState, &state, sizeof(struct gameState));
        
        player = state.whoseTurn;
        nextPlayer = getNextPlayer(player, state.numPlayers);
        numCards = state.handCount[player];

        if (numCards == 0)
        {
            handPos = 0;
        }
        else 
        {
            handPos = rand() % numCards;
            state.hand[player][handPos] = tribute;
        }
   
        result = processTributeCard(handPos, &state);

        if (prevState.deckCount[nextPlayer] >= 2)
        {
            testAssert("Next Player deck - 2 cards", state.deckCount[nextPlayer], 
                        prevState.deckCount[nextPlayer] - 2);
            checkDiscardCards(&state, &prevState, player, nextPlayer);
            testAssert("Successful Result", result, SUCCESS);
        }
        else if ((prevState.deckCount[nextPlayer] + prevState.discardCount[nextPlayer]) >= 2)
        {
            testAssert("Next Player deck and discard - 2 cards", state.deckCount[nextPlayer], 
                        prevState.deckCount[nextPlayer] + prevState.discardCount[nextPlayer] - 2);
            checkDiscardCards(&state, &prevState, player, nextPlayer);
            testAssert("Successful Result", result, SUCCESS);
        }
    }
}