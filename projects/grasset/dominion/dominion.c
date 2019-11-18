#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
 * \name    - isTreasure
 * \brief   - Function tells user if card is a treasure card or not
 * \param   - int card - card type being checked
 * \return  - 0 if it is a treasure, -1 if it is not a treasure
 */
int isTreasure(int card){
    if ((card >= copper) && (card <= gold)){
        return SUCCESS;
    }
    return ERROR;
}

/*
 * \name    - isVictoryCard
 * \brief   - Function tells user if card is a victory card or not
 * \param   - int card - card type being checked
 * \return  - 0 if it is a victory card, -1 if it is not
 */
int isVictoryCard(int card){
    if ((card >= estate) && (card <= province)){
        return SUCCESS;
    }
    return ERROR;
}

/*
 * \name    - locateAndDiscard
 * \brief   - Function locates the first instance of a card type in the users hand, it then discards
 *            it using the trashFlag to see if it is gone for good or just discarded
 * \param   - int trashCard - card type being looked up
 * \param   - int player - player whose hand they are looking through
 * \param   - struct gameState state - game information
 * \param   - int trashFlag - 0 if discarding, 1 if removing from deck
 * \return  - 0 if it is successfully completed, -1 if it could not locate the card
 */
int locateAndDiscard(int trashCard, int player, struct gameState *state, int trashFlag)
{
    int i;
    for (i = 0; i < state->handCount[player]; i++){
        if (state->hand[player][i] == trashCard){
            discardCard(i, player, state, trashFlag);
            return SUCCESS;
        }
    }
    return ERROR;
}

/*
 * \name    - discardHand
 * \brief   - Function discards all the cards in the particular user's hand
 * \param   - struct gameState state - game information
 * \param   - int player - player whose hand they are discarding
 * \return  - void
 */
void discardHand(struct gameState *state, int player)
{
    while(state->handCount[player] > 0)
    {
        // Continually discard card 0 until all cards in hand are gone
        discardCard(0, player, state, 0);
    }
}

/*
 * \name    - getCardHandQuantity
 * \brief   - Function gets the # of a particular card type in the specified player's hand
 * \param   - int card - Card type being looked up
 * \param   - struct gameState state - game information
 * \param   - int player - player whose hand they are looking through
 * \return  - quantity of cards (0 if none)
 */
int getCardHandQuantity(int card, struct gameState *state, int player)
{
    int quantity = 0;
    // Loop through the hand
    for (int i = 0; i < state->handCount[player]; i++){
        // Check if the card and the player's hand card are the same
        if (card == state->hand[player][i]){
            // Increment the quantity
            quantity++;
        }
    }
    return quantity;
}

/*
 * \name    - getNextPlayer
 * \brief   - Function gets next player to play (player to the left)
 * \param   - int currentPlayer - current player
 * \param   - int numPlayers - number of players in the game
 * \return  - player number in the player array (0-3)
 */
int getNextPlayer(int currentPlayer, int numPlayers)
{
    int nextPlayer = currentPlayer + 1;
    if (nextPlayer > (numPlayers - 1)){
        nextPlayer = 0;
    }
    return nextPlayer;
}

/*
 * \name    - discardLastDrawnCard
 * \brief   - Function discards the last card that was drawn by the player (last card in hand)
 * \param   - int player - player whose hand will have the card discarded from
 * \param   - struct gameState state - game information
 * \return  - 0 on success and -1 on error
 */
int discardLastDrawnCard(int player, struct gameState *state)
{
    int numCards = state->handCount[player];
    if (numCards > 0){
        if (discardCard((numCards - 1), player, state, 0) == ERROR){
            return ERROR;
        }
    }
    else{
        return ERROR;
    }

    return SUCCESS;
}

/*
 * \name    - returnLastDrawnCardType
 * \brief   - Function gets the card type of the last drawn card
 * \param   - int player - player whose hand will have the card discarded from
 * \param   - struct gameState state - game information
 * \return  - type # of the card or a -1 on error
 */
int returnLastDrawnCardType(int player, struct gameState *state)
{
    int numCards = state->handCount[player];
    if (numCards <= 0){
         return ERROR;
    }

    return state->hand[player][numCards - 1];
}

int compare(const void* a, const void* b) {
    if (*(int*)a > *(int*)b)
        return 1;
    if (*(int*)a < *(int*)b)
        return -1;
    return 0;
}

struct gameState* newGame() {
    struct gameState* g = malloc(sizeof(struct gameState));
    return g;
}

int* kingdomCards(int k1, int k2, int k3, int k4, int k5, int k6, int k7,
                  int k8, int k9, int k10) {
    int* k = malloc(10 * sizeof(int));
    k[0] = k1;
    k[1] = k2;
    k[2] = k3;
    k[3] = k4;
    k[4] = k5;
    k[5] = k6;
    k[6] = k7;
    k[7] = k8;
    k[8] = k9;
    k[9] = k10;
    return k;
}

int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
                   struct gameState *state) {
    int i;
    int j;
    int it;

    //set up random number generator
    SelectStream(1);
    PutSeed((long)randomSeed);

    //check number of players
    if (numPlayers > MAX_PLAYERS || numPlayers < 2)
    {
        return -1;
    }

    //set number of players
    state->numPlayers = numPlayers;

    //check selected kingdom cards are different
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (j != i && kingdomCards[j] == kingdomCards[i])
            {
                return -1;
            }
        }
    }


    //initialize supply
    ///////////////////////////////

    //set number of Curse cards
    if (numPlayers == 2)
    {
        state->supplyCount[curse] = 10;
    }
    else if (numPlayers == 3)
    {
        state->supplyCount[curse] = 20;
    }
    else
    {
        state->supplyCount[curse] = 30;
    }

    //set number of Victory cards
    if (numPlayers == 2)
    {
        state->supplyCount[estate] = 8;
        state->supplyCount[duchy] = 8;
        state->supplyCount[province] = 8;
    }
    else
    {
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }

    //set number of Treasure cards
    state->supplyCount[copper] = 60 - (7 * numPlayers);
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    //set number of Kingdom cards
    for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
        for (j = 0; j < 10; j++)           		//loop chosen cards
        {
            if (kingdomCards[j] == i)
            {
                //check if card is a 'Victory' Kingdom card
                if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
                {
                    if (numPlayers == 2) {
                        state->supplyCount[i] = 8;
                    }
                    else {
                        state->supplyCount[i] = 12;
                    }
                }
                else
                {
                    state->supplyCount[i] = 10;
                }
                break;
            }
            else    //card is not in the set choosen for the game
            {
                state->supplyCount[i] = -1;
            }
        }

    }

    ////////////////////////
    //supply intilization complete

    //set player decks
    for (i = 0; i < numPlayers; i++)
    {
        state->deckCount[i] = 0;
        for (j = 0; j < 3; j++)
        {
            state->deck[i][j] = estate;
            state->deckCount[i]++;
        }
        for (j = 3; j < 10; j++)
        {
            state->deck[i][j] = copper;
            state->deckCount[i]++;
        }
    }

    //shuffle player decks
    for (i = 0; i < numPlayers; i++)
    {
        if ( shuffle(i, state) < 0 )
        {
            return -1;
        }
    }

    //draw player hands
    for (i = 0; i < numPlayers; i++)
    {
        //initialize hand size to zero
        state->handCount[i] = 0;
        state->discardCount[i] = 0;
        //draw 5 cards
        // for (j = 0; j < 5; j++)
        //	{
        //	  drawCard(i, state);
        //	}
    }

    //set embargo tokens to 0 for all supply piles
    for (i = 0; i <= treasure_map; i++)
    {
        state->embargoTokens[i] = 0;
    }

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;
    state->handCount[state->whoseTurn] = 0;
    //int it; move to top

    //Moved draw cards to here, only drawing at the start of a turn
    for (it = 0; it < 5; it++) {
        drawCard(state->whoseTurn, state);
    }

    updateCoins(state->whoseTurn, state, 0);

    return 0;
}

int shuffle(int player, struct gameState *state) {


    int newDeck[MAX_DECK];
    int newDeckPos = 0;
    int card;
    int i;

    if (state->deckCount[player] < 1)
        return -1;
    qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare);
    /* SORT CARDS IN DECK TO ENSURE DETERMINISM! */

    while (state->deckCount[player] > 0) {
        card = floor(Random() * state->deckCount[player]);
        newDeck[newDeckPos] = state->deck[player][card];
        newDeckPos++;
        for (i = card; i < state->deckCount[player]-1; i++) {
            state->deck[player][i] = state->deck[player][i+1];
        }
        state->deckCount[player]--;
    }
    for (i = 0; i < newDeckPos; i++) {
        state->deck[player][i] = newDeck[i];
        state->deckCount[player]++;
    }

    return 0;
}

int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
{
    int card;
    int coin_bonus = 0; 		//tracks coins gain from actions

    //check if it is the right phase
    if (state->phase != 0)
    {
        return -1;
    }

    //check if player has enough actions
    if ( state->numActions < 1 )
    {
        return -1;
    }

    //get card played
    card = handCard(handPos, state);

    //check if selected card is an action
    if ( card < adventurer || card > treasure_map )
    {
        return -1;
    }

    //play card
    if ( cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus) < 0 )
    {
        return -1;
    }

    //reduce number of actions
    state->numActions--;

    //update coins (Treasure cards may be added with card draws)
    updateCoins(state->whoseTurn, state, coin_bonus);

    return 0;
}

int buyCard(int supplyPos, struct gameState *state) {
    int who;
    if (DEBUG) {
        printf("Entering buyCard...\n");
    }

    // I don't know what to do about the phase thing.

    who = state->whoseTurn;

    if (state->numBuys < 1) {
        if (DEBUG)
            printf("You do not have any buys left\n");
        return -1;
    } else if (supplyCount(supplyPos, state) <1) {
        if (DEBUG)
            printf("There are not any of that type of card left\n");
        return -1;
    } else if (state->coins < getCost(supplyPos)) {
        if (DEBUG)
            printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
        return -1;
    } else {
        state->phase=1;
        //state->supplyCount[supplyPos]--;
        gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)

        state->coins = (state->coins) - (getCost(supplyPos));
        state->numBuys--;
        if (DEBUG)
            printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
    }

    //state->discard[who][state->discardCount[who]] = supplyPos;
    //state->discardCount[who]++;

    return 0;
}

int numHandCards(struct gameState *state) {
    return state->handCount[ whoseTurn(state) ];
}

int handCard(int handPos, struct gameState *state) {
    int currentPlayer = whoseTurn(state);
    return state->hand[currentPlayer][handPos];
}

int supplyCount(int card, struct gameState *state) {
    return state->supplyCount[card];
}

int fullDeckCount(int player, int card, struct gameState *state) {
    int i;
    int count = 0;

    for (i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == card) count++;
    }

    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == card) count++;
    }

    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == card) count++;
    }

    return count;
}

int whoseTurn(struct gameState *state) {
    return state->whoseTurn;
}

int endTurn(struct gameState *state) {
    int k;
    int i;
    int currentPlayer = whoseTurn(state);

    //Discard hand
    for (i = 0; i < state->handCount[currentPlayer]; i++) {
        state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        state->hand[currentPlayer][i] = -1;//Set card to -1
    }
    state->handCount[currentPlayer] = 0;//Reset hand count

    //Code for determining the player
    if (currentPlayer < (state->numPlayers - 1)) {
        state->whoseTurn = currentPlayer + 1;//Still safe to increment
    }
    else {
        state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
    }

    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->coins = 0;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->handCount[state->whoseTurn] = 0;

    //int k; move to top
    //Next player draws hand
    for (k = 0; k < 5; k++) {
        drawCard(state->whoseTurn, state);//Draw a card
    }

    //Update money
    updateCoins(state->whoseTurn, state, 0);

    return 0;
}

int isGameOver(struct gameState *state) {
    int i;
    int j;

    //if stack of Province cards is empty, the game ends
    if (state->supplyCount[province] == 0)
    {
        return 1;
    }

    //if three supply pile are at 0, the game ends
    j = 0;
    for (i = 0; i < 25; i++)
    {
        if (state->supplyCount[i] == 0)
        {
            j++;
        }
    }
    if ( j >= 3)
    {
        return 1;
    }

    return 0;
}

int scoreFor (int player, struct gameState *state) {

    int i;
    int score = 0;
    //score from hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == curse) {
            score = score - 1;
        };
        if (state->hand[player][i] == estate) {
            score = score + 1;
        };
        if (state->hand[player][i] == duchy) {
            score = score + 3;
        };
        if (state->hand[player][i] == province) {
            score = score + 6;
        };
        if (state->hand[player][i] == great_hall) {
            score = score + 1;
        };
        if (state->hand[player][i] == gardens) {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    //score from discard
    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == curse) {
            score = score - 1;
        };
        if (state->discard[player][i] == estate) {
            score = score + 1;
        };
        if (state->discard[player][i] == duchy) {
            score = score + 3;
        };
        if (state->discard[player][i] == province) {
            score = score + 6;
        };
        if (state->discard[player][i] == great_hall) {
            score = score + 1;
        };
        if (state->discard[player][i] == gardens) {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    //score from deck
    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->deck[player][i] == curse) {
            score = score - 1;
        };
        if (state->deck[player][i] == estate) {
            score = score + 1;
        };
        if (state->deck[player][i] == duchy) {
            score = score + 3;
        };
        if (state->deck[player][i] == province) {
            score = score + 6;
        };
        if (state->deck[player][i] == great_hall) {
            score = score + 1;
        };
        if (state->deck[player][i] == gardens) {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    return score;
}

int getWinners(int players[MAX_PLAYERS], struct gameState *state) {
    int i;
    int j;
    int highScore;
    int currentPlayer;

    //get score for each player
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        //set unused player scores to -9999
        if (i >= state->numPlayers)
        {
            players[i] = -9999;
        }
        else
        {
            players[i] = scoreFor (i, state);
        }
    }

    //find highest score
    j = 0;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (players[i] > players[j])
        {
            j = i;
        }
    }
    highScore = players[j];

    //add 1 to players who had less turns
    currentPlayer = whoseTurn(state);
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if ( players[i] == highScore && i > currentPlayer )
        {
            players[i]++;
        }
    }

    //find new highest score
    j = 0;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if ( players[i] > players[j] )
        {
            j = i;
        }
    }
    highScore = players[j];

    //set winners in array to 1 and rest to 0
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if ( players[i] == highScore )
        {
            players[i] = 1;
        }
        else
        {
            players[i] = 0;
        }
    }

    return 0;
}

/*
 * \name    - drawXCards
 * \brief   - Function draws x number of cards for a player
 * \param   - int count - number of cards that will be drawn
 * \param   - int player - player whose hand will have the card discarded from
 * \param   - struct gameState state - game information
 * \return  - 0 on success and -1 on error
 */
int drawXCards(int count, int player, struct gameState *state)
{
    for (int i = 0; i < count; i++){
        if (drawCard(player, state) == ERROR){
            return ERROR;
        }
    }
    return SUCCESS;
}

int drawCard(int player, struct gameState *state)
{   int count;
    int deckCounter;
    if (state->deckCount[player] <= 0) { //Deck is empty

        //Step 1 Shuffle the discard pile back into a deck
        int i;
        //Move discard to deck
        for (i = 0; i < state->discardCount[player]; i++) {
            state->deck[player][i] = state->discard[player][i];
            state->discard[player][i] = -1;
        }

        state->deckCount[player] = state->discardCount[player];
        state->discardCount[player] = 0;//Reset discard

        //Shufffle the deck
        shuffle(player, state);//Shuffle the deck up and make it so that we can draw

        if (DEBUG) { //Debug statements
            printf("Deck count now: %d\n", state->deckCount[player]);
        }

        state->discardCount[player] = 0;

        //Step 2 Draw Card
        count = state->handCount[player];//Get current player's hand count

        if (DEBUG) { //Debug statements
            printf("Current hand count: %d\n", count);
        }

        deckCounter = state->deckCount[player];//Create a holder for the deck count

        if (deckCounter == 0)
            return -1;

        state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
        state->deckCount[player]--;
        state->handCount[player]++;//Increment hand count
    }

    else {
        int count = state->handCount[player];//Get current hand count for player
        int deckCounter;
        if (DEBUG) { //Debug statements
            printf("Current hand count: %d\n", count);
        }

        deckCounter = state->deckCount[player];//Create holder for the deck count
        state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
        state->deckCount[player]--;
        state->handCount[player]++;//Increment hand count
    }

    return 0;
}

int getCost(int cardNumber)
{
    switch( cardNumber )
    {
    case curse:
        return 0;
    case estate:
        return 2;
    case duchy:
        return 5;
    case province:
        return 8;
    case copper:
        return 0;
    case silver:
        return 3;
    case gold:
        return 6;
    case adventurer:
        return 6;
    case council_room:
        return 5;
    case feast:
        return 4;
    case gardens:
        return 4;
    case mine:
        return 5;
    case remodel:
        return 4;
    case smithy:
        return 4;
    case village:
        return 3;
    case baron:
        return 4;
    case great_hall:
        return 3;
    case minion:
        return 5;
    case steward:
        return 3;
    case tribute:
        return 5;
    case ambassador:
        return 3;
    case cutpurse:
        return 4;
    case embargo:
        return 2;
    case outpost:
        return 5;
    case salvager:
        return 4;
    case sea_hag:
        return 4;
    case treasure_map:
        return 4;
    }

    return -1;
}

/*
 * \name    - processBaronCard
 * \brief   - Function processes the Baron card when played
 * \param   - int discardEstate - 1 if discarding an estate, 0 if not
 * \param   - int handPos - current index of the Baron Card
 * \param   - struct gameState state - game information
 * \return  - 0 on success and -1 on error
 */
int processBaronCard(int discardEstate, int handPos, struct gameState *state)
{
    int player = whoseTurn(state);
    state->numBuys++;

    if (discardEstate){
        // Unable to locate an estate in the hand
        if (locateAndDiscard(estate, player, state, 0) == ERROR){
            if(DEBUG) {
                printf("No estate cards in your hand, invalid choice\n");
                printf("Must gain an estate if there are any\n");
            }
            // Gain an estate card
            if (gainCard(estate, state, 0, player) == ERROR){
                return ERROR;
            }
        }
        else{
            // Gain 4 coins
            state->coins += 4;
        }
    }
    else{
        // Gain an estate card
        gainCard(estate, state, 0, player);
    }

    // Discard the Baron Card
    discardCard(handPos, player, state, 1);

    return SUCCESS;
}

/*
 * \name    - processMinionCard
 * \brief   - Function processes the Minion card when played
 * \param   - int chooseCoins - player has chosen to receive coins
 * \param   - int chooseCards - player has chosen to discard cards
 * \param   - int handPos - current index of the Minion Card
 * \param   - struct gameState state - game information
 * \return  - 0 on success and -1 on error
 */
int processMinionCard(int chooseCoins, int chooseCards, int handPos, struct gameState *state)
{
    int player = whoseTurn(state);
    state->numActions++;

    if (chooseCoins){
        state->coins += 2;
    }
    else if (chooseCards){
        // Discard Hand
        discardHand(state, player);
        // Gain 4 cards
        if (drawXCards(4, player, state) == ERROR){
            return ERROR;
        }
        // Run through Each Player's hand
        for (int j = 0; j < 4; j++){
            if (j != player){   // If not the current player
                if (state->handCount[j] > 5){   // If they have 5 or more cards
                    // Discard the hand
                    discardHand(state, j);
                    // Draw 4 new cards
                    if (drawXCards(4, j, state) == ERROR){
                        return ERROR;
                    }
                }
            }
        }
    }

    // Discard the Minion Card
    discardCard(handPos, player, state, 0);

    return SUCCESS;
}

/*
 * \name    - processAmbassadorCard
 * \brief   - Function processes the Ambassador card when played
 * \param   - int revealCard - card type player has revealed 
 * \param   - int returnCards - # of cards the player will be returning
 * \param   - int handPos - current index of the Ambassador Card
 * \param   - struct gameState state - game information
 * \return  - 0 on success and -1 on error
 */
int processAmbassadorCard(int revealCard, int returnCards, int handPos, struct gameState *state)
{
    int player = whoseTurn(state);
    int cardType = state->hand[player][revealCard];

    // Reveal card cannot be the card being played 
    if (revealCard == handPos){
        return ERROR;
    }

    int cardNumber = getCardHandQuantity(cardType, state, player);
    // If the user does not have the proper quantity of cards to remove return error
    if (cardNumber < returnCards){
        return ERROR;
    }

    // If there will not be enough cards to hand out.  The supply and number being
    // returned should be >= to the number of players minus the current player
    if ((state->supplyCount[cardType] + returnCards) < state->numPlayers){
        return ERROR;
    }

    // Discard the number of cards wanted
    for (int k = 0; k < returnCards; k++){
        if (locateAndDiscard(cardType, player, state, 1) == ERROR){
            return ERROR;
        }
    }

    // Add the cards to the other players discard piles.
    for (int i = 0; i < state->numPlayers; i++){
        if (i != player){
            if (gainCard(cardType, state, 0, i) == ERROR){
                return ERROR;
            }
        }
    }

    return SUCCESS;
}

/*
 * \name    - processTributeCard
 * \brief   - Function processes the Tribute card when played
 * \param   - int handPos - current index of the Tribute Card
 * \param   - struct gameState state - game information
 * \return  - 0 on success and -1 on error
 */
int processTributeCard(int handPos, struct gameState *state)
{
    int player = whoseTurn(state);
    int nextPlayer = getNextPlayer(player, state->numPlayers);
    int npDiscard = state->discardCount[nextPlayer];
    int npDeck = state->deckCount[nextPlayer];
    int card1 = -1;
    int card2 = -1;

    if (npDeck >= 2){   // If the deck has two cards that can be pulled
        drawCard(nextPlayer, state);
        card1 = returnLastDrawnCardType(nextPlayer, state);
        drawCard(nextPlayer, state);
        card2 = returnLastDrawnCardType(nextPlayer, state);
    }
    else if ((npDeck + npDiscard) >= 2){
        // If the deck and discard have two cards that can be pulled 
        if (npDeck > 0){
            // Draw First Card
            drawCard(nextPlayer, state);
            card1 = returnLastDrawnCardType(nextPlayer, state);
            // Shuffle in discard pile to get cards to draw
            shuffle(nextPlayer, state);
            // Draw the Second Card
            drawCard(nextPlayer, state);
            card2 = returnLastDrawnCardType(nextPlayer, state);
        }
        else{
            // Shuffle in discard pile to get cards to draw
            shuffle(nextPlayer, state);
            // Draw First Card
            drawCard(nextPlayer, state);
            card1 = returnLastDrawnCardType(nextPlayer, state);
            // Draw the Second Card
            drawCard(nextPlayer, state);
            card2 = returnLastDrawnCardType(nextPlayer, state);
        }
    }

    // Compare Cards Here
    if (card1 != card2){
        if (isTreasure(card1) == SUCCESS){
            state->coins += 2;
        }
        else if (isVictoryCard(card1) == SUCCESS){
            drawXCards(2, player, state);
        }
        else {  // Action Card
            state->numActions += 2;
        }

        if (isTreasure(card2) == SUCCESS){
            state->coins += 2;
        }
        else if (isVictoryCard(card2) == SUCCESS){
            drawXCards(2, player, state);
        }
        else {  // Action Card
            state->numActions += 2;
        }
    }

    // Remember to remove the last two cards from the next player
    discardLastDrawnCard(nextPlayer, state);
    discardLastDrawnCard(nextPlayer, state);

    // Discard the Tribute Card
    discardCard(handPos, player, state, 0);
    
    return SUCCESS;
}

/*
 * \name    - processMineCard
 * \brief   - Function processes the Mine card when played
 * \param   - int handPos - current index of the Mine Card
 * \param   - int trashCard - card the user will be trashing
 * \param   - int treasureCard - card the user wants to exchange for the trash card
 * \param   - struct gameState state - game information
 * \return  - 0 on success and -1 on error
 */
int processMineCard(int handPos, int trashCard, int treasureCard, struct gameState *state)
{
    int player = whoseTurn(state);

    // Check if the card being trashed is a treasure cad
    if (isTreasure(trashCard) == SUCCESS){ 
        // Check if the card being picked is a treasure card
        if (isTreasure(treasureCard) == SUCCESS){
            // Check if the cost of the new card is within 3 cost of the trashed card
            if ((getCost(trashCard) + 3) < getCost(treasureCard)){
                gainCard(treasureCard, state, 2, player);
                discardCard(handPos, player, state, 0);      // Discard the Mine Card
                // Discard the card being trashed
                if (locateAndDiscard(trashCard, player, state, 1) == SUCCESS){
                    return SUCCESS;
                }
            }
        }
    }
    return ERROR;
}


int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
{
    int i;
    int j;
    int k;
    int x;
    int index;
    int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;

    int temphand[MAX_HAND];// moved above the if statement
    int drawntreasure=0;
    int cardDrawn;
    int z = 0;// this is the counter for the temp hand
    if (nextPlayer > (state->numPlayers - 1)) {
        nextPlayer = 0;
    }


    //uses switch to select card and perform actions
    switch( card )
    {
    case adventurer:
        while(drawntreasure<2) {
            if (state->deckCount[currentPlayer] <1) { //if the deck is empty we need to shuffle discard and add to deck
                shuffle(currentPlayer, state);
            }
            drawCard(currentPlayer, state);
            cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                drawntreasure++;
            else {
                temphand[z]=cardDrawn;
                state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
                z++;
            }
        }
        while(z-1>=0) {
            state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
            z=z-1;
        }
        return 0;

    case council_room:
        //+4 Cards
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, state);
        }

        //+1 Buy
        state->numBuys++;

        //Each other player draws a card
        for (i = 0; i < state->numPlayers; i++)
        {
            if ( i != currentPlayer )
            {
                drawCard(i, state);
            }
        }

        //put played card in played card pile
        discardCard(handPos, currentPlayer, state, 0);

        return 0;

    case feast:
        //gain card with cost up to 5
        //Backup hand
        for (i = 0; i <= state->handCount[currentPlayer]; i++) {
            temphand[i] = state->hand[currentPlayer][i];//Backup card
            state->hand[currentPlayer][i] = -1;//Set to nothing
        }
        //Backup hand

        //Update Coins for Buy
        updateCoins(currentPlayer, state, 5);
        x = 1;//Condition to loop on
        while( x == 1) {//Buy one card
            if (supplyCount(choice1, state) <= 0) {
                if (DEBUG)
                    printf("None of that card left, sorry!\n");

                if (DEBUG) {
                    printf("Cards Left: %d\n", supplyCount(choice1, state));
                }
            }
            else if (state->coins < getCost(choice1)) {
                printf("That card is too expensive!\n");

                if (DEBUG) {
                    printf("Coins: %d < %d\n", state->coins, getCost(choice1));
                }
            }
            else {

                if (DEBUG) {
                    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
                }

                gainCard(choice1, state, 0, currentPlayer);//Gain the card
                x = 0;//No more buying cards

                if (DEBUG) {
                    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
                }

            }
        }

        //Reset Hand
        for (i = 0; i <= state->handCount[currentPlayer]; i++) {
            state->hand[currentPlayer][i] = temphand[i];
            temphand[i] = -1;
        }
        //Reset Hand

        return 0;

    case gardens:
        return -1;

    case mine:
        return processMineCard(handPos, state->hand[currentPlayer][choice1],
                        choice2, state);

    case remodel:
        j = state->hand[currentPlayer][choice1];  //store card we will trash

        if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
        {
            return -1;
        }

        gainCard(choice2, state, 0, currentPlayer);

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);

        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(i, currentPlayer, state, 0);
                break;
            }
        }


        return 0;

    case smithy:
        //+3 Cards
        for (i = 0; i < 3; i++)
        {
            drawCard(currentPlayer, state);
        }

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case village:
        //+1 Card
        drawCard(currentPlayer, state);

        //+2 Actions
        state->numActions = state->numActions + 2;

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case baron:
        return processBaronCard(choice1, handPos, state);

    case great_hall:
        //+1 Card
        drawCard(currentPlayer, state);

        //+1 Actions
        state->numActions++;

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case minion:
        return processMinionCard(choice1, choice2, handPos, state);

    case steward:
        if (choice1 == 1)
        {
            //+2 cards
            drawCard(currentPlayer, state);
            drawCard(currentPlayer, state);
        }
        else if (choice1 == 2)
        {
            //+2 coins
            state->coins = state->coins + 2;
        }
        else
        {
            //trash 2 cards in hand
            discardCard(choice2, currentPlayer, state, 1);
            discardCard(choice3, currentPlayer, state, 1);
        }

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case tribute:
        return processTributeCard(handPos, state);

    case ambassador:
        return processAmbassadorCard(choice1, choice2, handPos, state);

    case cutpurse:

        updateCoins(currentPlayer, state, 2);
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                for (j = 0; j < state->handCount[i]; j++)
                {
                    if (state->hand[i][j] == copper)
                    {
                        discardCard(j, i, state, 0);
                        break;
                    }
                    if (j == state->handCount[i])
                    {
                        for (k = 0; k < state->handCount[i]; k++)
                        {
                            if (DEBUG)
                                printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
                        }
                        break;
                    }
                }

            }

        }

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);

        return 0;


    case embargo:
        //+2 Coins
        state->coins = state->coins + 2;

        //see if selected pile is in play
        if ( state->supplyCount[choice1] == -1 )
        {
            return -1;
        }

        //add embargo token to selected supply pile
        state->embargoTokens[choice1]++;

        //trash card
        discardCard(handPos, currentPlayer, state, 1);
        return 0;

    case outpost:
        //set outpost flag
        state->outpostPlayed++;

        //discard card
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case salvager:
        //+1 buy
        state->numBuys++;

        if (choice1)
        {
            //gain coins equal to trashed card
            state->coins = state->coins + getCost( handCard(choice1, state) );
            //trash card
            discardCard(choice1, currentPlayer, state, 1);
        }

        //discard card
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case sea_hag:
        for (i = 0; i < state->numPlayers; i++) {
            if (i != currentPlayer) {
                state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];
                state->deckCount[i]--;
                state->discardCount[i]++;
                state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
            }
        }
        return 0;

    case treasure_map:
        //search hand for another treasure_map
        index = -1;
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == treasure_map && i != handPos)
            {
                index = i;
                break;
            }
        }
        if (index > -1)
        {
            //trash both treasure cards
            discardCard(handPos, currentPlayer, state, 1);
            discardCard(index, currentPlayer, state, 1);

            //gain 4 Gold cards
            for (i = 0; i < 4; i++)
            {
                gainCard(gold, state, 1, currentPlayer);
            }

            //return success
            return 1;
        }

        //no second treasure_map found in hand
        return -1;
    }

    return -1;
}

int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{

    //if card is not trashed, added to Played pile
    if (trashFlag < 1)
    {
        //add card to played pile
        state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
        state->playedCardCount++;
    }

    //set played card to -1
    state->hand[currentPlayer][handPos] = -1;

    //remove card from player's hand
    if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
    {
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }
    else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
    {
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }
    else
    {
        //replace discarded card with last card in hand
        state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
        //set last card to -1
        state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }

    return 0;
}

int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
    //Note: supplyPos is enum of choosen card

    //check if supply pile is empty (0) or card is not used in game (-1)
    if ( supplyCount(supplyPos, state) < 1 )
    {
        return -1;
    }

    //added card for [whoseTurn] current player:
    // toFlag = 0 : add to discard
    // toFlag = 1 : add to deck
    // toFlag = 2 : add to hand

    if (toFlag == 1)
    {
        state->deck[ player ][ state->deckCount[player] ] = supplyPos;
        state->deckCount[player]++;
    }
    else if (toFlag == 2)
    {
        state->hand[ player ][ state->handCount[player] ] = supplyPos;
        state->handCount[player]++;
    }
    else
    {
        state->discard[player][ state->discardCount[player] ] = supplyPos;
        state->discardCount[player]++;
    }

    //decrease number in supply pile
    state->supplyCount[supplyPos]--;

    return 0;
}

int updateCoins(int player, struct gameState *state, int bonus)
{
    int i;

    //reset coin count
    state->coins = 0;

    //add coins for each Treasure card in player's hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == copper)
        {
            state->coins += 1;
        }
        else if (state->hand[player][i] == silver)
        {
            state->coins += 2;
        }
        else if (state->hand[player][i] == gold)
        {
            state->coins += 3;
        }
    }

    //add bonus
    state->coins += bonus;

    return 0;
}


//end of dominion.c

