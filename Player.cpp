#include "Player.h"

// ============================================
// Player Implementation
// ============================================

Player::Player(string name, BiddingFacility* biddingFaci)
{
	this->name = name;
	this->bidFaci = biddingFaci;
}

Player::~Player()
{
	// Depends on implementation.
}

void Player::PayCoin()
{
	if (this->numOfCoins > 0)
	{
		numOfCoins--;
		// Do action.
	}
	else
	{
		// Exceptions.
	}
}

void Player::PlaceNewArmies(Territory* territory)
{
	// Create new army.
	// Check if territory is available.
	// Place in territory.
	// add army to armies;
}

void Player::MoveArmies(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->GetPosition();
	oldPos->RemoveArmy(army);
	army->SetPosition(endLocation);
	endLocation->AddArmy(army);
}

void Player::MoveOverLand(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->GetPosition();
	oldPos->RemoveArmy(army);
	army->SetPosition(endLocation);
	endLocation->AddArmy(army);
}

void Player::BuildCity(Territory* territory)
{
	// Build city on territory.
}

void Player::DestroyArmy(Army* army)
{
	// Remove army from armies;
	// delete army;
	// army = nullptr;
}

string Player::GetName()
{
	return name;
}

ostream& operator<<(ostream& strm, const Player& player)
{
	return strm << player.name << ": " << player.numOfCoins << " coins.";
}

// ============================================
// Army Implementation
// ============================================

Army::Army(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

Army::~Army()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

string Army::GetOwnerName()
{
	return (*owner).GetName();
}

Territory* Army::GetPosition()
{
	return position;
}

void Army::SetPosition(Territory* newPosition)
{
	position = newPosition;
}