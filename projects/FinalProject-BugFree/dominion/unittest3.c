/*
 * Name:        unittest3.c
 * Description: 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "test_helpers.h"

void displayTestInfo()
{
    printf("***************************************************\n");
    printf("***                 Unit Test 3                 ***\n");
    printf("***************************************************\n\n");
}

void testSetup(struct gameState *state, int card1)
{
    // Clear out the gameState structure
    memset(state, 0, sizeof(struct gameState));

    // Set all the supplyCount values to 10
    for (int i = 0; i <= treasure_map; i++)
    {
        state->supplyCount[i] = 10;
    }

    state->whoseTurn = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = remodel;
    state->hand[0][1] = card1;
}

int main(void)
{
    int result;
    struct gameState state;

    displayTestInfo();

    // curse cost = 0, estate cost = 2
    testSetup(&state, curse);
    result = cardEffect(remodel, 1, estate, 0, &state, 0, 0);
    testAssert("Assert 1", result, SUCCESS);

    // feast cost = 4, mine cost = 5
    testSetup(&state, feast);
    result = cardEffect(remodel, 1, mine, 0, &state, 0, 0);
    testAssert("Assert 2", result, SUCCESS);

    // copper cost = 0, smithy cost = 4
    testSetup(&state, copper);
    result = cardEffect(remodel, 1, smithy, 0, &state, 0, 0);
    testAssert("Assert 3", result, ERROR);

    // baron cost = 4, outpost cost = 4
    testSetup(&state, baron);
    result = cardEffect(remodel, 1, outpost, 0, &state, 0, 0);
    testAssert("Assert 4", result, SUCCESS);
    
    // silver cost = 3, silver cost = 3
    testSetup(&state, silver);
    result = cardEffect(remodel, 1, silver, 0, &state, 0, 0);
    testAssert("Assert 5", result, SUCCESS);

    // embargo cost = 2, mine cost =5
    testSetup(&state, embargo);
    result = cardEffect(remodel, 1, mine, 0, &state, 0, 0);
    testAssert("Assert 6", result, ERROR);
    
    // smithy cost = 4, copper cost = 0
    testSetup(&state, smithy);
    result = cardEffect(remodel, 1, copper, 0, &state, 0, 0);
    testAssert("Assert 7", result, SUCCESS);

    // tribute cost = 5, steward cost = 3
    testSetup(&state, tribute);
    result = cardEffect(remodel, 1, steward, 0, &state, 0, 0);
    testAssert("Assert 8", result, SUCCESS);

    printf("\n");
}