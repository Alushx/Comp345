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