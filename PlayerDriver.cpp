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
#include <iostream>

int main()
{
	Territory* territory1 = new Territory();
	Territory* territory2 = new Territory("Troy");
	Player* player1 = new Player("Achilles", 12);

	// Creating army.
	std::cout << "\n Creating new army:\t";
	player1->placeNewArmies(territory1);
	Army* army = player1->getArmies()->front();

	// Moving army.
	std::cout << "\n Moving army:\t";
	player1->moveArmies(army, territory2);

	// Moving army overland.
	std::cout << "\n Moving army overland:\t";
	player1->moveOverLand(army, territory1);

	// Territory1 owner.
	std::cout << "\n Finding territory1 owner:\t";
	territory1->getOwner();

	// Territory2 owner.
	std::cout << "\n Finding territory2 owner:\t";
	territory2->getOwner();

	// Destroying army.
	std::cout << "\n Destroying army:\t";
	player1->destroyArmy(army);
	
	std::cout << "\n" << std::endl;

	// Deallocating heap.
	delete territory1;
	delete territory2;
	delete player1;
	territory1 = nullptr;
	territory2 = nullptr;
	player1 = nullptr;

	return 0;
}

