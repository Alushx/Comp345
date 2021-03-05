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
#include <iostream>
#include "Cards/Cards.h"
#include "BiddingFacility.h"
#include <sstream>
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

	// Handling static variables.
	playerNum++;
	playerList.push_back(this);
}

// Player value constructor.
Player::Player(string aName, int coinNum)
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
}

// Player copy constructor.
Player::Player(const Player& anotherPlayer)
{
	name = anotherPlayer.name;
	numOfCoins = anotherPlayer.numOfCoins;

	if (anotherPlayer.bidFaci)
		bidFaci = new BiddingFacility(*(anotherPlayer.bidFaci));
	else
		bidFaci = nullptr;

	// Shallow copy because the map is the same.
	for (Territory* territory : anotherPlayer.playerTerritory)
	{
		playerTerritory.push_back(territory);
	}

	for (Card* card : anotherPlayer.playerHand)
	{
		playerHand.push_back(new Card(*card));
	}

	for (City* city : anotherPlayer.cities)
	{
		cities.push_back(new City(*city));
	}

	for (Army* army : anotherPlayer.armies)
	{
		armies.push_back(new Army(*army));
	}

	numOfCubes = anotherPlayer.numOfCubes;
	numOfDisks = anotherPlayer.numOfDisks;
}

// Player destructor.
Player::~Player()
{
	// Cards and territories must be deallocated independently since they belong to all players.

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

vector<Player*>& Player::getPlayerList()
{
	return playerList;
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
	cout << *city << " is built in " << territory->getName();
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

// Plays the card and executes all its actions.
void Player::playCard(Card* aCard)
{
	if (!aCard)
	{
		cout << "ERROR! Dangling Passed! In Player::PlayCard()." << endl;
		exit(1);
	}

	string combinationType = aCard->getCombinationType();

	// No combination.
	if (combinationType == " ")
	{
		playCardAction(aCard->getFirstAction());
	}
	else
	{
		andOrAction(aCard, combinationType);
	}
}

// Handles and/or case.
void Player::andOrAction(Card* aCard, string& combinationType)
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
			playCardAction(aCard->getFirstAction());
		}
		else if (choiceNum == 2)
		{
			playCardAction(aCard->getSecondAction());
		}

	}
	// And case. Plays both actions.
	else if (combinationType == "AND")
	{
		playCardAction(aCard->getFirstAction());
		playCardAction(aCard->getSecondAction());
	}
}

// Executes the appropriate methods for the player action.
void Player::playCardAction(string anAction)
{
	istringstream actionStream(anAction);
	string keyWord = "";
	
	actionStream >> keyWord;

	// Handles all "Move X Armies" actions.
	if (keyWord == "Move")
	{
		int numOfArmiesToMove = 0;
		actionStream >> numOfArmiesToMove;
		moveArmiesAction(numOfArmiesToMove);
	}
	// Handles "Build City" action.
	else if (keyWord == "Build")
	{
		buildCityAction();
	}
	// Handles "Add X Armies" actions.
	else if (keyWord == "Add")
	{
		int numOfArmiesToCreate = 0;
		actionStream >> numOfArmiesToCreate;
		addArmiesAction(numOfArmiesToCreate);
	}
	// Handles "Destroy Army" action.
	else if (keyWord == "Destroy")
	{
		destroyArmyAction();
	}
}

// Moves all the armies in the action.
void Player::moveArmiesAction(int numOfArmiesToMove)
{
	Army* army = nullptr;
	Territory* endLocation = nullptr;

	// ? I should check for land/sky here, shouldn't I? And deduct the appropriate number of moves.

	// Moves an army for each number of moves a player has.
	for (int i = 0; i < numOfArmiesToMove; i++)
	{
		army = selectArmy();
		endLocation = selectNeighbouringTerritory(army->getPosition());
		moveArmies(army, endLocation);
	}
}

// Builds a city.
void Player::buildCityAction()
{
	Territory* position = selectTerritoryCurrentlyOn();
	buildCity(position);
}

// Creates the appropriate number of armies.
void Player::addArmiesAction(int numOfArmiesToAdd)
{
	// Adds an army according to the number of armies in the argument.
	Territory* position = nullptr;
	for (int i = 0; i < numOfArmiesToAdd; i++)
	{
		position = selectTerritoryWithCity();
		placeNewArmies(position);
	}
}

// Allows the player to select an enemy and one of its armies to destroy.
void Player::destroyArmyAction()
{
	Player* player = Player::selectPlayer();
	Army* army = player->selectArmy();

	destroyArmy(army);
}

// Returns a pointer to one of the players in the game.
Player* Player::selectPlayer()
{
	if (playerNum == 0)
	{
		cout << "There are no players to choose from." << endl;
		return nullptr;
	}


	int playerChoice = -1;

	// Lists all players and allows user to select which one.
	do
	{
		cout << "There are " << playerNum << " players." << endl;

		for (int i = 0; i < playerNum; i++)
		{
			cout << "\t " << (i + 1) << ") " << *playerList[i] << endl;
		}

		cout << "Select the player you want: ";
		cin >> playerChoice;

	} while (playerChoice < 1 || playerChoice > playerNum);

	// Returns pointer to player.
	return playerList[playerChoice - 1];
}

// Select one of the player's armies.
Army* Player::selectArmy()
{
	if (armies.size() == 0)
	{
		cout << "There are no armies to choose from." << endl;
		return nullptr;
	}

	int playerChoice = -1;
	int i = 0;

	// Prints all armies and allows player to select one.
	do
	{
		cout << name << " has " << armies.size() << " armies.";

		i = 0;
		for (Army* army : armies)
		{
			cout << "\t " << (i + 1) << ") " << *army << " in " << army->getPosition()->getName() << endl;
			i++;
		}

		cout << "Choose an army: ";
		cin >> playerChoice;
	} while (playerChoice > armies.size() || playerChoice <= 0);

	// Iterates over the list of armies to return the army.
	int j = 0;
	for (list<Army*>::iterator armyIterator = armies.begin(); armyIterator != armies.end(); armyIterator++)
	{
		j++;
		if (j == playerChoice)
		{
			return *armyIterator;
		}
	}

	return nullptr;
}

// Helps player choose a territory to build a city on.
Territory* Player::selectTerritoryCurrentlyOn()
{
	if (armies.size() == 0)
	{
		cout << "There are no territories to choose from." << endl;
		return nullptr;
	}

	map<Territory*, Territory*> territoriesCurrentlyOn = map<Territory*, Territory*>();
	
	// Make a set of all territories currently on.
	for (Army* army : armies)
	{
		territoriesCurrentlyOn[army->getPosition()] = army->getPosition();
	}

	int playerChoice = -1;
	int i = 0;
	Territory* territory = nullptr;

	// Prints all territories and allows player to select one.
	do
	{
		i = 0;

		for (pair<Territory*, Territory*> territoryPair : territoriesCurrentlyOn)
		{
			territory = territoryPair.first;
			cout << "\t " << (i + 1) << ") " << *territory << endl;
			i++;
		}

		// Player makes a choice.
		cout << "Choose a territory: ";
		cin >> playerChoice;

	} while (playerChoice > armies.size() || playerChoice <= 0);
	
	int j = 1;

	// Looping through and finding the territory again.
	for (pair<Territory*, Territory*> territoryPair : territoriesCurrentlyOn)
	{
		if (j == playerChoice)
		{
			return territoryPair.first;
		}
		j++;
	}

	// Returning null if nothing found.
	return nullptr;
}

// Helps player choose a territory to build an army on.
Territory* Player::selectTerritoryWithCity()
{
	int i = 0;
	int playerChoice = -1;
	
	// Display options for player.
	do
	{
		cout << "Choose one of the following territories with cities.";

		i = 1;

		cout << "\t 1) Starting Region" << endl;

		for (City* city : cities)
		{
			cout << "\t " << (++i) << ") " << *(city->getPosition()) << endl;
		} 
	} while (playerChoice <= 0 || playerChoice > (cities.size() + 1));

	// Special case when starting region is selected.
	if (playerChoice == 1)
	{
		return getStartingRegion();
	}
	
	int j = 2; // Other cities start from 2 in the player's eyes.

	// Loops through list and returns the appropriate position.
	for (City* city : cities)
	{
		if (playerChoice == j++)
		{
			return city->getPosition();
		}
	}

	cout << "\n DEBUG Player::selectTerritoryWithCity() - city not found. j = " << j << endl;
	return nullptr;
}

// Helps player choose a territory to move an army to.
Territory* Player::selectNeighbouringTerritory(Territory* currentTerritory)
{
	// TODO implement this.
	return nullptr;
}



// toString
ostream& operator<<(ostream& strm, const Player& player)
{
	return strm << player.name << ": " << player.numOfCoins << " coins" << " : " << player.armies.size() << " armies";
}

Player& Player::operator= (const Player& anotherPlayer)
{
	if (&anotherPlayer == this)
		return *this;

	name = anotherPlayer.name;
	numOfCoins = anotherPlayer.numOfCoins;

	if (anotherPlayer.bidFaci)
		bidFaci = new BiddingFacility(*(anotherPlayer.bidFaci));
	else
		bidFaci = nullptr;

	// Shallow copy because the map is the same.
	for (Territory* territory : anotherPlayer.playerTerritory)
	{
		playerTerritory.push_back(territory);
	}

	for (Card* card : anotherPlayer.playerHand)
	{
		playerHand.push_back(new Card(*card));
	}

	for (City* city : anotherPlayer.cities)
	{
		cities.push_back(new City(*city));
	}

	for (Army* army : anotherPlayer.armies)
	{
		armies.push_back(new Army(*army));
	}

	numOfCubes = anotherPlayer.numOfCubes;
	numOfDisks = anotherPlayer.numOfDisks;

	return *this;
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

// Default constructor.
City::City()
{
	owner = nullptr;
	position = nullptr;
}

// City constructor.
City::City(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

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