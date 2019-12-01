/*
 * Name:        unittest2.c
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
    printf("***                 Unit Test 2                 ***\n");
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

    // compare copper to silver
    testSetup(&state, copper);
    result = cardEffect(mine, 1, silver, 0, &state, 0, 0);
    testAssert("Assert 1", result, SUCCESS);

    // compare copper to gold, will fail
    testSetup(&state, copper);
    result = cardEffect(mine, 1, gold, 0, &state, 0, 0);
    testAssert("Assert 2", result, ERROR);

    // compare copper to copper
    testSetup(&state, copper);
    result = cardEffect(mine, 1, copper, 0, &state, 0, 0);
    testAssert("Assert 3", result, SUCCESS);

    // compare silver to silver
    testSetup(&state, silver);
    result = cardEffect(mine, 1, silver, 0, &state, 0, 0);
    testAssert("Assert 4", result, SUCCESS);

    // compare silver to gold
    testSetup(&state, silver);
    result = cardEffect(mine, 1, gold, 0, &state, 0, 0);
    testAssert("Assert 5", result, SUCCESS);

    // compare silver to copper
    testSetup(&state, silver);
    result = cardEffect(mine, 1, copper, 0, &state, 0, 0);
    testAssert("Assert 6", result, SUCCESS);

    // compare gold to copper
    testSetup(&state, gold);
    result = cardEffect(mine, 1, copper, 0, &state, 0, 0);
    testAssert("Assert 7", result, SUCCESS);

    // compare gold to silver
    testSetup(&state, gold);
    result = cardEffect(mine, 1, silver, 0, &state, 0, 0);
    testAssert("Assert 8", result, SUCCESS);

    // compare gold to gold
    testSetup(&state, gold);
    result = cardEffect(mine, 1, gold, 0, &state, 0, 0);
    testAssert("Assert 9", result, SUCCESS);

    printf("\n");
}
