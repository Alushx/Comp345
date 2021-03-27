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

//Deallocate maploader, deck and Player
void deallocateResources(MapLoader* mapLoader, Deck* deck) {
	delete mapLoader;
	delete deck;

	vector<Player*> players = Player::getPlayerList();
	for (int i = 0; i < Player::getPlayerNum(); i++)
	{
		delete players[i];
	}
	if (Player::getBot() != NULL)
		delete Player::getBot();
}

//Determine the bid winner
void selectBidWinner() {
	int bidWinner = -1;
	bidWinner = BiddingFacility::biddingPhase(Player::getPlayerList());
	Player::getPlayerList()[bidWinner];
	// return player.
}

//Create the deck: generate it, shuffle it and print it.
void createDeck(Deck *deck) {
	deck->generateDeck();
	deck->shuffleDeck();
	deck->printDeck();
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
	for (Player* playerChar : Player::getPlayerList())
	{
		playerChar->computeScore(mapLoader->getMap());
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
    MapLoader* mapLoader = new MapLoader();
    int numOfPlayers;
    int playerChoice;
    string fileName;

    // Hard coded.
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

    fileName = validMaps[playerChoice - 1];
    
    // Seeing how many players there are.
    do
    {
        cout << "\n Please enter the number of players in the game: ";
        cin >> numOfPlayers;
    } while (numOfPlayers <= 1 || numOfPlayers > 4);

    // Creating map.
    if (!mapLoader->verifyFile(fileName))
    {
        std::cout << "ERROR! INVALID FILE!" << std::endl;
        exit(1);
    }

    mapLoader->readMapFile(fileName, numOfPlayers);

    if (!mapLoader->getMap()->validate())
    {
        exit(1);
    }

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
        new Player(lName, coins);
    }

    if (numOfPlayers == 2)
        new Player("BOT", 999, true);

    // Armies, tokens, cities, and bidding facility is all created within each instance of Player.
    return mapLoader;
}