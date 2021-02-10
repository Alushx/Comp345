
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Map.h"
#include "Cards.h"
#include "BiddingFacility.h"

using std::cout;
using std::string;

// Forward declarations to make compiler happy.
class Army;
class City;

// Player class.
class Player
{
// Local variables.
private:
	string name;
	int numOfCoins;
	list<Territory*> playerTerritory;
	list<Card*> playerHand;
	BiddingFacility* bidFaci;
	list<City*> cities;
	list<Army*> armies;

// Public methods
public:
	Player(string name, BiddingFacility* bidFaci);
	~Player();
	void PayCoin();
	void PlaceNewArmies(Territory* territory);
	void MoveArmies(Army*, Territory*);
	void MoveOverLand(Army*, Territory*);
	void BuildCity(Territory* territory);
	void DestroyArmy(Army*);
	string GetName();
	list<Army*>* GetArmies();

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
	Army(Player*, Territory*);
	~Army();
	string GetOwnerName();
	Player* GetOwner();
	Territory* GetPosition();
	void SetPosition(Territory*);

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
	City(Player*, Territory*);
	~City();
	string GetOwnerName();
	Player* GetOwner();
	Territory* GetPosition();

	// Operators.
private:
	friend ostream& operator<<(ostream&, const City&);
};
#endif

