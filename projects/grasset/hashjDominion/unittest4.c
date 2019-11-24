/*
 * Name:        unittest1.c
 * Description: Tests the cardEffectTribute Function
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
    int k[10] = {adventurer, council_room, feast, gardens, mine, tribute, 
                    smithy, village, remodel, great_hall};
    int tributeRevealedCards[2] = {-1, -1};
    
    // declare the game state
    struct gameState state, checkState;
    initializeGame(2, k, 2, &state);

    printf("**********************************************************\n");
    printf("* unittest1: Testing cardEffectTribute function.....    *\n");
    printf("**********************************************************\n\n");

    // Test 1, deck has two cards, they are the same as the hand that is intentional
    printf("cardEffectTribute deck has 2 same cards\n");
    state.hand[0][0] = tribute;
    state.handCount[1] = 5;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    state.hand[1][4] = copper;
    state.deckCount[1] = 2;
    state.deck[1][0] = copper;
    state.deck[1][1] = copper;
    state.coins = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectTribute(&state, 0, 0, 1, tributeRevealedCards);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Hand counts equal", state.handCount[1], checkState.handCount[1]);
    testAssert("Deck count 2 less", state.deckCount[1], checkState.deckCount[1] - 2);
    testAssert("state.coins is zero", state.coins, 0);
    testAssert("NumActions is the same", state.numActions, checkState.numActions);
    testAssert("Hand count is one less", state.handCount[0], checkState.handCount[0] - 1);

    // Test 2, deck has two cards, one treasure one action card
    printf("cardEffectTribute deck has 1 treasure 1 action card\n");
    state.hand[0][0] = tribute;
    state.handCount[1] = 5;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    state.hand[1][4] = copper;
    state.deckCount[1] = 1;
    state.deck[1][0] = adventurer;
    state.discardCount[1] = 1;
    state.discard[1][0] = copper;
    state.coins = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectTribute(&state, 0, 0, 1, tributeRevealedCards);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Hand counts are equal", state.handCount[1], checkState.handCount[1]);
    testAssert("Deck count is one less", state.deckCount[1], checkState.deckCount[1] - 1);
    testAssert("Discard count is one less", state.discardCount[1], checkState.discardCount[1] - 1);
    testAssert("state.coins is zero", state.coins, 0);
    testAssert("NumActions increased by 2", state.numActions, checkState.numActions + 2);
    testAssert("Hand count less by 1", state.handCount[0], checkState.handCount[0] - 1);

    // Test 3, deck has two cards, one action and one victory card
    printf("cardEffectTribute deck has 1 action 1 victory card\n");
    state.hand[0][0] = tribute;
    state.handCount[1] = 5;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    state.hand[1][4] = copper;
    state.deckCount[1] = 0;
    state.discardCount[1] = 2;
    state.discard[1][0] = adventurer;
    state.discard[1][1] = estate;
    state.coins = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectTribute(&state, 0, 0, 1, tributeRevealedCards);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Hand counts are equal", state.handCount[1], checkState.handCount[1]);
    testAssert("Discard count less by 2", state.discardCount[1], checkState.discardCount[1] - 2);
    testAssert("state.coins is zero", state.coins, 0);
    testAssert("NumActions is increased by 2", state.numActions, checkState.numActions + 2);
    testAssert("Hand count increased by 1", state.handCount[0], checkState.handCount[0] + 1);

    // Test 4, discard has two cards, one victory and one action card
    printf("cardEffectTribute deck has 1 action 1 victory card\n");
    state.hand[0][0] = tribute;
    state.handCount[1] = 5;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    state.hand[1][4] = copper;
    state.deckCount[1] = 0;
    state.discardCount[1] = 2;
    state.discard[1][0] = estate;
    state.discard[1][1] = adventurer;
    state.coins = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectTribute(&state, 0, 0, 1, tributeRevealedCards);
    testAssert("Successful result", result, SUCCESS);
    testAssert("Hand Counts are equal", state.handCount[1], checkState.handCount[1]);
    testAssert("Discard count increased by 2", state.discardCount[1], checkState.discardCount[1] - 2);
    testAssert("state.coins equals zero", state.coins, 0);
    testAssert("NumActions increased by 2", state.numActions, checkState.numActions + 2);
    testAssert("Hand count increased by 1", state.handCount[0], checkState.handCount[0] + 1);

    // Test 5, not enough deck or discard cards
    printf("cardEffectTribute no deck or discard cards\n");
    state.hand[0][0] = tribute;
    state.handCount[1] = 5;
    state.hand[1][0] = copper;
    state.hand[1][1] = copper;
    state.hand[1][2] = copper;
    state.hand[1][3] = copper;
    state.hand[1][4] = copper;
    state.deckCount[1] = 0;
    state.discardCount[1] = 0;
    state.coins = 0;
    memcpy(&checkState, &state, sizeof(struct gameState));
    result = cardEffectTribute(&state, 0, 0, 1, tributeRevealedCards);
    testAssert("Error result", result, ERROR);

    printf("\n");
}