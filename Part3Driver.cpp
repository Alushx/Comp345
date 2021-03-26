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
#include <vector>
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
	selectBidWinner();

	// Display 6 cards.
	Hand* hand = new Hand(deck);
	hand->printHand();

	// Placing each player's 4 armies.
	placeArmies(mapLoader);

	// Places bot armies.
	placeBotArmies(mapLoader);

	// Getting the list of players.
	vector<Player*> player;
	player = Player::getPlayerList();

	int index = 0;

	int numOfTurns = 0;

	// Based on the number of players we decide numOfTurns
	for (int j = 0 ; j < numOfTurns ; j++ )
	{ 
		for (int i = 0; i < player.size(); i++)
		{
			index = 0;
			while (index >= 0) {
				hand->printHand();
				cout << "Please enter the index of the card you want to pick or a negative number to exit: ";
				cin >> index;
				Card* card = hand->exchange(index, player[i]);
				if (card == NULL)
					break;
				else
				{
					player[i]->playCard(card, mapLoader->getMap());
				}
			}
		}
	}

	// Deallocating Players and Bot armies.
	deallocateResources(mapLoader, deck);

	return 0;
}