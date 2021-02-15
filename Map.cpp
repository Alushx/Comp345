#include <iostream>
#include "Map.h"
using namespace std;

	// Map constructor
	Map::Map(){
		map<int, list< pair<int, int>> > countriesList;
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

	// Validates graph connectivity.
	bool Map::Validate()
	{
		map<int, bool> visitedList;

		// Setting all nodes to unvisited — AKA false.
		for (auto i : countriesList)
		{
			visitedList[i.first] = false;
		}

		// Traversing graph through one node (should visit all other nodes if it is truly connected).
		ValidateHelper(countriesList.begin()->first, &visitedList);

		// Check each node has been visited.
		for (auto i : visitedList)
		{
			if (!i.second)
			{
				cout << "Invalid map. Not fully connected." << endl;
				return false;
			}
		}

		// If every node was visited, validate.
		cout << "Valid map. It is fully connected." << endl;
		return true;
	}

	// Recursive part of DFS.
	void Map::ValidateHelper(int node, map<int, bool>* visitedList)
	{
		// Visit node.
		(*visitedList)[node] = true;

		// Recursively check adjacent nodes.
		list<pair<int, int>> adjacentNodes = countriesList[node];
		for (auto i : adjacentNodes)
		{
			if (!(*visitedList)[i.first])
			{
				ValidateHelper(i.first, visitedList);
			}
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

