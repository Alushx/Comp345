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

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	// Map 1: Valid

	MapLoader* loader1 = new MapLoader();
	
	loader1->readMapFile("map1.txt");

	loader1->getMap()->printList();

	cout << "\n Validating: ";
	loader1->getMap()->validate();

	delete loader1;

	// Map 2: Invalid. Not connected map. (Only for 4 players because the invalid board piece is optional)

	MapLoader* loader2 = new MapLoader();

	loader2->readMapFile("map2.txt");

	loader2->getMap()->printList();

	cout << "\n Validating: ";
	loader2->getMap()->validate();

	delete loader2;

	// Map 3: Invalid. Not connected subgraphs. (Only for 4 players because the invalid board piece is optional)

	MapLoader* loader3 = new MapLoader();

	loader3->readMapFile("map3.txt");

	loader3->getMap()->printList();

	cout << "\n Validating: ";
	loader3->getMap()->validate();

	delete loader3;

	// Map 4: Invalid. A territory appears in two different continents. (Only for 4 players because the invalid board piece is optional)

	MapLoader* loader4 = new MapLoader();

	loader4->readMapFile("map4.txt");

	loader4->getMap()->printList();

	cout << "\n Validating: ";
	loader4->getMap()->validate();

	delete loader4;

	return 0;
}

