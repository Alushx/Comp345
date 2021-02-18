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

// Player class.
class Player
{
// Local variables.
private:
	string name;
	int numOfCoins;
	BiddingFacility* bidFaci;
	list<Territory*> playerTerritory;
	list<Card*> playerHand;
	list<City*> cities;
	list<Army*> armies;

// Public methods
public:
	// Constructors and destructors.
	Player();
	Player(string name, int coinNum);
	Player(Player&);
	~Player();

	// Methods.
	bool payCoin(int& cost);
	void placeNewArmies(Territory* territory);
	void moveArmies(Army*, Territory*);
	void moveOverLand(Army*, Territory*);
	void buildCity(Territory* territory);
	void destroyArmy(Army*);
	string getName();
	void setName(string n);
	int getCoins();
	void setCoins(int c);
	BiddingFacility* getBidFaci() const;
	list<Army*>* getArmies();
	Player& operator= (const Player&);

// Operators
private:
	friend ostream& operator<<(ostream&, const Player&);

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
	Army(Army&);
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
	City(City&);
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

