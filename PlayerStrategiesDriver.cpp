//===================================================================
// Course: COMP 345
// Professor: Nora Houari
// Team: 14
// Students:
//      Adam Yafout - 40040306
//      Bryan Lee - 40079332
//      Carl Randyl Tuquero - 40067781
//      Sobhan Mehrpour - 40122438
//      Vithura Muthiah - 40062305
//===================================================================
#include "Player.h"
#include "Cards.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"
#include <string>
#include "Game.h"
using namespace std;

int main()
{
    // Setting up players, bidding facility, and map.
    MapLoader* mapLoader;
    mapLoader = startGame();

    // Creating deck.
    Deck* deck = new Deck(Player::getPlayerNum());
    createDeck(deck);

    // Selecting first player.
    int bidWinner = selectBidWinner();

    // Display 6 cards.
    Hand* hand = new Hand(deck);
    hand->printHand();

    // Placing each player's 4 armies.
    placeArmies(mapLoader);

    // Places bot armies.
    placeBotArmies(mapLoader);

    // Main game loop
    playGame(hand, bidWinner, mapLoader, 1);

    // Compute score
    calculateScore(mapLoader);

    // Determine winner
    determineWinner();

    // Deallocating Players and Bot armies.
    deallocateResources(mapLoader, deck, hand);

    return 0;
}