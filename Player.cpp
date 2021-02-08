#include "Player.h"

Player::Player(string name, BiddingFacility* biddingFaci)
{
	this->name = name;
	this->bidFaci = biddingFaci;
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

void Player::MoveArmies(Army* army, Territory* startLocation, Territory* endLocation)
{
	// Validate if you can move.
	// Move if possible.
	// Throw exception or something if invalid.
}

void Player::MoveOverLand(Army* army, Territory* startLocation, Territory* endLocation)
{
	// Validate if you can move.
	// Move if possible.
	// Throw exception or something if invalid.
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