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

void setupGame(struct gameState *state, int currentPlayer, int card1, int card2)
{
    // Build a random game state with 2 players
    // Populate the players hand, discard and deck with random cards
    state->coins = 5;
    int nextPlayer;
    nextPlayer = currentPlayer + 1;
    state->whoseTurn = 0;
    state->numPlayers = 2;
    state->numActions = 1;


    // Set a game state
    state->handCount[currentPlayer] = 5;
    state->deckCount[currentPlayer] = 5;
    state->discardCount[currentPlayer] = 2;
    state->hand[currentPlayer][0] = tribute;
    state->hand[currentPlayer][1] = copper;
    state->hand[currentPlayer][2] = gold;
    state->hand[currentPlayer][3] = estate;
    state->hand[currentPlayer][4] = mine;
    state->deck[nextPlayer][0] = mine;
    state->deck[nextPlayer][1] = copper;
    state->deck[nextPlayer][2] = adventurer;
    state->deck[nextPlayer][3] = estate;
    state->deck[nextPlayer][4] = mine; 
    state->discard[nextPlayer][0] = baron;
    state->discard[nextPlayer][0] = copper;

    state->deckCount[nextPlayer] = 5;
    state->discardCount[nextPlayer] = 2;
    state->deck[nextPlayer][0] = mine;
    state->deck[nextPlayer][1] = copper;
    state->deck[nextPlayer][2] = adventurer;
    state->deck[nextPlayer][3] = card1;    // These should be the two cards that are compared
    state->deck[nextPlayer][4] = card2;      // **
    state->discard[nextPlayer][0] = adventurer;
    state->discard[nextPlayer][0] = feast;

}

void setupTributeCards(struct gameState *state, int tributeRevealedCards[], int nextPlayer, int *preCoin, int *drawCardCounter, int *actionCounter)
{
    tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
    tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 2];

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
            *preCoin = *preCoin + 2;
        }
        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) 
        { //Victory Card Found
            *drawCardCounter = *drawCardCounter + 2;
        }
        else 
        { //Action Card
            *actionCounter = *actionCounter + 2;
        }
    }
}


int main(void)
{
    displayTestInfo();
    srand(time(0));
    
    struct gameState state;
    int currentPlayer = 0;
    int nextPlayer = currentPlayer + 1;
    int handPos = 0;
    setupGame(&state, currentPlayer, estate, mine);
    int tributeRevealedCards[2] = {-1, -1};
    int preCoin = 5;
    int drawCardCounter = state.handCount[currentPlayer];
    int actionCounter = state.numActions;
    int bonus = 0;

    setupTributeCards(&state, tributeRevealedCards, nextPlayer, &preCoin, &drawCardCounter, &actionCounter);

    cardEffect(tribute, 0, 0, 0, &state, handPos, &bonus);

    // Assert that the player received the correct benefits for their tribute card
    testAssert("Assert 7a - Tribute Card Benefit Check - Coins", preCoin, state.coins);
    testAssert("Assert 7b - Tribute Card Benefit Check - Hand Count", drawCardCounter, state.handCount[currentPlayer]);
    testAssert("Assert 7c - Tribute Card Benefit Check - Actions", actionCounter, state.numActions);

    memset(&state, 0, sizeof(struct gameState));
    setupGame(&state, currentPlayer, copper, mine);
    tributeRevealedCards[0] = -1;
    tributeRevealedCards[1] = -1;
    preCoin = 5;
    drawCardCounter = state.handCount[currentPlayer];
    actionCounter = state.numActions;
    bonus = 0;

    setupTributeCards(&state, tributeRevealedCards, nextPlayer, &preCoin, &drawCardCounter, &actionCounter);
    cardEffect(tribute, 0, 0, 0, &state, handPos, &bonus);
    // Assert that the player received the correct benefits for their tribute card
    testAssert("Assert 7d - Tribute Card Benefit Check - Coins", preCoin, state.coins);
    testAssert("Assert 7e - Tribute Card Benefit Check - Hand Count", drawCardCounter, state.handCount[currentPlayer]);
    testAssert("Assert 7f - Tribute Card Benefit Check - Actions", actionCounter, state.numActions);

    printf("\n");
}