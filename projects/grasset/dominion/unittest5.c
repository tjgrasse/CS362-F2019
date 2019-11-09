/*
 * Name:        unittest1.c
 * Description: Tests the processMineCard Function
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

    printf("**********************************************************\n");
    printf("* unittest5: Testing processMineCard function.....       *\n");
    printf("**********************************************************\n\n");

    // Test 1, trashCard not a treasure
    printf("processMineCard trashcard not treasure\n");
    state.hand[0][0] = mine;
    result = processMineCard(0, ambassador, copper, &state);
    testAssert("Error result", result, ERROR, EQUAL);

    // Test 2, treasureCard not a treasure
    printf("processMineCard treasureCard not treasure\n");
    state.hand[0][0] = mine;
    result = processMineCard(0, copper, adventurer, &state);
    testAssert("Error result", result, ERROR, EQUAL);

    // Test 3, treasureCard too large
    printf("processMineCard treasureCard too large\n");
    state.hand[0][0] = mine;
    result = processMineCard(0, copper, gold, &state);
    testAssert("Error result", result, ERROR, EQUAL);

    // Test 4, copper to silver
    printf("processMineCard copper to silver\n");
    state.discardCount[0] = 0;
    state.handCount[0] = 5;
    state.hand[0][0] = mine;
    state.hand[0][1] = copper;
    state.hand[0][2] = estate;
    state.hand[0][3] = estate;
    state.hand[0][4] = estate;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = processMineCard(0, copper, silver, &state);
    testAssert("Successful response", result, SUCCESS, EQUAL);
    testAssert("Hand count is one less", state.handCount[0], checkState.handCount[0] - 1, EQUAL);
    testAssert("Card 4 is a silver", state.hand[0][0], silver, EQUAL);

    // Test 5, same card
    printf("processMineCard same card\n");
    state.discardCount[0] = 0;
    state.handCount[0] = 5;
    state.hand[0][0] = mine;
    state.hand[0][1] = silver;
    state.hand[0][2] = estate;
    state.hand[0][3] = estate;
    state.hand[0][4] = estate;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = processMineCard(0, silver, silver, &state);
    testAssert("Successful response", result, SUCCESS, EQUAL);
    testAssert("Hand count is one less", state.handCount[0], checkState.handCount[0] - 1, EQUAL);
    testAssert("Card 4 is a silver", state.hand[0][0], silver, EQUAL);

    // Test 4, copper to silver no cards
    printf("processMineCard copper to silver no cards\n");
    state.discardCount[0] = 0;
    state.handCount[0] = 5;
    state.hand[0][0] = mine;
    state.hand[0][1] = copper;
    state.hand[0][2] = estate;
    state.hand[0][3] = estate;
    state.hand[0][4] = estate;
    state.supplyCount[silver] = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = processMineCard(0, copper, silver, &state);
    testAssert("Error response", result, ERROR, EQUAL);

    printf("\n");
}