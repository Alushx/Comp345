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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Map.h"
#include "BiddingFacility.h"

using std::string;

// Forward declarations to make compiler happy.
class Army;
class City;
class Card;
class BiddingFacility;
class PlayerStrategies;

// Player class.
class Player
{

private:
	// Member variables.
	string name;
	int numOfCoins;
	int numOfCubes;
	int numOfDisks;
	BiddingFacility* bidFaci;
	list<Territory*> playerTerritory;
	list<Card*> playerHand;
	list<City*> cities;
	list<Army*> armies;
	int score;
	int ownNumElixer;
	PlayerStrategies* strategy;

	// Static variables.
	static vector<Player*> playerList;
	static int playerNum;
	static Territory* startingRegion;
	static Player* bot;

public:

	// Constructors and destructors.
	Player();
	Player(string name, int coinNum, PlayerStrategies* aStrategy = nullptr, bool isBot = false);
	Player(const Player&);
	~Player();

	// Service methods.
	bool payCoin(int& cost);
	void placeNewArmies(Territory* territory);
	void moveArmies(Army*, Territory*);
	void moveOverLand(Army*, Territory*);
	void moveOverWater(Army*, Territory*);
	void buildCity(Territory* territory);
	void destroyArmy(Army*);
	void addCard(Card*);
	Player* computeScore(Map* map);
	void playCard(Card*, Map*);
	int computeContinentsOwned(Map*);

	// Accessors.
	string getName();
	int getCoins();
	int getNumOfCubes();
	int getNumOfDisks();
	BiddingFacility* getBidFaci() const;
	list<Territory*>* getPlayerTerritories();
	list<Card*>* getPlayerHand();
	list<City*>* getCities();
	list<Army*>* getArmies();
	int getScore();
	int getOwnNumElixer();
	PlayerStrategies* getStrategy();

	// Mutators.
	void setName(string n);
	void setCoins(int c);
	void setNumOfCubes(int);
	void setNumOfDisks(int);
	void setBidFaci(BiddingFacility*);
	void setOwnNumElixer(int numElixer);
	void setStrategy(PlayerStrategies*);

	// Operators.
	friend ostream& operator<<(ostream&, const Player&);
	Player& operator= (const Player&);

	// Static methods.
	static Player* getBot();
	static void setBot(Player*);
	static void placeBotArmies(int, Map*);
	static int getPlayerNum();
	static vector<Player*>& getPlayerList();
	static void setStartingRegion(Territory*);
	static Territory* getStartingRegion();
	static Player* announcement(vector<Player*> player);
	static Player* computeElixerScore();

private:
	// Helping methods.
	void andOrAction(Card*, string&, Map*);
	void playCardAction(string, Map*);
	void moveArmiesAction(int, Map*);
	void buildCityAction();
	void addArmiesAction(int);
	void destroyArmyAction();
	int calculateMoveBonus();
	int calculateArmyBonus();
	int calculateFlightBonus();
	bool calculateImmunityBonus();
};

class Army
{
// Local variables.
private:
	Player* owner;
	Territory* position;

// Public methods.
public:
	// Constructors and destructors.
	Army();
	Army(Player*, Territory*);
	Army(const Army&);
	~Army();
	// Useful methods.
	string getOwnerName();
	Player* getOwner();
	Territory* getPosition();
	void setPosition(Territory*);
	Army& operator=(Army&);

// Operators.
private:
	friend ostream& operator<<(ostream&, const Army&);
};

class City
{
	Player* owner;
	Territory* position;
	// Public methods.
public:
	// Constructors and destructors.
	City();
	City(Player*, Territory*);
	City(const City&);
	~City();
	// Useful methods.
	string getOwnerName();
	Player* getOwner();
	Territory* getPosition();
	City& operator=(City&);

	// Operators.
private:
	friend ostream& operator<<(ostream&, const City&);
};
#endif

