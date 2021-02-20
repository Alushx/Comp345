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
	std::vector<Territory*> cities1 = vector<Territory*>();
	std::list<Territory*> continent = list<Territory*>();
	std::string name = "City ";
	int pause = 0;

	//===============
	// Map 1 - Valid
	//===============
	std::cout << "\n===========================\n"
			<< "           Map 1          \n"
			<< "===========================\n" << endl;

	for (int i = 0; i < 18; i++)
	{
		name = "City ";
		name.append(to_string(i+1));
		cities1.push_back(new Territory(name));
	}

	// Continent A: cities 0, 1, 2, 3, 4, 5, 6
	for (int i = 0; i <= 6; i++)
	{
		continent.push_back(cities1[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent Edges
	m1->addEdge(cities1[0], cities1[1], 1);
	m1->addEdge(cities1[1], cities1[2], 1);
	m1->addEdge(cities1[2], cities1[3], 1);
	m1->addEdge(cities1[2], cities1[4], 1);
	m1->addEdge(cities1[2], cities1[5], 1);
	m1->addEdge(cities1[5], cities1[6], 1);
	

	// Continent B - 7, 8, 12, 13, 14
	for (int i = 7; i <= 14; i++)
	{
		if (i <= 8 || i >= 12)
			continent.push_back(cities1[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent edges.
	m1->addEdge(cities1[7], cities1[8], 1);
	m1->addEdge(cities1[7], cities1[12], 1);
	m1->addEdge(cities1[7], cities1[13], 1);
	m1->addEdge(cities1[13], cities1[14], 1);
	

	// Continent C - 9, 10, 11
	for (int i = 9; i <= 11; i++)
	{
		continent.push_back(cities1[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent edges.
	m1->addEdge(cities1[9], cities1[10], 1);
	m1->addEdge(cities1[10], cities1[11], 1);

	// Continent D - 15, 16, 17
	for (int i = 15; i <= 17; i++)
	{
		continent.push_back(cities1[i]);
	}
	m1->addContinent(continent);
	continent.clear();

	// Continent edges.
	m1->addEdge(cities1[15], cities1[16], 1);
	m1->addEdge(cities1[16], cities1[17], 1);

	// Connecting Continents
	m1->addEdge(cities1[5], cities1[7], 3);
	m1->addEdge(cities1[8], cities1[9], 3);
	m1->addEdge(cities1[13], cities1[15], 3);

	// Printing map.
	m1->printList();
	std::cout << "\n ========== Validating Map ==========\n" << endl;
	m1->validate();

	// Deallocating memory;
	delete m1; // only one that's needed.
	m1 = nullptr;

	std::cout << "Enter a number to continue... ";
	std::cin >> pause;
	
	//==============================================
	// Map 2 - Fails Condition 1 - Is not connected
	//==============================================
	std::cout << "\n===========================\n"
				<< "           Map 2          \n"
				<< "===========================\n" << endl;
	
	std::vector<Territory*> cities2 = vector<Territory*>();
	Map* m2 = new Map();

	for (int i = 0; i < 18; i++)
	{
		name = "City ";
		name.append(to_string(i + 1));
		cities2.push_back(new Territory(name));
	}

	// Continent A: cities 0, 1, 2, 3, 4, 5, 6
	for (int i = 0; i <= 6; i++)
	{
		continent.push_back(cities2[i]);
	}
	m2->addContinent(continent);
	continent.clear();

	// Continent Edges
	m2->addEdge(cities2[0], cities2[1], 1);
	m2->addEdge(cities2[1], cities2[2], 1);
	m2->addEdge(cities2[2], cities2[3], 1);
	m2->addEdge(cities2[2], cities2[4], 1);
	m2->addEdge(cities2[2], cities2[5], 1);
	m2->addEdge(cities2[5], cities2[6], 1);


	// Continent B - 7, 8, 12, 13, 14
	for (int i = 7; i <= 14; i++)
	{
		if (i <= 8 || i >= 12)
			continent.push_back(cities2[i]);
	}
	m2->addContinent(continent);
	continent.clear();

	// Continent edges.
	m2->addEdge(cities2[7], cities2[8], 1);
	m2->addEdge(cities2[7], cities2[12], 1);
	m2->addEdge(cities2[7], cities2[13], 1);
	m2->addEdge(cities2[13], cities2[14], 1);


	// Continent C - 9, 10, 11
	for (int i = 9; i <= 11; i++)
	{
		continent.push_back(cities2[i]);
	}
	m2->addContinent(continent);
	continent.clear();

	// Continent edges.
	m2->addEdge(cities2[9], cities2[10], 1);
	m2->addEdge(cities2[10], cities2[11], 1);

	// Continent D - 15, 16, 17
	for (int i = 15; i <= 17; i++)
	{
		continent.push_back(cities2[i]);
	}
	m2->addContinent(continent);
	continent.clear();

	// Continent edges.
	m2->addEdge(cities2[15], cities2[16], 1);
	m2->addEdge(cities2[16], cities2[17], 1);

	// Connecting Continents
	m2->addEdge(cities2[5], cities2[7], 3);
	// Removed the connection to continent C
	m2->addEdge(cities2[13], cities2[15], 3);

	// Printing map.
	m2->printList();
	std::cout << "\n ========== Validating Map ==========\n" << endl;
	m2->validate();

	// Deallocating memory;
	delete m2; // only one that's needed.
	m2 = nullptr;

	std::cout << "Enter a number to continue... ";
	std::cin >> pause;

	//======================================================
	// Map 3 - Fails Condition 2 - Is not connected subgraph
	//======================================================
	std::cout << "\n===========================\n"
		<< "           Map 3          \n"
		<< "===========================\n" << endl;

	std::vector<Territory*> cities3 = vector<Territory*>();
	Map* m3 = new Map();

	for (int i = 0; i < 18; i++)
	{
		name = "City ";
		name.append(to_string(i + 1));
		cities3.push_back(new Territory(name));
	}

	// Continent A: cities 0, 1, 2, 3, 4, 5, 6
	for (int i = 0; i <= 6; i++)
	{
		continent.push_back(cities3[i]);
	}
	m3->addContinent(continent);
	continent.clear();

	// Continent Edges
	m3->addEdge(cities3[0], cities3[1], 1);
	m3->addEdge(cities3[1], cities3[2], 1);
	m3->addEdge(cities3[2], cities3[3], 1);
	m3->addEdge(cities3[2], cities3[4], 1);
	m3->addEdge(cities3[2], cities3[5], 1);
	m3->addEdge(cities3[5], cities3[6], 1);


	// Continent B - 7, 8, 12, 13, 14
	for (int i = 7; i <= 14; i++)
	{
		if (i <= 8 || i >= 12)
			continent.push_back(cities3[i]);
	}
	m3->addContinent(continent);
	continent.clear();

	// Continent edges.
	// Isolated city 7
	m3->addEdge(cities3[8], cities3[12], 1);
	m3->addEdge(cities3[8], cities3[13], 1);
	m3->addEdge(cities3[13], cities3[14], 1);


	// Continent C - 9, 10, 11
	for (int i = 9; i <= 11; i++)
	{
		continent.push_back(cities3[i]);
	}
	m3->addContinent(continent);
	continent.clear();

	// Continent edges.
	m3->addEdge(cities3[9], cities3[10], 1);
	m3->addEdge(cities3[10], cities3[11], 1);

	// Continent D - 15, 16, 17
	for (int i = 15; i <= 17; i++)
	{
		continent.push_back(cities3[i]);
	}
	m3->addContinent(continent);
	continent.clear();

	// Continent edges.
	m3->addEdge(cities3[15], cities3[16], 1);
	m3->addEdge(cities3[16], cities3[17], 1);

	// Connecting Continents
	m3->addEdge(cities3[5], cities3[7], 3);
	m3->addEdge(cities3[8], cities3[9], 3);
	m3->addEdge(cities3[8], cities3[5], 3); // Added this so it would be connected overall.
	m3->addEdge(cities3[13], cities3[15], 3);

	// Printing map.
	m3->printList();
	std::cout << "\n ========== Validating Map ==========\n" << endl;
	m3->validate();

	// Deallocating memory;
	delete m3; // only one that's needed.
	m3 = nullptr;

	std::cout << "Enter a number to continue... ";
	std::cin >> pause;

	//=======================================================
	// Map 4 - Fails Condition 3 - Territories are not unique
	//=======================================================
	std::cout << "\n===========================\n"
		<< "           Map 4          \n"
		<< "===========================\n" << endl;

	std::vector<Territory*> cities4 = vector<Territory*>();
	Map* m4 = new Map();

	for (int i = 0; i < 18; i++)
	{
		name = "City ";
		name.append(to_string(i + 1));
		cities4.push_back(new Territory(name));
	}

	// Changed this to include 7
	// Continent A: cities 0, 1, 2, 3, 4, 5, 6, 7
	for (int i = 0; i <= 7; i++)
	{
		continent.push_back(cities4[i]);
	}
	m4->addContinent(continent);
	continent.clear();

	// Continent Edges
	m4->addEdge(cities4[0], cities4[1], 1);
	m4->addEdge(cities4[1], cities4[2], 1);
	m4->addEdge(cities4[2], cities4[3], 1);
	m4->addEdge(cities4[2], cities4[4], 1);
	m4->addEdge(cities4[2], cities4[5], 1);
	m4->addEdge(cities4[5], cities4[6], 1);
	m4->addEdge(cities4[5], cities4[7], 1);

	// Continent B - 7, 8, 12, 13, 14
	for (int i = 7; i <= 14; i++)
	{
		if (i <= 8 || i >= 12)
			continent.push_back(cities4[i]);
	}
	m4->addContinent(continent);
	continent.clear();

	// Continent edges.
	m4->addEdge(cities4[7], cities4[8], 1);
	m4->addEdge(cities4[7], cities4[12], 1);
	m4->addEdge(cities4[7], cities4[13], 1);
	m4->addEdge(cities4[13], cities4[14], 1);


	// Continent C - 9, 10, 11
	for (int i = 9; i <= 11; i++)
	{
		continent.push_back(cities4[i]);
	}
	m4->addContinent(continent);
	continent.clear();

	// Continent edges.
	m4->addEdge(cities4[9], cities4[10], 1);
	m4->addEdge(cities4[10], cities4[11], 1);

	// Continent D - 15, 16, 17
	for (int i = 15; i <= 17; i++)
	{
		continent.push_back(cities4[i]);
	}
	m4->addContinent(continent);
	continent.clear();

	// Continent edges.
	m4->addEdge(cities4[15], cities4[16], 1);
	m4->addEdge(cities4[16], cities4[17], 1);

	// Connecting Continents
	// Removing this becuase we already have an edge between the two.
	m4->addEdge(cities4[8], cities4[9], 3);
	m4->addEdge(cities4[13], cities4[15], 3);

	// Printing map.
	m4->printList();
	std::cout << "\n ========== Validating Map ==========\n" << endl;
	m4->validate();

	// Deallocating memory;
	delete m4; // only one that's needed.
	m4 = nullptr;

	return 0;
}
