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

#include "Map.h"
#include "BiddingFacility.h"
#include "Player.h"
#include "Cards/Cards.h"
#include "Maploader/MapLoader.h"

using namespace std;

int main()
{
	// Setting up players, bidding facility, and map.
	MapLoader* mapLoader;
	mapLoader = startGame();

	// Creating deck.
	Deck* deck = new Deck(Player::getPlayerNum());
	deck->generateDeck();
	deck->shuffleDeck();
	deck->printDeck();

	// Selecting first player.
	int bidWinner = -1;
	bidWinner = BiddingFacility::biddingPhase(Player::getPlayerList());
	Player::getPlayerList()[bidWinner];

	// Display 6 cards.
	Hand* hand = new Hand(deck);
	hand->printHand();

	// Placing each player's 4 armies.
	Territory* startingTerritory = mapLoader->getMap()->getTerritory("territory1");
	Player::setStartingRegion(startingTerritory);

	for (Player* player : Player::getPlayerList())
	{
		for (int i = 0; i < 4; i++)
		{
			player->placeNewArmies(startingTerritory);
		}
	}

	// Places bot armies.
	if (Player::getPlayerNum() == 2)
	{
		Player* bot = Player::getBot();
		bot->placeBotArmies(10, mapLoader->getMap());
	}

	// Deallocating stuff.
	delete mapLoader;
	delete deck;

	vector<Player*> players = Player::getPlayerList();
	for (int i = 0; i < Player::getPlayerNum(); i++)
	{
		delete players[i];
	}
	if (Player::getBot() != NULL)
		delete Player::getBot();
	return 0;
}