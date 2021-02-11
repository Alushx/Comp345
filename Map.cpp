#include <iostream>
#include "Map.h"
using namespace std;

	// Map constructor
	Map::Map(){
		unordered_map<int, list< pair<int, int>> > countriesList;
	}

	// Creates an edge between countries
	void Map::addEdge(int a, int b, int cost) {
		countriesList[a].push_back(make_pair(b, cost));
		countriesList[b].push_back(make_pair(a, cost));
	}
	
	// Prints countries, the adjacent countries and the cost to move
	void Map::printList() {
		for (auto i : countriesList) {
			int country = i.first;
			list < pair<int, int>> adjacent = i.second;
			cout << "Country " << country << " ---> ";
			for (auto j : adjacent) {
				int destination = j.first;
				int cost = j.second;

				cout << "Adj to country " << destination << " and costs " << cost << " moves | ";
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

