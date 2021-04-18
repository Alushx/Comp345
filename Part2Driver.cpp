#include "Game.h"
#include "Player.h"
#include "Cards.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"
#include <string>

using namespace std;

// An alternative to startGame() specifically for this driver.
// Reduces some options to quickly get to the focus of this part of the assignment.
MapLoader* setUpDriver2()
{
	const int NUM_OF_PLAYERS = 2;
	const int COIN_AMOUNT = 14;
	string name = "";

	// Create all players. Can later be retrieved through the static method.
	for (int i = 1; i <= NUM_OF_PLAYERS; i++) {
		cout << "Player " << i << " last name: " << std::endl;
		cin >> name;
		new Player(name, COIN_AMOUNT, new HumanPlayer);
	}

	string fileName = "map1.txt";

	return loadValidMap(fileName);
}

int main()
{
	// Setting up players, bidding facility, and map.
	MapLoader* mapLoader = setUpDriver2();

	// Creating deck.
	Deck* deck = new Deck(Player::getPlayerNum());
	createDeck(deck);
	Hand* hand = new Hand(deck);

	// Placing each player's 4 armies.
	placeArmies(mapLoader);

	// Main game loop
	playGame(hand, 0, mapLoader, 3);

	// Deallocating Players and Bot armies.
	deallocateResources(mapLoader, deck, hand);

	return 0;
}