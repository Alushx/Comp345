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

int main()
{
	Territory* territory1 = new Territory();
	Territory* territory2 = new Territory();
	Player* player1 = new Player("Achilles", 12);

	player1->placeNewArmies(territory1);

	Army* army = player1->getArmies()->front();
	player1->moveArmies(army, territory2);
	player1->moveOverLand(army, territory1);
	player1->destroyArmy(army);

	delete territory1;
	delete territory2;
	delete player1;
	territory1 = nullptr;
	territory2 = nullptr;
	player1 = nullptr;

	return 0;
}

