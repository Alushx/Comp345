
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Map.h"
#include "BiddingFacility.h"

using namespace std;

class Player
{
private:
	// Local variables.
	string name;
	int numOfCoins;
	Territory playerRegions[];
	Card playerHand[];
	BiddingFacility* bidFaci;
	Disk disks[];
	Army armies[];
	
public:
	Player(string name, BiddingFacility* bidFaci);
	~Player();
	void PayCoin();
	void PlaceNewArmies(Territory* territory);
	void MoveArmies(Army* army, Territory* startLocation, Territory* endLocation);
	void MoveOverLand(Army* army, Territory* startLocation, Territory* endLocation);
	void BuildCity(Territory* territory);
	void DestroyArmy(Army* army);

private:
	friend ostream& operator<<(ostream&, const Player&);

};

#endif

