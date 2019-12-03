/*
 * Name:        unittest1.c
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
    printf("***                 Unit Test 1                 ***\n");
    printf("***************************************************\n\n");
}

void testSetup(struct gameState *state, struct gameState *prevState)
{
    memset(state, 0, sizeof(struct gameState));

    state->whoseTurn = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = mine;
    state->hand[0][1] = copper;
    state->discardCount[0] = 0;
    state->supplyCount[silver] = 10;

    memcpy(prevState, state, sizeof(struct gameState));
}

int main(void)
{
    int result;
    struct gameState state, prevState;

    displayTestInfo();

    testSetup(&state, &prevState);
    result = cardEffect(mine, 1, silver, 0, &state, 0, 0);
    testAssert("Assert 1", result, SUCCESS);
    testAssert("Assert 2", state.discardCount[0], (prevState.discardCount[0] + 1));
    testAssert("Assert 3", state.handCount[0], (prevState.handCount[0] - 1));
    testAssert("Assert 4", state.discard[0][0], mine);
    testAssert("Assert 5", state.hand[0][0], silver);

    printf("\n");
}