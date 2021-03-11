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

#include <string>
#include "Cards/Cards.h"
#include "MapLoader/MapLoader.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
using namespace std;

int main() 
{
    // Creating players.
    Player* player1 = new Player("Anakin", 14);
    Player* player2 = new Player("Obi Wan", 14);
    
    // Creating deck.
    Deck* deck = new Deck(Player::getPlayerNum());

    // Creating map.
    MapLoader* mapLoader = new MapLoader();
    mapLoader->readMapFile("map1.txt", Player::getPlayerNum());
    Player::setStartingRegion(mapLoader->getMap()->getTerritory("territory1"));

    // Creating 4 armies for each player to start things off.
    player1->placeNewArmies(Player::getStartingRegion());
    player1->placeNewArmies(Player::getStartingRegion());
    player1->placeNewArmies(Player::getStartingRegion());
    player1->placeNewArmies(Player::getStartingRegion());

    player2->placeNewArmies(Player::getStartingRegion());
    player2->placeNewArmies(Player::getStartingRegion());
    player2->placeNewArmies(Player::getStartingRegion());
    player2->placeNewArmies(Player::getStartingRegion());

    // Generating and shuffling the cards.
    deck->generateDeck();
    deck->shuffleDeck();
    cout << "PlayerNum: " << Player::getPlayerNum() << endl;

    // Preparing the hand.
    cout << "\n\n___________________________________________________Card Space\n\n" << endl;
    Hand* hand = new Hand(deck);

    // Playing the card.
    int index = 0;
    while (index >= 0) {
        hand->printHand();
        cout << "Please enter the index of the card you want tp pick or a negative number to exit: ";
        cin >> index;
        player1->playCard(hand->exchange(index, player1), mapLoader->getMap());
    }

    // Deallocating heap.
    if (hand != NULL)
        delete hand;
    hand = nullptr;
    if (deck != NULL)
        delete deck;
    deck = nullptr;
    if (player1 != NULL)
        delete player1;
    player1 = nullptr;
    if (player2 != NULL)
        delete player2;
    player2 = nullptr;
    if (mapLoader != NULL)
        delete mapLoader;
    mapLoader = nullptr;

}