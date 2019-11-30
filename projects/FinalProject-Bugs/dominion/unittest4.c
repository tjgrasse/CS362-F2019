/*
 * Name:        unittest4.c
 * Description: 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "test_helpers.h"

#define NO_CARD -1

void setupTest(struct gameState *state, int count1, int count2, int count3, int count4)
{
    // Set each supplyCount value to 10
    for (int i = 0; i <= (treasure_map); i++)
    {
        state->supplyCount[i] = 10;
    }
    
    // If there is a card listed for count1, set that to zero
    if (count1 != NO_CARD)
    {
        state->supplyCount[count1] = 0;
    }

    if (count2 != NO_CARD)
    {
        state->supplyCount[count2] = 0;
    }

    if (count3 != NO_CARD)
    {
        state->supplyCount[count3] = 0;
    }

    if (count4 != NO_CARD)
    {
        state->supplyCount[count4] = 0;
    }
}

void displayTestInfo()
{
    printf("***************************************************\n");
    printf("***                 Unit Test 4                 ***\n");
    printf("***************************************************\n\n");
}

int main(void)
{
    int result;
    struct gameState state;

    displayTestInfo();
        
    setupTest(&state, province, NO_CARD, NO_CARD, NO_CARD);
    result = isGameOver(&state);
    testAssert("Assert 1", result, 1);

    setupTest(&state, minion, feast, NO_CARD, NO_CARD);
    result = isGameOver(&state);
    testAssert("Assert 2", result, 0);

    setupTest(&state, gold, NO_CARD, NO_CARD, NO_CARD);
    result = isGameOver(&state);
    testAssert("Assert 3", result, 0);

    setupTest(&state, sea_hag, mine, silver, NO_CARD);
    result = isGameOver(&state);
    testAssert("Assert 4", result, 1);

    setupTest(&state, copper, baron, outpost, NO_CARD);
    result = isGameOver(&state);
    testAssert("Assert 5", result, 1);

    setupTest(&state, sea_hag, remodel, ambassador, treasure_map);
    result = isGameOver(&state);
    testAssert("Assert 6", result, 1);

    setupTest(&state, NO_CARD, NO_CARD, NO_CARD, NO_CARD);
    result = isGameOver(&state);
    testAssert("Assert 7", result, 0);
    
    printf("\n");
}