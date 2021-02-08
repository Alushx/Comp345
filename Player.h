
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Territory.h"
#include "Map.h"
#include "BiddingFacility.h"

using namespace std;

class Player
{
	string name;
	int numOfCoins;
	Territory playerRegions[];
	Card playerHand[];
	BiddingFacility* bidFaci;
	Disk disks[];
	Army armies[];
	 
	
public:
	Player(string name, BiddingFacility* bidFaci);
	void PayCoin();
	void PlaceNewArmies(Territory* territory);
	void MoveArmies(Army* army, Territory* startLocation, Territory* endLocation);
	void MoveOverLand(Army* Territory* startLocation, Territory* endLocation);
	void BuildCity(Territory* territory);
	void DestroyArmy(Army* army);
};

#endif

