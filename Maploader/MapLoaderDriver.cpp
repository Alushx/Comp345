#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	MapLoader* loader = new MapLoader();
	
	loader->readMapFile("map.txt");

	loader->GetMap()->printList();

	delete loader;

	return 0;
}

