#include "Player.h"

int main()
{
	Territory* territory1 = new Territory();
	Territory* territory2 = new Territory();
	Player* player1 = new Player("Achilles", 12);

	player1->PlaceNewArmies(territory1);

	Army* army = player1->GetArmies()->front();
	player1->MoveArmies(army, territory2);
	player1->MoveOverLand(army, territory1);
	player1->DestroyArmy(army);

	delete territory1;
	delete territory2;
	delete player1;
	territory1 = nullptr;
	territory2 = nullptr;
	player1 = nullptr;

	return 0;
}

