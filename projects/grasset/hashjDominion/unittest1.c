/*
 * Name:        unittest1.c
 * Description: Tests the cardEffectBaron Function
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
    int k[10] = {adventurer, council_room, feast, gardens, mine, baron, 
                    smithy, village, remodel, great_hall};
    
    // declare the game state
    struct gameState state, checkState;
    initializeGame(2, k, 2, &state);

    printf("*****************************************************\n");
    printf("* unittest1: Testing cardEffectBaron function..... *\n");
    printf("*****************************************************\n\n");

    // Test 1, discard estate
    printf("cardEffectBaron Discarding\n");
    state.hand[0][0] = baron;
    state.hand[0][1] = estate;
    state.coins = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectBaron(1, &state, 0);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Handcount is 2 less", state.handCount[0], checkState.handCount[0] - 2);
    testAssert("state.coins did not increase", state.coins, 0); 

    // Test 2, not discarding an estate 
    printf("cardEffectBaron Not Discarding\n");
    state.handCount[0] = 5;
    state.hand[0][0] = baron;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectBaron(0, &state, 0);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Handcount is one less", state.handCount[0], checkState.handCount[0] - 1);
    testAssert("Discard Count increased by 1", state.discardCount[0], checkState.discardCount[0] + 1); 
    testAssert("Played Card Count increased by 1", state.playedCardCount, checkState.playedCardCount + 1); 
    testAssert("Estate was discarded", state.discard[0][state.discardCount[0] - 1], estate); 

    // Test 3, discarding an estate but no estate present
    printf("cardEffectBaron Discarding, No Estate\n");
    state.handCount[0] = 5;
    state.hand[0][0] = baron;
    state.hand[0][1] = copper;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectBaron(1, &state, 0);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Handcount is one less", state.handCount[0], checkState.handCount[0] - 1);
    testAssert("Discard Count increased by 1", state.discardCount[0], checkState.discardCount[0] + 1); 
    testAssert("Estate was discarded", state.discard[0][state.discardCount[0] - 1], estate); 

    // Test 4, not discarding an estate but no available estate 
    printf("cardEffectBaron Not Discarding, No Supply\n");
    state.handCount[0] = 5;
    state.hand[0][0] = baron;
    state.hand[0][1] = copper;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    state.supplyCount[estate] = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectBaron(0, &state, 0);
    testAssert("Error result", result, ERROR);

    // Test 5, discarding an estate, no estate in hand, and no available estate 
    printf("cardEffectBaron Discarding, No Estate, No Supply\n");
    state.handCount[0] = 5;
    state.hand[0][0] = baron;
    state.hand[0][1] = copper;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    state.supplyCount[estate] = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectBaron(1, &state, 0);
    testAssert("Error result", result, ERROR);

    printf("\n");
}