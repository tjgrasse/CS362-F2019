/*
 * Name:        unittest10.c
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
    printf("***                 Unit Test 10                ***\n");
    printf("***************************************************\n\n");
}

void testSetup(struct gameState *game, int testCard)
{
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    //int nextPlayer = 1;

    int k[10] = {adventurer, council_room, ambassador, gardens, mine,
                 remodel, smithy, village, baron, great_hall
                };

    // initialize a new gameState structure
    initializeGame(numPlayers, k, seed, game);

    game->numActions = 0;
    game->coins = 0;

    // create a known, sample hand with three identical cards to test if more than 2 can be discarded
    game->handCount[0] = 7;
    game->hand[currentPlayer][0] = estate;
    game->hand[currentPlayer][1] = testCard;
    game->hand[currentPlayer][2] = testCard;
    game->hand[currentPlayer][3] = testCard;
    game->hand[currentPlayer][4] = ambassador;
    game->hand[currentPlayer][5] = estate;
    game->hand[currentPlayer][6] = mine;


}

void printHand(struct gameState *before, struct gameState *after, int currentPlayer, int testCard) {

    // iterate over the hand and compare the before and after
    for (int i = 0; i < before->handCount[0]; i++){
        printf("     Card %d Before: %d     Card %d After: %d\n", i, before->hand[currentPlayer][i], i, after->hand[currentPlayer][i]); 
    }
}

void testResult(struct gameState *before, struct gameState *after, int currentPlayer, int testCard, int testFlag) {

    int ambassadorFlag = 0;
    int testCardsFlag = 0;

    // discard 0 copies of test card
    if (testFlag == 0) {
        for (int i = 0; i < after->handCount[0]; i++){
            if (after->hand[currentPlayer][i] == ambassador) {
                ambassadorFlag++;
            }

        }
        if (ambassadorFlag > 0) {
            printf("FAILED\n");
        }
        else {
            printf("PASSED\n");
        }
    }

    // discard 1 copy of test card
    if (testFlag == 1) {
        for (int i = 0; i < after->handCount[0]; i++){
            if (after->hand[currentPlayer][i] == testCard) {
                testCardsFlag++;
            }

        }
        if (testCardsFlag == 2) {
            printf("PASSED\n");
        }
        else {
            printf("FAILED\n");
        }
    }

    // discard 2 copy of test card
    if (testFlag == 2) {
    for (int i = 0; i < after->handCount[0]; i++){
            if (after->hand[currentPlayer][i] == testCard) {
                testCardsFlag++;
            }

        }
        if (testCardsFlag == 1) {
            printf("PASSED\n");
        }
        else {
            printf("FAILED\n");
        }
    }

}

int main(void)
{   
    // header text for the test
    displayTestInfo();
    // new game state and test setup
    struct gameState game;
    struct gameState testGame;
    int coinBonus = 0;
    int testCard = smithy;
 
    // setup game and create a duplicate, test game state
    printf("Discard 0 copies of %d. Expect -1 Ambassador.\n", testCard);
    testSetup(&game, testCard); // start off with smithy duplicates
    memcpy(&testGame, &game, sizeof(struct gameState));
    cardEffect(ambassador, 2, 0, 0, &testGame, 4, &coinBonus); // get rid of 0 smithy copy
    printHand(&game, &testGame, 0, testCard);
    testResult(&game, &testGame, 0, testCard, 0);

    // setup game and create a duplicate, test game state
    printf("Discard 1 copy of %d. Expect -1 Ambassador, -1 Card %d.\n", testCard, testCard);
    testSetup(&game, testCard); // start off with smithy duplicates
    memcpy(&testGame, &game, sizeof(struct gameState));
    cardEffect(ambassador, 2, 1, 0, &testGame, 4, &coinBonus); // get rid of 0 smithy copy
    printHand(&game, &testGame, 0, testCard);
    testResult(&game, &testGame, 0, testCard, 1);

    // setup game and create a duplicate, test game state
    printf("Discard 2 copies of %d. Expect -1 Ambassador, -2 Card %d.\n", testCard, testCard);
    testSetup(&game, testCard); // start off with smithy duplicates
    memcpy(&testGame, &game, sizeof(struct gameState));
    cardEffect(ambassador, 2, 2, 0, &testGame, 4, &coinBonus); // get rid of 0 smithy copy
    printHand(&game, &testGame, 0, testCard);
    testResult(&game, &testGame, 0, testCard, 2);

    printf("\n");
}