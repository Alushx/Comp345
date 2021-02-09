#include <iostream>
#include "Map.h"
using namespace std;

	Continent::Continent(int V) {
		this->countries = V;
		countriesList = new list<int>[V];
	}

	void Continent::addEdge(int x, int y) {
		countriesList[x].push_back(y);
		countriesList[y].push_back(x);
	}

	void Continent::printList() {
		for (int i = 0; i < countries; i++)
		{
			cout << "Country " << i << "----";
			for (int j : countriesList[i]) {
				cout << j << ",";
			}
			cout << endl;
		}
	}

	// Territory default constructor.
	Territory::Territory()
	{
		numOfArmies = 0;
		armies = std::list<Army*>();
	}
	// Territory destructor.
	Territory::~Territory()
	{
		// Delete each pointer inside the list to avoid memory leaks.
		for (std::list<Army*>::iterator iter = armies.begin(); iter != armies.end(); iter++)
		{
			delete *iter;
			*iter = nullptr;
		}
	}
	void Territory::RemoveArmy(Army* army)
	{
		numOfArmies--;
		armies.remove(army); // Does this cause memory leak?
	}
	void Territory::AddArmy(Army* army)
	{
		numOfArmies++;
		armies.push_back(army);
	}
	std::string Territory::Owner()
	{
		// Count how many armies belong to each player.
		// Player with the most armies has their name returned.
	}

