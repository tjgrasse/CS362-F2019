/*
 * Name:        unittest1.c
 * Description: Tests the cardEffectMinion Function
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
    int k[10] = {adventurer, council_room, feast, gardens, mine, minion, 
                    smithy, village, remodel, great_hall};
    
    // declare the game state
    struct gameState state, checkState;
    initializeGame(2, k, 2, &state);

    printf("******************************************************\n");
    printf("* unittest2: Testing cardEffectMinion function..... *\n");
    printf("******************************************************\n\n");

    // Test 1, discard estate
    printf("cardEffectMinion choose coins\n");
    state.hand[0][0] = minion;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectMinion(1, 0, &state, 0, 0);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Handcount is one less", state.handCount[0], checkState.handCount[0] - 1);
    testAssert("state.coins equals zero", state.coins, 0); 

    // Test 2, discarding cards but second player has fewer than 5 cards 
    printf("cardEffectMinion choose cards, small hand\n");
    state.handCount[0] = 5;
    state.hand[0][0] = minion;
    state.hand[0][1] = copper;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    state.handCount[1] = 4;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectMinion(0, 1, &state, 0, 0);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Player 1 handcount is 4", state.handCount[0], 4);
    testAssert("Player 2 handcount is 4", state.handCount[1], 4);
    testAssert("Player 2 card 1 is copper", state.hand[1][0], copper);
    testAssert("Player 2 card 2 is copper", state.hand[1][1], copper);
    testAssert("Player 2 card 3 is copper", state.hand[1][2], copper);
    testAssert("Player 2 card 4 is copper", state.hand[1][3], copper);

    // Test 3, discarding cards as well as second players cards (second player has 5 cards)
    printf("cardEffectMinion choose cards, large hand\n");
    state.handCount[0] = 5;
    state.hand[0][0] = minion;
    state.hand[0][1] = copper;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    state.deckCount[0] = 4;
    state.deck[0][0] = copper;
    state.deck[0][1] = copper;
    state.deck[0][2] = copper;
    state.deck[0][3] = copper;
    state.handCount[1] = 5;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    state.hand[1][4] = copper;
    state.deckCount[1] = 4;
    state.deck[1][0] = copper;
    state.deck[1][1] = copper;
    state.deck[1][2] = copper;
    state.deck[1][3] = copper;

    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectMinion(0, 1, &state, 0, 0);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Player 1 handcount is 4", state.handCount[0], 4);
    testAssert("Player 2 handcount is 4", state.handCount[1], 4);

    // Test 4, discarding cards as well as second players cards (second player has 6 cards)
    printf("cardEffectMinion choose cards, larger hand\n");
    state.handCount[0] = 5;
    state.hand[0][0] = minion;
    state.hand[0][1] = copper;
    state.hand[0][2] = copper;
    state.hand[0][3] = copper;
    state.hand[0][4] = copper;
    state.deckCount[0] = 4;
    state.deck[0][0] = copper;
    state.deck[0][1] = copper;
    state.deck[0][2] = copper;
    state.deck[0][3] = copper;
    state.handCount[1] = 6;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    state.hand[1][4] = copper;
    state.hand[1][5] = copper;
    state.deckCount[1] = 4;
    state.deck[1][0] = copper;
    state.deck[1][1] = copper;
    state.deck[1][2] = copper;
    state.deck[1][3] = copper;

    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectMinion(0, 1, &state, 0, 0);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Player 1 handcount is 4", state.handCount[0], 4);
    testAssert("Player 2 handcount is 4", state.handCount[1], 4);

    printf("\n");
}