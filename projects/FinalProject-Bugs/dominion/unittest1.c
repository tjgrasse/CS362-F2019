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

int main(void)
{
    struct gameState state, prevState;

    displayTestInfo();

    memset(&state, 0, sizeof(struct gameState));
    memset(&prevState, 0, sizeof(struct gameState));


    printf("\n");
}