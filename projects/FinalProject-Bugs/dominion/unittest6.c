/*
 * Name:        unittest6.c
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
    printf("***                 Unit Test 6                 ***\n");
    printf("***************************************************\n\n");
}

void setupGame(struct gameState *state, int currentPlayer, int card)
{
    // Build a random game state
    // Populate the players hand, discard and deck with random cards
    int j;
    j = currentPlayer;
    state->handCount[j] = 5;
    state->discardCount[j] = 5;
    state->deckCount[j] = 5;
    state->supplyCount[card] = 2;
    state->coins = 4;  // Copper + Gold

    for (int de = 0; de < state->deckCount[j]; de++)
    {
        state->deck[j][de] = rand() % treasure_map + 1;
    }

    for (int di = 0; di < state->discardCount[j]; di++)
    {
        state->discard[j][di] = rand() % treasure_map + 1;
    }

    state->hand[currentPlayer][0] = feast;
    state->hand[currentPlayer][1] = copper;
    state->hand[currentPlayer][2] = gold;
    state->hand[currentPlayer][3] = estate;
    state->hand[currentPlayer][4] = mine;
}


int main(void)
{
    displayTestInfo();
    srand(time(0));

    struct gameState state;
    int currentPlayer = 0;
    int handPos = 0;
    int preCoins = 0;
    int choice1 = 0;
    int retVal = 0;
    int badCardGain = 0;

    // Set choice1 to a baron card costing 4, should fail due to coin gain
    // This first test should fail, no coin change should be permitted
    // Second test should pass, Baron card should be gained.
    // Since updateCoins assigns a temp hand of all -1, it essentially just sets state.coins to 5
    // Third test should succeed
    choice1 = baron;
    setupGame(&state, currentPlayer, baron);
    preCoins = state.coins;
    retVal = cardEffect(feast, choice1, 0, 0, &state, handPos, 0);
    testAssert("Assert 6a - Feast Test Baron - Coins Modified", preCoins, state.coins);
    testAssert("Assert 6b - Feast Test Baron - Baron Card Gain", baron, state.discard[currentPlayer][state.discardCount[currentPlayer] - 1]);
    testAssert("Assert 6c - Feast Test Baron - Correctly Returns 0", retVal, 0);

    // Set choice1 to an adventurer card, costing 6. 
    // This should fail, no coin gain should be permitted
    // Adventurer card should not be gained, second test should succeed.
    // Third test should fail here, but will cause infinite loop so a return value must be added or x=0 to stop the while loop
    choice1 = adventurer;
    setupGame(&state, currentPlayer, adventurer);
    preCoins = state.coins;
    retVal = cardEffect(feast, choice1, 0, 0, &state, handPos, 0);
    if (state.discard[currentPlayer][state.discardCount[currentPlayer] - 1] == adventurer)
    {
        badCardGain = 1;
    }
    testAssert("Assert 6d - Feast Test Adventurer - Coins Modified", preCoins, state.coins);
    testAssert("Assert 6e - Feast Test Adventurer - No Adventurer Card Gain", badCardGain, SUCCESS);
    testAssert("Assert 6f - Feast Test Adventurer - Correctly Returns -1 If Card Too Expensive", retVal, -1);

    printf("\n");
}