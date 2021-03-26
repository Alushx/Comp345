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

#include "MapLoader/MapLoader.h"
#include "Cards/Cards.h"
#include "Player.h"
#include "Game.h"

int main()
{
	// Setting up players, bidding facility, and map.
	MapLoader* mapLoader;
	mapLoader = startGame();

	// Creating deck.
	Deck* deck = new Deck(Player::getPlayerNum());
	deck->generateDeck();
	deck->printDeck();

	// Deallocating Players and Bot armies.
	deallocateResources(mapLoader, deck);

	return 0;
}