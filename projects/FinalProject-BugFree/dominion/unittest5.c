/*
 * Name:        unittest5.c
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
    printf("***                 Unit Test 5                 ***\n");
    printf("***************************************************\n\n");
}

void setupGame(struct gameState *state, int currentPlayer)
{
    // Build a random game state
    // Populate the players hand, discard and deck with random cards
    int j;
    j = currentPlayer;
    state->handCount[j] = rand() % 11;
    state->discardCount[j] = rand() % 11;
    state->deckCount[j] = rand() % 100;

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

int calculatedScore(struct gameState *state, int player)
{
    // Taken from dominion source code
    int i;
    int score = 0;
    //score from hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == curse) {
            score = score - 1;
        };
        if (state->hand[player][i] == estate) {
            score = score + 1;
        };
        if (state->hand[player][i] == duchy) {
            score = score + 3;
        };
        if (state->hand[player][i] == province) {
            score = score + 6;
        };
        if (state->hand[player][i] == great_hall) {
            score = score + 1;
        };
        if (state->hand[player][i] == gardens) {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    //score from discard
    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == curse) {
            score = score - 1;
        };
        if (state->discard[player][i] == estate) {
            score = score + 1;
        };
        if (state->discard[player][i] == duchy) {
            score = score + 3;
        };
        if (state->discard[player][i] == province) {
            score = score + 6;
        };
        if (state->discard[player][i] == great_hall) {
            score = score + 1;
        };
        if (state->discard[player][i] == gardens) {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    //score from deck
    for (i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == curse) {
            score = score - 1;
        };
        if (state->deck[player][i] == estate) {
            score = score + 1;
        };
        if (state->deck[player][i] == duchy) {
            score = score + 3;
        };
        if (state->deck[player][i] == province) {
            score = score + 6;
        };
        if (state->deck[player][i] == great_hall) {
            score = score + 1;
        };
        if (state->deck[player][i] == gardens) {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    return score;
}


int main(void)
{
    displayTestInfo();
    srand(time(0));
    
    struct gameState state;
    int currentPlayer = 0;
    int scoreForScore = 0;
    int calculateScore = 0;

    // Give the player random cards, add them up and check to see if the score matches scoreFor
    setupGame(&state, currentPlayer);
    calculateScore = calculatedScore(&state, currentPlayer);
    scoreForScore = scoreFor(currentPlayer, &state);
    testAssert("Assert 5a", calculateScore, scoreForScore);
    memset(&state, 0, sizeof(struct gameState));

    setupGame(&state, currentPlayer);
    calculateScore = calculatedScore(&state, currentPlayer);
    scoreForScore = scoreFor(currentPlayer, &state);
    testAssert("Assert 5b", calculateScore, scoreForScore);
    memset(&state, 0, sizeof(struct gameState));

    setupGame(&state, currentPlayer);
    calculateScore = calculatedScore(&state, currentPlayer);
    scoreForScore = scoreFor(currentPlayer, &state);
    testAssert("Assert 5c", calculateScore, scoreForScore);
    memset(&state, 0, sizeof(struct gameState));

    printf("\n");
}