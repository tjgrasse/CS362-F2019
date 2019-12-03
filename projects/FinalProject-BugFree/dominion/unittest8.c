/*
 * Name:        unittest8.c
 * Description: Unit Test to check that the number of coins is properly updated. 
 * Calls: cardEffect() and updatecoins() functions in dominion.c
 * 
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
    printf("***                 Unit Test 8                 ***\n");
    printf("***************************************************\n\n");
}

void testSetup(struct gameState *game)
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

    game->coins = 0;

    game->discardCount[nextPlayer]= 3;
    game->discard[nextPlayer][0] = copper;
    game->discard[nextPlayer][1] = copper;
    game->discard[nextPlayer][2] = copper;

    game->deckCount[nextPlayer]= 3;
    game->deck[nextPlayer][0] = copper;
    game->deck[nextPlayer][1] = copper;
    game->deck[nextPlayer][2] = copper;

}

void testResults(int before, int after, int plus) {
    printf("     Coins before: %d\n", before);
    printf("     Coins after: %d\n", after);

    if (before + plus == after) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }   
}

int main(void)
{
    // new game state and test setup
    struct gameState game;
    int coinBonus = 0;
    int coinsBefore = 0;
    int coinsAfter = 0;
    testSetup(&game);

    // header text for the test
    displayTestInfo();

    // save number of coins before the baron card is used, call functions, get coins after
    printf("Baron played. Expect +4 number of Coins.\n");
    coinsBefore = game.coins;
    cardEffect(baron, 1, 0, 0, &game, 0, &coinBonus);
    updateCoins(0, &game, coinBonus);
    coinsAfter = game.coins;
    testResults(coinsBefore, coinsAfter, 4);
    printf("\n");

    // save number of coins before the tribute card is used, call functions, get coins after
    printf("Tribute played. Expect +2 number of Coins.\n");
    testSetup(&game);
    coinsBefore = game.coins;
    coinBonus = 0;
    cardEffect(tribute, 1, 0, 0, &game, 0, &coinBonus);
    updateCoins(0, &game, coinBonus);
    coinsAfter = game.coins;
    testResults(coinsBefore, coinsAfter, 2);
    printf("\n");

    // save number of coins before the minion card is used, call functions, get coins after
    printf("Minion played. Expect +2 number of Coins.\n");
    testSetup(&game);
    coinsBefore = game.coins;
    coinBonus = 0;
    cardEffect(minion, 1, 0, 0, &game, 0, &coinBonus);
    updateCoins(0, &game, coinBonus);
    coinsAfter = game.coins;
    testResults(coinsBefore, coinsAfter, 2);
    printf("\n");

    // save number of coins before the embargo card is used, call functions, get coins after
    printf("Embargo played. Expect +2 number of Coins.\n");
    testSetup(&game);
    coinsBefore = game.coins;
    coinBonus = 0;
    cardEffect(embargo, 0, 0, 0, &game, 0, &coinBonus);
    updateCoins(0, &game, coinBonus);
    coinsAfter = game.coins;
    testResults(coinsBefore, coinsAfter, 2);
    printf("\n");

    printf("\n");
}