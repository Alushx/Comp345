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
	int bidWinner = -1;
	bidWinner = BiddingFacility::biddingPhase(Player::getPlayerList());
	Player::getPlayerList()[bidWinner];

	// Display 6 cards.
	Hand* hand = new Hand(deck);
	hand->printHand();

	// Placing each player's 4 armies.
	placeArmies(mapLoader);

	// Places bot armies.
	placeBotArmies(mapLoader);

	// Cad related task.
	vector<Player*> player;
	player = Player::getPlayerList();
	int playerNum = Player::getPlayerNum();

	int index = 0;
	int numOfTurns = 0; // Figure out numOfTurns based on players.

	for (int turn = 0; turn < numOfTurns; turn++)
	{
		for (int i = 0; i < player.size(); i++)
		{
			index = 0;
			while (index >= 0) {
				hand->printHand();
				cout << "Please enter the index of the card you want to pick or a negative number to exit: ";
				cin >> index;

				// Checking valid input.
				if (index >= 0 && index < 5)
				{
					Card* card = hand->exchange(index, player[(bidWinner + i) % playerNum]);
					if (card == NULL)
					{
						continue;
					}
					player[(bidWinner + i) % playerNum]->playCard(card, mapLoader->getMap());
				}
				else
					continue;
			}
		}
	}

	// Compute score
	calculateScore(mapLoader);


	// Determine winner
	determineWinner();



	// Deallocating Players and Bot armies.
	deallocateResources(mapLoader, deck);

	return 0;
}