#include "Player.h"

// ============================================
// Player Implementation
// ============================================

// Player value constructor.
Player::Player(string aName, BiddingFacility* aBiddingFaci)
{
	name = aName;
	bidFaci = aBiddingFaci;
}

// Player destructor.
Player::~Player()
{
	// Depends on implementation.
}

// Pay coin.
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

// Creates new army.
void Player::PlaceNewArmies(Territory* territory)
{
	Army* army = new Army(this, territory);
	territory->AddArmy();
	armies.push_back(army);
	army = nullptr;
	cout << "Created " << *army << " in " << *territory << endl;
}

// Moves army. Should work for both land and water.
void Player::MoveArmies(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->GetPosition();
	oldPos->RemoveArmy();
	army->SetPosition(endLocation);
	endLocation->AddArmy();
	cout << "Moved " << *army << " from " << *oldPos << " to " << *endLocation << endl;
	oldPos = nullptr;
}

// Moves army over land.
void Player::MoveOverLand(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->GetPosition();
	oldPos->RemoveArmy();
	army->SetPosition(endLocation);
	endLocation->AddArmy();
	cout << "Moved " << *army << " overland from " << *oldPos << " to " << *endLocation << endl;
	oldPos = nullptr;
}

// Creates a city on the territory. Is not currently functional because we have no idea of what a city is.
void Player::BuildCity(Territory* territory)
{
	City* city = new City(this, territory);
	this->cities.push_back(city);
	cout << *city << " is built in " << *territory;
	city = nullptr;
}

// Destroys army and deallocates dynamic memory.
void Player::DestroyArmy(Army* army)
{
	army->GetPosition()->RemoveArmy();
	army->GetOwner()->armies.remove(army);
	cout << *army << " is destroyed!";
	delete army;
	army = nullptr;
}

// Returns player name.
string Player::GetName()
{
	return name;
}

// Returns list of player armies.
list<Army*>* Player::GetArmies()
{
	return &armies;
}

// toString
ostream& operator<<(ostream& strm, const Player& player)
{
	return strm << player.name << ": " << player.numOfCoins << " coins.";
}

// ============================================
// Army Implementation
// ============================================

// Army constructor.
Army::Army(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

// Army destructor.
Army::~Army()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string Army::GetOwnerName()
{
	return (*owner).GetName();
}

// Returns pointer to owner.
Player* Army::GetOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* Army::GetPosition()
{
	return position;
}

// Changes position.
void Army::SetPosition(Territory* newPosition)
{
	position = newPosition;
}

// Army's toString
ostream& operator<<(ostream& strm, const Army& army)
{
	return strm << army.owner->GetName() << "'s army";
}

// ============================================
// City Implementation
// ============================================

// City constructor.
City::City(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

// City destructor.
City::~City()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string City::GetOwnerName()
{
	return owner->GetName();
}

// Returns pointer to owner.
Player* City::GetOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* City::GetPosition()
{
	return position;
}

// City's toString
ostream& operator<<(ostream& strm, const City& city)
{
	return strm << city.owner->GetName() << "'s city";
}