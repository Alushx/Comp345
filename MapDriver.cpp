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

#include <iostream>
#include<map>
#include "Map.h"
#include <vector>
#include <string>

int main() {

	Map* m1 = new Map();
	std::vector<Territory*> cities = vector<Territory*>();
	std::list<Territory*> continent = list<Territory*>();
	std::string name = "City ";
	for (int i = 0; i < 18; i++)
	{
		name = "City ";
		name.append(to_string(i+1));
		cities.push_back(new Territory(name));
	}


	// Continent A: cities 0, 1, 2, 3, 4, 5, 6
	for (int i = 0; i <= 6; i++)
	{
		continent.push_back(cities[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent Edges
	m1->addEdge(cities[0], cities[1], 1);
	m1->addEdge(cities[1], cities[2], 1);
	m1->addEdge(cities[2], cities[3], 1);
	m1->addEdge(cities[2], cities[4], 1);
	m1->addEdge(cities[2], cities[5], 1);
	m1->addEdge(cities[5], cities[6], 1);
	

	// Continent B - 7, 8, 12, 13, 14
	for (int i = 7; i <= 14; i++)
	{
		if (i <= 8 || i >= 12)
			continent.push_back(cities[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent edges.
	m1->addEdge(cities[7], cities[8], 1);
	m1->addEdge(cities[7], cities[12], 1);
	m1->addEdge(cities[7], cities[13], 1);
	m1->addEdge(cities[13], cities[14], 1);
	

	// Continent C - 9, 10, 11
	for (int i = 9; i <= 11; i++)
	{
		continent.push_back(cities[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent edges.
	m1->addEdge(cities[9], cities[10], 1);
	m1->addEdge(cities[10], cities[11], 1);

	// Continent D - 15, 16, 17
	for (int i = 15; i <= 17; i++)
	{
		continent.push_back(cities[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent edges.
	m1->addEdge(cities[15], cities[16], 1);
	m1->addEdge(cities[16], cities[17], 1);

	// Connecting Continents
	m1->addEdge(cities[5], cities[7], 3);
	m1->addEdge(cities[8], cities[9], 3);
	m1->addEdge(cities[13], cities[15], 3);

	// Printing map.
	m1->printList();
	m1->validate();

	// Deallocating memory;
	delete m1; // only one that's needed.
	m1 = nullptr;

	return 0;
}
