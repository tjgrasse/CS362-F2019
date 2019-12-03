/*
 * Name:        unittest9.c
 * Description: Unit test to check that bonuses based on tribute cards
 * are properly disbursed.
 * We test the case when the next player reveals two duplicate cards.
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
    printf("***                 Unit Test 9                 ***\n");
    printf("***************************************************\n\n");
}

void testSetup(struct gameState *game, int testCard)
{
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall
                };

    // initialize a new gameState structure
    initializeGame(numPlayers, k, seed, game);

    game->handCount[currentPlayer] = 2;
    game->hand[currentPlayer][0] = baron;
    game->hand[currentPlayer][1] = estate;

    game->numActions = 0;
    game->coins = 0;

    game->discardCount[nextPlayer]= 3;
    game->discard[nextPlayer][0] = testCard;
    game->discard[nextPlayer][1] = testCard;
    game->discard[nextPlayer][2] = testCard;

    game->deckCount[nextPlayer]= 3;
    game->deck[nextPlayer][0] = testCard;
    game->deck[nextPlayer][1] = testCard;
    game->deck[nextPlayer][2] = testCard;

}

// typeFlag 1 is for treasure, typeFlag 2 is for province, typeFlag 3 is for action
void testResults(int before, int after, int plus, int typeFlag) {
    printf("     Actions before: %d\n", before);
    printf("     Actions after: %d\n", after);

    // treasure card duplicates, we expect no change in actions before an after
    if (typeFlag == 1) {
        if (before == after) {
            printf("PASSED\n");
        }
        else {
            printf("FAILED\n");
        } 
    }

    // privince card duplicates, we expect no change in actions before an after
    if (typeFlag == 2) {
        if (before == after) {
            printf("PASSED\n");
        }
        else {
            printf("FAILED\n");
        } 
    }

    // action card duplicates, we expect +2 change in actions before an after
    if (typeFlag == 3) {
        if (before + plus == after) {
            printf("PASSED\n");
        }
        else {
            printf("FAILED\n");
        } 
    }
}

int main(void)
{
    // new game state and test setup
    struct gameState game;
    int coinBonus =0;
    int actionsBefore = 0;
    int actionsAfter = 0;
    testSetup(&game, copper); // start off with copper duplicates

    // header text for the test
    displayTestInfo();

    // save number of actions before the tribute card is used, call functions, get actions after
    // duplicate copper test, function should not award any actions
    printf("Duplicate Copper Treasure Cards. Expect +0 Actions.\n");
    actionsBefore = game.numActions;
    cardEffect(tribute, 1, 0, 0, &game, 0, &coinBonus);
    actionsAfter = game.numActions;
    testResults(actionsBefore, actionsAfter, 2, 1);
    printf("\n");

    // save number of actions before the tribute card is used, call functions, get actions after
    // duplicate silver test, function should not award any actions
    printf("Duplicate Silver Treasure Cards. Expect +0 Actions.\n");
    testSetup(&game, silver); // start off with silver duplicates
    actionsBefore = game.numActions;
    cardEffect(tribute, 1, 0, 0, &game, 0, &coinBonus);
    actionsAfter = game.numActions;
    testResults(actionsBefore, actionsAfter, 2, 1);
    printf("\n");

    // save number of actions before the tribute card is used, call functions, get actions after
    // duplicate estate test, function should not award any actions
    printf("Duplicate Estate Province Cards. Expect +0 Actions.\n");
    testSetup(&game, estate); // start off with estate duplicates
    actionsBefore = game.numActions;
    cardEffect(tribute, 1, 0, 0, &game, 0, &coinBonus);
    actionsAfter = game.numActions;
    testResults(actionsBefore, actionsAfter, 2, 2);
    printf("\n");

    // save number of actions before the tribute card is used, call functions, get actions after
    // duplicate estate test, function should not award any actions
    printf("Duplicate Duchy Province Cards. Expect +0 Actions.\n");
    testSetup(&game, duchy); // start off with estate duplicates
    actionsBefore = game.numActions;
    cardEffect(tribute, 1, 0, 0, &game, 0, &coinBonus);
    actionsAfter = game.numActions;
    testResults(actionsBefore, actionsAfter, 2, 2);
    printf("\n");

    // save number of actions before the tribute card is used, call functions, get actions after
    // duplicate estate test, function should not award any actions
    printf("Duplicate Mine Action Cards. Expect +2 Actions.\n");
    testSetup(&game, mine); // start off with estate duplicates
    actionsBefore = game.numActions;
    cardEffect(tribute, 1, 0, 0, &game, 0, &coinBonus);
    actionsAfter = game.numActions;
    testResults(actionsBefore, actionsAfter, 2, 2);
    printf("\n");

    // save number of actions before the tribute card is used, call functions, get actions after
    // duplicate estate test, function should not award any actions
    printf("Duplicate Baron Province Cards. Expect +2 Actions.\n");
    testSetup(&game, baron); // start off with estate duplicates
    actionsBefore = game.numActions;
    cardEffect(tribute, 1, 0, 0, &game, 0, &coinBonus);
    actionsAfter = game.numActions;
    testResults(actionsBefore, actionsAfter, 2, 2);
    printf("\n");
    
    printf("\n");
}