/*
 * Name:        unittest1.c
 * Description: Tests the cardEffectAmbassador Function
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "test_helpers.h"

int main(void)
{
    int result;
    // Set up the kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, ambassador, 
                    smithy, village, remodel, great_hall};
    
    // declare the game state
    struct gameState state, checkState;
    initializeGame(2, k, 2, &state);

    printf("**********************************************************\n");
    printf("* unittest3: Testing cardEffectAmbassador function..... *\n");
    printf("**********************************************************\n\n");

    // Test 1, attempting to reveal the card being played, produces an error
    printf("cardEffectAmbassador handPos error\n");
    state.hand[0][0] = ambassador;
    result = cardEffectAmbassador(0, 0, &state, 0, 0);
    testAssert("Error result", result, ERROR);

    // Test 2, attempting to return fewer cards than are in the hand
    printf("cardEffectAmbassador # cards < returnCards\n");
    state.handCount[0] = 5;
    state.hand[0][0] = ambassador;
    state.hand[0][1] = estate;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    result = cardEffectAmbassador(1, 2, &state, 0, 0);
    testAssert("Error result", result, ERROR);
    
    // Test 3, supply count error
    printf("cardEffectAmbassador supply count less than needed\n");
    state.handCount[0] = 5;
    state.hand[0][0] = ambassador;
    state.hand[0][1] = estate;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    state.supplyCount[estate] = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectAmbassador(1, 1, &state, 0, 0);
    testAssert("Error result", result, ERROR);
    testAssert("Player 1 discard count increased by 2", state.discardCount[0], checkState.discardCount[0] + 2);
    testAssert("Player 2 discard count increased by 1", state.discardCount[1], checkState.discardCount[1] + 1);

    // Test 4, supply count error
    printf("cardEffectAmbassador too many returnCards\n");
    state.handCount[0] = 5;
    state.hand[0][0] = ambassador;
    state.hand[0][1] = estate;
    state.hand[0][2] = estate;
    state.hand[0][3] = estate;
    state.hand[0][4] = copper;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectAmbassador(1, 3, &state, 0, 0);
    testAssert("Error result", result, ERROR);

    printf("\n");
}