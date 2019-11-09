/*
 * Name:        unittest1.c
 * Description: Tests the processAmbassadorCard Function
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
    printf("* unittest3: Testing processAmbassadorCard function..... *\n");
    printf("**********************************************************\n\n");

    // Test 1, attempting to reveal the card being played, produces an error
    printf("processAmbassadorCard handPos error\n");
    state.hand[0][0] = ambassador;
    result = processAmbassadorCard(0, 0, 0, &state);
    testAssert("Error result", result, ERROR, EQUAL);

    // Test 2, attempting to return fewer cards than are in the hand
    printf("processAmbassadorCard # cards < returnCards\n");
    state.handCount[0] = 5;
    state.hand[0][0] = ambassador;
    state.hand[0][1] = estate;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    result = processAmbassadorCard(1, 2, 0, &state);
    testAssert("Error result", result, ERROR, EQUAL);
    
    // Test 3, supply count error
    printf("processAmbassadorCard supply count less than needed\n");
    state.handCount[0] = 5;
    state.hand[0][0] = ambassador;
    state.hand[0][1] = estate;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    state.supplyCount[estate] = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = processAmbassadorCard(1, 1, 0, &state);
    testAssert("Error result", result, ERROR, EQUAL);
    testAssert("Player 1 discard count increased by 2", state.discardCount[0], checkState.discardCount[0] + 2, EQUAL);
    testAssert("Player 2 discard count increased by 1", state.discardCount[1], checkState.discardCount[1] + 1, EQUAL);

    // Test 4, supply count error
    printf("processAmbassadorCard too many returnCards\n");
    state.handCount[0] = 5;
    state.hand[0][0] = ambassador;
    state.hand[0][1] = estate;
    state.hand[0][2] = estate;
    state.hand[0][3] = estate;
    state.hand[0][4] = copper;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = processAmbassadorCard(1, 3, 0, &state);
    testAssert("Error result", result, ERROR, EQUAL);

    printf("\n");
}