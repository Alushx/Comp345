#include "Game.h"
#include "Player.h"
#include "Cards.h"
#include "MapLoader.h"

using namespace std;

int main()
{
	// Setting up players, bidding facility, and map.
	MapLoader* mapLoader = startGame();

	// Creating deck.
	Deck* deck = new Deck(Player::getPlayerNum());
	createDeck(deck);

	// Display 6 cards.
	Hand* hand = new Hand(deck);
	hand->printHand();

	// Placing each player's 4 armies.
	placeArmies(mapLoader);

	// Main game loop
	playGame(hand, 0, mapLoader, 1);

	displayTournamentResults();

	// Deallocating Players and Bot armies.
	deallocateResources(mapLoader, deck, hand);

	return 0;
}