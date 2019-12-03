/*
 * Name:        unittest7.c
 * Description: 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "test_helpers.h"
#include <time.h>
#include <stdlib.h>

void displayTestInfo()
{
    printf("***************************************************\n");
    printf("***                 Unit Test 7                 ***\n");
    printf("***************************************************\n\n");
}

void setupGame(struct gameState *state, int currentPlayer)
{
    // Build a random game state with 2 players
    // Populate the players hand, discard and deck with random cards
    int numPlayers = 2;
    state->coins = 5;

    for (int j = 0; j < numPlayers; j++)
    {
        state->handCount[j] = rand() % (10 + 1 - 5) + 5;
        state->discardCount[j] = rand() % (10 + 1 - 5) + 5;
        state->deckCount[j] = rand() % (10 + 1 - 5) + 5;

        for (int c = 0; c < state->handCount[j]; c++)
        {
            state->hand[j][c] = rand() % treasure_map + 1;
        }

        for (int de = 0; de < state->deckCount[j]; de++)
        {
            state->deck[j][de] = rand() % treasure_map + 1;
        }

        for (int di = 0; di < state->discardCount[j]; di++)
        {
            state->discard[j][di] = rand() % treasure_map + 1;
        }
    }
    
    state->hand[currentPlayer][0] = tribute;
}

// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

int main(void)
{
    displayTestInfo();
    srand(time(0));
    
    struct gameState state;
    int currentPlayer = 0;
    int nextPlayer = currentPlayer + 1;
    int handPos = 0;
    setupGame(&state, currentPlayer);
    int tributeRevealedCards[2] = {-1, -1};
    int preCoin = 5;
    int drawCardCounter = state.handCount[currentPlayer];
    int actionCounter = state.numActions;

    tributeRevealedCards[0] = state.deck[nextPlayer][state.deckCount[nextPlayer] - 1];
    tributeRevealedCards[1] = state.deck[nextPlayer][state.deckCount[nextPlayer] - 1];

    // This section taken from dominion source code
    // Manually figure out what the correct action should be
    if (tributeRevealedCards[0] == tributeRevealedCards[1])
    {
        tributeRevealedCards[1] = -1;
    }

    // Manually add up the benefits to the player
    for (int i = 0; i < 2; i ++) 
    {
        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) 
        { //Treasure cards
            preCoin = preCoin + 2;
        }
        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) 
        { //Victory Card Found
            drawCardCounter = drawCardCounter + 2;
        }
        else 
        { //Action Card
            actionCounter = actionCounter + 2;
        }
    }

    cardEffect(tribute, 0, 0, 0, &state, handPos, 0);
    // Assert that the player received the correct benefits for their tribute card
    testAssert("Assert 7a - Tribute Card Benefit Check - Coins", preCoin, state.coins);
    testAssert("Assert 7b - Tribute Card Benefit Check - Hand Count", drawCardCounter, state.handCount[currentPlayer]);
    testAssert("Assert 7c - Tribute Card Benefit Check - Actions", actionCounter, state.numActions);

    printf("\n");
}