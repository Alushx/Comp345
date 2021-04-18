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
#include "GameObservers.h"
#include "PlayerStrategies.h"

using namespace std;

//Deallocate MapLoader, Deck, Hand, and Players.
// Armies, Cities, Cards, and Maps are deleted by the former 4.
void deallocateResources(MapLoader* mapLoader, Deck* deck, Hand* hand) {
	delete mapLoader;
	delete deck;
    delete hand;

	vector<Player*> players = Player::getPlayerList();
	for (int i = 0; i < Player::getPlayerNum(); i++)
	{
		delete players[i];
	}
	if (Player::getBot() != NULL)
		delete Player::getBot();
}

//Determine the bid winner
int selectBidWinner() {
	int bidWinner = -1;
	bidWinner = BiddingFacility::biddingPhase(Player::getPlayerList());
	Player::getPlayerList()[bidWinner];
    return bidWinner;
}

//Create the deck: generate it, shuffle it and print it.
void createDeck(Deck *deck) {
	deck->generateDeck();
	deck->shuffleDeck();
}

//Method to place the armies
void placeArmies(MapLoader* mapLoader) {
	Territory* startingTerritory = mapLoader->getMap()->getTerritory("territory1");
	Player::setStartingRegion(startingTerritory);

	for (Player* player : Player::getPlayerList())
	{
		for (int i = 0; i < 4; i++)
		{
			player->placeNewArmies(startingTerritory);
		}
	}
}

//Method to place the bot armies
void placeBotArmies(MapLoader* mapLoader) {
	if (Player::getPlayerNum() == 2)
	{
		Player* bot = Player::getBot();
		bot->placeBotArmies(10, mapLoader->getMap());
	}
}

//Compute the Score
void calculateScore(MapLoader* mapLoader) {
	calculateScore(mapLoader->getMap());
}

// Calculates the score.
void calculateScore(Map* map)
{
	for (Player* playerChar : Player::getPlayerList())
	{
		playerChar->computeScore(map);
	}

	Player::computeElixerScore();
}

//Determine the Winner
void determineWinner() {
	Player* winner = nullptr;
	winner = Player::announcement(Player::getPlayerList());

	cout << "The winner is: " << *winner << endl;
}

// Function that starts creates loads a map, builds it, creates players, and the bidding facility.
// Callers of this function are responsible for deallocating memory of MapLoader and the player created here.
// Note that the player have to be retrieved with the static Player method.
MapLoader* startGame()
{
	// Armies, tokens, cities, and bidding facility is all created within each instance of Player.
	createPlayers();
	string fileName = chooseFile();
	return loadValidMap(fileName);
}

void playGame(Hand* hand, int bidWinner, MapLoader* mapLoader, int selectedMode)
{
	// Setting up variables.
	vector<Player*> player = Player::getPlayerList();
	int playerNum = Player::getPlayerNum();
	Turn* turn = createTurns(selectedMode, mapLoader->getMap(), hand);

	// Adding observers. Automatically deleted by subject.
	new PlayerTurnViewer(turn);
	new CardPickViewer(turn);
	for (Player* subjectPlayer : player)
		new PlayerActionViewer(subjectPlayer);

	// Main game loop.
	for (int i = 0; i < turn->getMaxNumOfTurns(); i++)
	{
		for (int j = 0; j < player.size(); j++)
		{
			turn->setPlayerTurn(player[(bidWinner + j) % playerNum]);
			turn->playTurn();
		}
	}

	delete turn;
}

// Displays the tournament results as a table.
void displayTournamentResults()
{
	cout << "=========================================================" << endl;
	cout << "||   Player #   ||   Cards   ||   Score   ||   Coins   ||" << endl;

	int i = 0;
	for (Player* player : Player::getPlayerList())
	{
		cout << "=========================================================" << endl;
		cout << "||       " << ++i << "      ||     " << player->getPlayerHand()->size() << "    ||     "
			<< player->getScore() << "     ||     " << player->getCoins() << "     ||" << endl;
	}

	cout << "=========================================================" << endl;
}

// Takes in an int and creates a turn object with the appropriate number of turns.
Turn* createTurns(int selectedMode, Map* map, Hand* hand)
{
	if (selectedMode == 1) {
		switch (Player::getPlayerNum())
		{
		case 2:
			return new Turn(13, map, hand);
		case 3:
			return new Turn(10, map, hand);
		case 4:
			return new Turn(8, map, hand);
		}
	}
	else 
		return new Turn(20, map, hand);
}

// Allows the player to select a map file that's currently available, and returns the file's name.
string chooseFile()
{
	int playerChoice;

	// Hard coded files.
	const int NUMBER_OF_VALID_MAPS = 4;
	string validMaps[NUMBER_OF_VALID_MAPS] = { "map1.txt", "map2.txt", "map3.txt","map4.txt" };

	// Player chooses a file.
	do
	{
		cout << "Please select a map: " << endl;

		for (int i = 1; i <= NUMBER_OF_VALID_MAPS; i++)
		{
			cout << "\t" << i << ") " << validMaps[i - 1] << endl;
		}

		cin >> playerChoice;

	} while (playerChoice < 1 || playerChoice > NUMBER_OF_VALID_MAPS);

	return validMaps[playerChoice - 1];
}

// Verifies file is in the correct format, creates a map based on file content, and then validates the map.
// Finally returns the mapLoader for further usage.
MapLoader* loadValidMap(string fileName)
{
	MapLoader* mapLoader = new MapLoader();

	// Creating map.
	if (!mapLoader->verifyFile(fileName))
	{
		std::cout << "ERROR! INVALID FILE!" << std::endl;
		exit(1);
	}

	mapLoader->readMapFile(fileName, Player::getPlayerNum());

	if (!mapLoader->getMap()->validate())
	{
		exit(1);
	}

	return mapLoader;
}

// Asks for the number of players.
// Creates them with the right amount of coins.
// And creates a bot if needed.
void createPlayers()
{
	int numOfPlayers;

	// Seeing how many players there are.
	do
	{
		cout << "Please enter the number of players in the game: ";
		cin >> numOfPlayers;
	} while (numOfPlayers <= 1 || numOfPlayers > 4);

	int coins = 0;
	string lName;

	//Determine number of coins allocated based on number of players
	if (numOfPlayers == 4) coins = 9;
	if (numOfPlayers == 3) coins = 11;
	if (numOfPlayers == 2) coins = 14;

	// Create all players. Can later be retrieved through the static method.
	for (int i = 1; i <= numOfPlayers; i++) {
		cout << "Player " << i << " last name: " << std::endl;
		cin >> lName;
		new Player(lName, coins, new HumanPlayer);
	}

	if (numOfPlayers == 2)
		new Player("BOT", 999, nullptr, true);
}

// Receives player input to change strategy.
void changePlayerStrategy(Player* player)
{
	char response = 'a';

	if (player->getStrategy() == nullptr || shouldChangeStrategy(player))
	{
		do
		{
			cout << "1) Human Player" << endl;
			cout << "2) Greedy Bot" << endl;
			cout << "3) Moderate Bot" << endl;
			cout << "Select a strategy: ";
			cin >> response;
		} while (response != '1' && response != '2' && response != '3');

		switch (response)
		{
		case '1':
			player->setStrategy(new HumanPlayer);
			break;
		case '2':
			player->setStrategy(new GreedyComputer);
			break;
		case '3':
			player->setStrategy(new ModerateComputer);
			break;
		}
	}
}

// Asks player if they should change strategy or not.
bool shouldChangeStrategy(Player* player)
{
	char response = 'a';

	do
	{
		cout << "Do you want to change " << player->getName() << "'s strategy? (y/n)";
		cin >> response;
	} while (response != 'y' && response != 'n');
	
	return response == 'y';

}
