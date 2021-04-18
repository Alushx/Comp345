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

void playGamePart3(Hand* hand, int bidWinner, MapLoader* mapLoader, int selectedMode)
{
	// Setting up variables.
	vector<Player*> player = Player::getPlayerList();
	int playerNum = Player::getPlayerNum();
	Turn* turn = createTurns(selectedMode, mapLoader->getMap(), hand);
	GameState* state = new GameState(mapLoader->getMap());

	// Adding observers. Automatically deleted by subject.
	new View(state);
	new PlayerTurnViewer(turn);
	new CardPickViewer(turn);
	for (Player* subjectPlayer : player)
	{
		new PlayerActionViewer(subjectPlayer);
		new CardBonusViewer(subjectPlayer);
	}

	// Main game loop.
	for (int i = 0; i < turn->getMaxNumOfTurns(); i++)
	{
		for (int j = 0; j < player.size(); j++)
		{
			turn->setPlayerTurn(player[(bidWinner + j) % playerNum]);
			turn->playTurn();
			state->computeGameState();
		}
	}

	delete turn;
	delete state;
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
	playGamePart3(hand, 0, mapLoader, 3);

	// Deallocating Players and Bot armies.
	deallocateResources(mapLoader, deck, hand);

	return 0;
}