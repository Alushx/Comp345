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

#include "Player.h"
#include "PlayerStrategies.h"
#include <iostream>
#include "Cards.h"
#include "BiddingFacility.h"
#include "Map.h"
#include <sstream>
#include <algorithm>
using namespace std;

// ============================================
// Player Implementation
// ============================================

// Player default constructor.
Player::Player()
{
	name = "Odysseus";
	numOfCoins = 0;
	bidFaci = new BiddingFacility();
	playerTerritory = list<Territory*>();
	playerHand = list<Card*>();
	cities = list<City*>();
	armies = list<Army*>();
	numOfCubes = 18;
	numOfDisks = 3;
	strategy = nullptr;

	// Handling static variables.
	playerNum++;
	playerList.push_back(this);
}

// Player value constructor.
Player::Player(string aName, int coinNum, PlayerStrategies* aStrategy, bool isBot)
{
	name = aName;
	numOfCoins = coinNum;
	bidFaci = new BiddingFacility();
	playerTerritory = list<Territory*>();
	playerHand = list<Card*>();
	cities = list<City*>();
	armies = list<Army*>();
	numOfCubes = 18;
	numOfDisks = 3;
	score = 0; 
	ownNumElixer = 0;
	strategy = aStrategy;

	// Handling static variables.
	if (isBot)
	{
		Player::setBot(this);
	}
	else
	{
		playerNum++;
		playerList.push_back(this);
	}
}

// Player copy constructor.
Player::Player(const Player& anotherPlayer)
{
	// Copying member variables.
	name = anotherPlayer.name;
	numOfCoins = anotherPlayer.numOfCoins;
	numOfCubes = anotherPlayer.numOfCubes;
	numOfDisks = anotherPlayer.numOfDisks;
	score = anotherPlayer.score;
	ownNumElixer = anotherPlayer.ownNumElixer;
	strategy = anotherPlayer.strategy;

	if (anotherPlayer.bidFaci != NULL)
		bidFaci = new BiddingFacility(*(anotherPlayer.bidFaci));
	else
		bidFaci = nullptr;

	// Shallow copy because the map/cards are the same.
	for (Territory* territory : anotherPlayer.playerTerritory)
	{
		playerTerritory.push_back(territory);
	}

	for (Card* card : anotherPlayer.playerHand)
	{
		playerHand.push_back(card);
	}

	for (City* city : anotherPlayer.cities)
	{
		cities.push_back(new City(this, city->getPosition()));
	}

	for (Army* army : anotherPlayer.armies)
	{
		armies.push_back(new Army(this, army->getPosition()));
	}

	// Handling static variables.
	playerNum++;
	playerList.push_back(this);
}

// Player destructor.
Player::~Player()
{
	// Cards and territories must be deallocated independently since they belong to all players.
	delete strategy;

	if (bidFaci)
	{
		delete bidFaci;
		bidFaci = nullptr;
	}

	// Deallocating all cities.
	for (list<City*>::iterator iter = cities.begin(); iter != cities.end(); ++iter)
	{
		City* tempCity = *iter;
		delete tempCity;
		tempCity = nullptr;
	}

	// Deallocating all armies.
	for (list<Army*>::iterator iter = armies.begin(); iter != armies.end(); ++iter)
	{
		Army* tempArmy = *iter;
		delete tempArmy;
		tempArmy = nullptr;
	}
}

// Initializing static variable.
int Player::playerNum = 0;
vector<Player*> Player::playerList = vector<Player*>();
Territory* Player::startingRegion = nullptr;
Player* Player::bot = nullptr;

// Set the starting region that all players share.
void Player::setStartingRegion(Territory* aStartingRegion)
{
	startingRegion = aStartingRegion;
}

// Get the starting region shared by all players.
Territory* Player::getStartingRegion()
{
	return startingRegion;
}

// Returns the number of players currently playing.
int Player::getPlayerNum()
{
	return playerNum;
}

// Returns a list of all non-bot players.
vector<Player*>& Player::getPlayerList()
{
	return playerList;
}

// Returns the last created bot.
Player* Player::getBot()
{
	return bot;
}

// Sets a player to be a bot.
void Player::setBot(Player* aBot)
{
	bot = aBot;
}

//Set the number of Elixer a player own 
void Player :: setOwnNumElixer(int numElixer) {
	ownNumElixer = numElixer;
}

//Returns the number of Elixer that a player own
int Player :: getOwnNumElixer() {
	return ownNumElixer;
}
int Player :: getScore() {
	return score;
}

PlayerStrategies* Player::getStrategy()
{
	return strategy;
}

// Sets a strategy. Automatically deallocates memory of the previous one.
void Player::setStrategy(PlayerStrategies* aStrategy)
{
	if (strategy != nullptr)
		delete strategy;
	strategy = aStrategy;
}

void Player::placeBotArmies(int n, Map* map)
{
	if (map == NULL || getBot() == NULL)
	{
		cout << "ERROR!" << endl;
		exit(1);
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << "You can place " << n - i << " armies." << std::endl;
		Territory* territory = map->selectTerritory();
		getBot()->placeNewArmies(territory);
	}
}

// Switched Pay coin into a boolean type 
// Pay coin.
bool Player::payCoin(int& cost)
{
	if (this->numOfCoins >= cost)
	{
		numOfCoins = numOfCoins - cost;
		cout << this->name << " has now " << this->numOfCoins << endl;
		return true;
	}
	else
	{
		cout << this->name + " doesn't have enough coins " << endl;
		return false;
	}
}

// Territory getter
list<Territory*>* Player::getPlayerTerritories()
{
	return &playerTerritory;
}

// Adds a card to the player's personal hand.
void Player::addCard(Card* card)
{
	playerHand.push_back(card);
}


// Creates new army.
void Player::placeNewArmies(Territory* territory)
{
	if (numOfCubes <= 0)
	{
		cout << name << " does not have enough cubes to place a new army." << endl;
		return;
	}
	Army* army = new Army(this, territory);
	territory->addArmy(army);
	armies.push_back(army);
	cout << "Created " << *army << " in " << territory->getName() << endl;
	army = nullptr;
	numOfCubes--;
}

// Moves army. Should work for both land and water.
void Player::moveArmies(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->getPosition();
	oldPos->removeArmy(army);
	army->setPosition(endLocation);
	endLocation->addArmy(army);
	cout << "Moved " << *army << " from " << oldPos->getName() << " to " << endLocation->getName() << endl;
	oldPos = nullptr;
}

// Moves army over land.
void Player::moveOverLand(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->getPosition();
	oldPos->removeArmy(army);
	army->setPosition(endLocation);
	endLocation->addArmy(army);
	cout << "Moved " << *army << " overland from " << oldPos->getName() << " to " << endLocation->getName() << endl;
	oldPos = nullptr;
}

// Moves the army over land.
void Player::moveOverWater(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->getPosition();
	oldPos->removeArmy(army);
	army->setPosition(endLocation);
	endLocation->addArmy(army);
	cout << "Moved " << *army << " over water from " << oldPos->getName() << " to " << endLocation->getName() << endl;
}

// Creates a city on the territory. Is not currently functional because we have no idea of what a city is.
void Player::buildCity(Territory* territory)
{
	if (numOfDisks <= 0)
	{
		cout << name << " does not have enough disks to place a new city." << endl;
		return;
	}
	City* city = new City(this, territory);
	this->cities.push_back(city);
	cout << *city << " is built in " << territory->getName() << endl;
	city = nullptr;
	numOfDisks--;
}

// Destroys army and deallocates dynamic memory.
void Player::destroyArmy(Army* army)
{
	army->getPosition()->removeArmy(army);
	army->getOwner()->armies.remove(army);
	cout << *army << " is destroyed!";
	delete army;
	army = nullptr;
}

// Returns player name.
string Player::getName()
{
	return name;
}

void Player::setName(string n) {
	name = n;
}

int Player::getCoins() {
	return numOfCoins;
}

void Player::setCoins(int c) {
	numOfCoins = c;
}

BiddingFacility* Player::getBidFaci() const { 
	return bidFaci;
}

// Returns list of player armies.
list<Army*>* Player::getArmies()
{
	return &armies;
}

// Accessor for the number of cubes (army tokens) a player has.
int Player::getNumOfCubes()
{
	return numOfCubes;
}

// Accessor for the number of disks (city tokens) a player has.
int Player::getNumOfDisks()
{
	return numOfDisks;
}

// Returns a pointer to the player's hand (list of cards).
list<Card*>* Player::getPlayerHand()
{
	return &playerHand;
}

// Returns a pointer to the list of cities owned by the player.
// Not to be confused with the territories.
list<City*>* Player::getCities()
{
	return &cities;
}

// Mutator to change the number of cubes (army tokens) a player has.
void Player::setNumOfCubes(int newNumOfCubes)
{
	numOfCubes = newNumOfCubes;
}

// Mutator to change the number of disks (city tokens) a player has.
void Player::setNumOfDisks(int newNumOfDisks)
{
	numOfDisks = newNumOfDisks;
}

// Assigns a new bidding facility to the player.
// Note that the user of this method is responsible for 
// deallocating the memory of the old bidding facility.
void Player::setBidFaci(BiddingFacility* newBiddingFacility)
{
	bidFaci = newBiddingFacility;
}


// Plays the card and executes all its actions.
void Player::playCard(Card* aCard, Map* map)
{
	if (aCard == NULL)
	{
		cout << "ERROR! Dangling Passed! In Player::PlayCard()." << endl;
		exit(1);
	}

	string combinationType = aCard->getCombinationType();

	// No combination.
	if (combinationType == " ")
	{
		playCardAction(aCard->getFirstAction(), map);
	}
	else
	{
		andOrAction(aCard, combinationType, map);
	}
}

// Handles and/or case.
void Player::andOrAction(Card* aCard, string& combinationType, Map* map)
{
	if (!aCard)
	{
		cout << "ERROR! Dangling Passed! In Player::AndOrAction()." << endl;
		exit(1);
	}
	
	// Or case.
	if (combinationType == "OR")
	{
		int choiceNum = 0;

		// Player makes a decision.
		do
		{
			cout << "Which of the following actions would you like to take?" << endl;
			cout << "\t 1) " << aCard->getFirstAction() << endl;
			cout << "\t 2) " << aCard->getSecondAction() << endl;

			cin >> choiceNum;

		} while (!(choiceNum == 1 || choiceNum == 2));
		
		// Appropriate action is played.

		if (choiceNum == 1)
		{
			playCardAction(aCard->getFirstAction(), map);
		}
		else if (choiceNum == 2)
		{
			playCardAction(aCard->getSecondAction(), map);
		}

	}
	// And case. Plays both actions.
	else if (combinationType == "AND")
	{
		playCardAction(aCard->getFirstAction(), map);
		playCardAction(aCard->getSecondAction(), map);
	}
}

// Executes the appropriate methods for the player action.
void Player::playCardAction(string anAction, Map* map)
{
	istringstream actionStream(anAction);
	string keyWord = "";
	
	actionStream >> keyWord;

	// Handles all "Move X Armies" actions.
	if (keyWord == "Move")
	{
		cout << endl;
		cout << name << " is moving armies..." << endl;
		int numOfArmiesToMove = 0;
		actionStream >> numOfArmiesToMove;
		moveArmiesAction(numOfArmiesToMove, map);
	}
	// Handles "Build City" action.
	else if (keyWord == "Build")
	{
		cout << endl;
		cout << name << " is building a city..." << endl;
		buildCityAction();
	}
	// Handles "Add X Armies" actions.
	else if (keyWord == "Add")
	{
		cout << endl;
		cout << name << " is adding armies..." << endl;
		int numOfArmiesToCreate = 0;
		actionStream >> numOfArmiesToCreate;
		addArmiesAction(numOfArmiesToCreate);
	}
	// Handles "Destroy Army" action.
	else if (keyWord == "Destroy")
	{
		cout << endl;
		cout << name << " is destroying an army..." << endl;
		destroyArmyAction();
	}
}

// Moves all the armies in the action.
void Player::moveArmiesAction(int numOfArmiesToMove, Map* map)
{
	Army* army = nullptr;
	pair<Territory*, int> endLocation;

	numOfArmiesToMove += calculateMoveBonus();

	// Moves an army for each number of moves a player has.
	while (numOfArmiesToMove > 0)
	{
		cout << endl;
		cout << name << " has " << numOfArmiesToMove << " moves left..." << endl;
		army = strategy->selectArmy(armies);
		endLocation = strategy->selectNeighbouringTerritory(army->getPosition(), map);

		int flightBonus = calculateFlightBonus();
		int moveCost = max(endLocation.second - flightBonus, 1);

		// Check if player has the needed number of moves.
		if (moveCost > numOfArmiesToMove)
		{
			cout << "Invalid move. You do not have enough moves for that. Please pick again." << endl;
		}
		else
		{
			// Move army and deduct cost.
			moveArmies(army, endLocation.first);
			numOfArmiesToMove -= moveCost;
		}
		
	}
}

// Builds a city.
void Player::buildCityAction()
{
	Territory* position = strategy->selectTerritoryCurrentlyOn(armies);
	buildCity(position);
}

// Creates the appropriate number of armies.
void Player::addArmiesAction(int numOfArmiesToAdd)
{
	// Adds an army according to the number of armies in the argument.
	Territory* position = nullptr;
	numOfArmiesToAdd += calculateArmyBonus();

	for (int i = 0; i < numOfArmiesToAdd; i++)
	{
		cout << endl;
		cout << name << " has " << numOfArmiesToAdd - i<< " armies left to add..." << endl;
		position = strategy->selectTerritoryWithCity(cities);
		placeNewArmies(position);
	}
}

// Allows the player to select an enemy and one of its armies to destroy.
void Player::destroyArmyAction()
{
	bool isImmune = false;
	Player* player = nullptr;

	do
	{
		player = strategy->selectPlayer();
		isImmune = player->calculateImmunityBonus();
	} while (isImmune);
	
	Army* army = player->getStrategy()->selectArmy(*(player->getArmies()));

	destroyArmy(army);
}

// Iterates over all cards in the player hand and counts the 
// total move bonus the player gets from all cards.
// This is the extra moves a player gets whenever they play a "Move Army" card.
int Player::calculateMoveBonus()
{
	int moveBonus = 0; 

	for (Card* card : playerHand)
	{
		if (card->getAbility() == "+1 Move")
			moveBonus++;
	}

	cout << "\n Player has " << moveBonus << " bonus moves... \n" << endl;

	return moveBonus;
}

// Iterates over all cards in the player hand and counts the number of 
// extra armies a player can create whenever they play a "Create Army" card.
int Player::calculateArmyBonus()
{
	int armyBonus = 0;

	for (Card* card : playerHand)
	{
		if (card->getAbility() == "+1 Army")
			armyBonus++;
	}

	cout << "Player has " << armyBonus << " bonus armies... \n" << endl;

	return armyBonus;
}

// Iterates over all cards in the player hand and counts the total flight 
// bonus a player has. Each one reduces an overseas move cost down to a minimum of 1.
int Player::calculateFlightBonus()
{
	int flightBonus = 0;

	for (Card* card : playerHand)
	{
		if (card->getAbility() == "Flying")
			flightBonus++;
	}

	cout << "Player has " << flightBonus << " bonus flight... \n" << endl;

	return flightBonus;
}

// Returns true if the player has a card that grants them 
// immunity to attacks. Returns false otherwise.
bool Player::calculateImmunityBonus()
{
	bool isImmune = false;
	for (Card* card : playerHand)
	{
		// Immediately exit and return true.
		if (card->getAbility() == "Immune to attack")
		{
			cout << "Cannot attack this player! They are immune...\n" << endl;
			isImmune = true;
			return isImmune;
		}
	}

	// Return false otherwise.
	return false;
}

// toString
ostream& operator<<(ostream& strm, const Player& player)
{
	return strm << player.name << ": " << player.numOfCoins << " coins" << " : " << player.armies.size() << " armies";
}

// Overloaded assignment operator.
Player& Player::operator= (const Player& anotherPlayer)
{
	// Self check.
	if (&anotherPlayer == this)
		return *this;

	name = anotherPlayer.name;
	numOfCoins = anotherPlayer.numOfCoins;
	score = anotherPlayer.score;
	ownNumElixer = anotherPlayer.score;
	numOfCubes = anotherPlayer.numOfCubes;
	numOfDisks = anotherPlayer.numOfDisks;

	if (anotherPlayer.bidFaci != NULL)
		bidFaci = new BiddingFacility(*(anotherPlayer.bidFaci));
	else
		bidFaci = nullptr;

	// Shallow copy because the map/deck is the same.
	for (Territory* territory : anotherPlayer.playerTerritory)
	{
		playerTerritory.push_back(territory);
	}

	for (Card* card : anotherPlayer.playerHand)
	{
		playerHand.push_back(card);
	}

	for (City* city : anotherPlayer.cities)
	{
		cities.push_back(new City(this, city->getPosition()));
	}

	for (Army* army : anotherPlayer.armies)
	{
		armies.push_back(new Army(this, army->getPosition()));
	}
	strategy = anotherPlayer.strategy;

	return *this;
}

//player with the most elixers gains 2 extra victory points.
Player* Player::computeElixerScore() {
	Player* winner = nullptr;
	for (Player* playerChar : Player::getPlayerList())
	{
		if (winner == nullptr)
			winner = playerChar;
		else if (winner->getOwnNumElixer() > playerChar->getOwnNumElixer())
			continue;
		else if (winner->getOwnNumElixer() < playerChar->getOwnNumElixer())
			winner = playerChar;
	}
	winner->score += 2;
	return winner;
}


//Returns the scrore of each player
Player* Player::computeScore( Map* map) {
	
	// Resetting values for computation.
	score = 0;
	playerTerritory.clear();

	// Assigning owned territories.
	for (pair<string, Territory*> territoryPair : map->getTerritories())
	{
		if (this == territoryPair.second->getOwner())
			playerTerritory.push_back(territoryPair.second);
	}
	score = score + this->playerTerritory.size();

	// Computing the score for continents.
	score += computeContinentsOwned(map);

	// Computing the score for cards.
	for (Card* card : this->playerHand)
	{
		score = score + card->getCardScore(playerHand, this);
	}

	return this;
}

// Winner Annocement 
Player* Player::announcement(vector<Player*> player) 
{
	Player* winner = nullptr;
	int conqueredTerritoriesW = NULL;
	int conqueredTerritoriesP = NULL;
	for (Player* player : player)
	{
		if (winner == nullptr)
			winner = player;
		else if (winner->score > player->score)
			continue;
		else if (winner->score < player->score)
			winner = player;
		else
		{
			cout << winner->name << " and " << player->name << " have the same score" << endl;
			
			if (winner->numOfCoins > player->numOfCoins)
				continue;
			else if (winner->numOfCoins < player->numOfCoins)
				winner = player;
			else 
			{
				cout << winner->name << " and " << player->name << " have the same score even with the coin count" << endl;
				if (winner->numOfCubes < player->numOfCubes)
					continue;
				else if (winner->numOfCubes > player->numOfCubes)
					winner = player;
				else 
				{
					cout << winner->name << " and " << player->name << " have the same score, number of coin " 
						<< "and same number of armies" << endl;

					// Calculate the number of the conquered terrotories
					conqueredTerritoriesW = winner->getPlayerTerritories()->size();
					conqueredTerritoriesP = player->getPlayerTerritories()->size();
					if (conqueredTerritoriesW > conqueredTerritoriesP)
						continue;
					else if (conqueredTerritoriesW < conqueredTerritoriesP)
						winner = player;
					else
					{
						cout << "This match is an absolute tie" << endl;
						return winner->name > player->name ? winner : player;
					}
				}
			}
		}		
	}
	return winner;
}

// Counts the number of continents owned by this player.
int Player::computeContinentsOwned(Map* map)
{
	int numOfContinents = 0;
	list<list<Territory*>> continents = map->getContinents();
	for (list<Territory*> continent : continents)
	{
		if (map->getContinentOwner(continent) == this)
			numOfContinents++;
	}

	return numOfContinents;
}


// ============================================
// Army Implementation
// ============================================

// Default constructor.
Army::Army()
{
	owner = nullptr;
	position = nullptr;
}

// Army constructor.
Army::Army(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

// Copy constructor.
Army::Army(const Army& anotherArmy)
{
	// Shallow copies because the owner and position will the same.
	if (anotherArmy.owner)
	{
		owner = anotherArmy.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherArmy.position)
	{
		position = anotherArmy.position;
	}
	else
	{
		position = nullptr;
	}
}

// Army destructor.
Army::~Army()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string Army::getOwnerName()
{
	return (*owner).getName();
}

// Returns pointer to owner.
Player* Army::getOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* Army::getPosition()
{
	return position;
}

// Changes position.
void Army::setPosition(Territory* newPosition)
{
	position = newPosition;
}

// Army's toString
ostream& operator<<(ostream& strm, const Army& army)
{
	return strm << army.owner->getName() << "'s army";
}

// Assignment operator overload.
Army& Army::operator=(Army& anotherArmy)
{
	if (&anotherArmy == this)
		return *this;

	// Shallow copies because the owner and position will the same.
	if (anotherArmy.owner)
	{
		owner = anotherArmy.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherArmy.position)
	{
		position = anotherArmy.position;
	}
	else
	{
		position = nullptr;
	}

	return *this;
}

// ============================================
// City Implementation
// ============================================

// City Default constructor.
City::City()
{
	owner = nullptr;
	position = nullptr;
}

// City value constructor.
City::City(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

// City copy constructor.
City::City(const City& anotherCity)
{
	// Shallow copies because the owner and position will the same.
	if (anotherCity.owner)
	{
		owner = anotherCity.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherCity.position)
	{
		position = anotherCity.position;
	}
	else
	{
		position = nullptr;
	}
}

// City destructor.
City::~City()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string City::getOwnerName()
{
	return owner->getName();
}

// Returns pointer to owner.
Player* City::getOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* City::getPosition()
{
	return position;
}

// City's toString
ostream& operator<<(ostream& strm, const City& city)
{
	return strm << city.owner->getName() << "'s city";
}

// Assignment operator overload.
City& City::operator=(City& anotherCity)
{
	if (&anotherCity == this)
		return *this;

	// Shallow copies because the owner and position will the same.
	if (anotherCity.owner)
	{
		owner = anotherCity.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherCity.position)
	{
		position = anotherCity.position;
	}
	else
	{
		position = nullptr;
	}

	return *this;
}