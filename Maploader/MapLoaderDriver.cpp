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
	MapLoader* loader = new MapLoader();
	
	loader->readMapFile("map.txt");

	loader->getMap()->printList();

	loader->getMap()->validate(); // Expected invalid. Because territory1 appears twice!

	delete loader;

	return 0;
}

