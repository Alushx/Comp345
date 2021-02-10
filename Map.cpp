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
	}

	// Decrements army count.
	void Territory::RemoveArmy()
	{
		numOfArmies--;
	}

	// Increments army count.
	void Territory::AddArmy()
	{
		numOfArmies++;
	}

	// Returns numOfArmies.
	int Territory::GetNumOfArmies() const
	{
		return numOfArmies;
	}

	ostream& operator<<(ostream& strm, const Territory& territory)
	{
		return strm << "territory with " << territory.GetNumOfArmies() << " armies.";
	}

