#include <iostream>
#include "Map.h"
using namespace std;
	
	//====================================
	// Map implementation.
	//====================================

	// Map constructor
	Map::Map(){
		map<Territory*, list< pair<Territory*, int>> > countriesList;
		list<list<Territory*>> continentList;
	}

	// Creates an edge between countries
	void Map::addEdge(Territory* a, Territory* b, int cost) {
		countriesList[a][b] = cost;
		countriesList[b][a] = cost;
	}
	
	// Prints countries, the adjacent countries and the cost to move
	void Map::printList() {
		for (auto i : countriesList) {
			Territory* country = i.first;
			map <Territory*, int> adjacent = i.second;
			cout << "Country " << country->GetName() << " ---> ";
			for (auto j : adjacent) {
				Territory* destination = j.first;
				int cost = j.second;

				cout << "Adj to country " << destination->GetName() << " and costs " << cost << " moves | ";
			}
			cout << endl;
		}
	}

	// Validates if our map meets all the criteria.
	bool Map::Validate()
	{
		bool isConnectedMap = IsConnectedMap();
		bool hasUniqueTerritories = HasUniqueTerritories();
		bool isConnectedContinent = true;

		for (list<Territory*> continent : continentList)
		{
			isConnectedContinent = isConnectedContinent && IsConnectedContinent(&continent);
		}

		if (isConnectedMap && isConnectedContinent && hasUniqueTerritories)
		{
			cout << "The map is valid." << endl;
			return true;
		}
		else
		{
			cout << "The map is invalid!" << endl;
			return false;
		}
	}

	// Validates graph connectivity.
	bool Map::IsConnectedMap()
	{
		map<Territory*, bool> visitedList;

		// Setting all nodes to unvisited — AKA false.
		for (auto i : countriesList)
		{
			visitedList[i.first] = false;
		}

		// Traversing graph through one node (should visit all other nodes if it is truly connected).
		HelpVisitMap(countriesList.begin()->first, &visitedList);

		// Check each node has been visited.
		for (auto i : visitedList)
		{
			if (!i.second)
			{
				return false;
			}
		}

		// If every node was visited, validate.
		return true;
	}

	// Recursive part of DFS.
	void Map::HelpVisitMap(Territory* node, map<Territory*, bool>* visitedList)
	{
		// Visit node.
		(*visitedList)[node] = true;

		// Recursively check adjacent nodes.
		map<Territory*, int> adjacentNodes = countriesList[node];
		for (auto i : adjacentNodes)
		{
			if (!(*visitedList)[i.first])
			{
				HelpVisitMap(i.first, visitedList);
			}
		}
	}

	// Checks if a continent is a connected subgraph.
	bool Map::IsConnectedContinent(list<Territory*>* continent)
	{
		map<Territory*, bool> visitedList;

		// Setting all territories to unvisited.
		for (auto territory : (*continent))
		{
			visitedList[territory] = false;
		}

		// Traversing continent through 1 territory.
		HelpVisitContinent(*(*continent).begin(), &visitedList);

		// Check each territory has been visited.
		for (auto territory : visitedList)
		{
			if (!territory.second)
			{
				return false;
			}
		}

		// If every territory was visited.
		return true;
	}

	// Helper function for IsConnectedContinent
	void Map::HelpVisitContinent(Territory* node, std::map<Territory*, bool>* visitedList)
	{
		// Visit node.
		(*visitedList)[node] = true;

		// Recursively check adjacent territories that do not travel by sea.
		map<Territory*, int> adjacentNodes = countriesList[node];
		for (auto i : adjacentNodes)
		{
			if (!(*visitedList)[i.first] && i.second != 3)
			{
				HelpVisitContinent(i.first, visitedList);
			}
		}
	}

	// Helper method that checks if each territory belongs to only one continent.
	bool Map::HasUniqueTerritories()
	{
		map<Territory*, bool> visitedTerritories;

		// Loop through continent territories and check if a territory has been visited before.
		for (list<list<Territory*>>::iterator continentIter = continentList.begin(); continentIter != continentList.end(); continentIter++)
		{
			for (list<Territory*>::iterator territoryIter = continentIter->begin(); territoryIter != continentIter->end(); territoryIter++)
			{
				if (visitedTerritories[*territoryIter])
				{
					// Has been visited before.
					return false;
				}
				else
				{
					// Visit territory.
					visitedTerritories[*territoryIter] = true;
				}
			}
		}

		// No duplicates.
		return true;
	}

	// Returns list of continents.
	list<list<Territory*>>* Map::GetContinents()
	{
		return &continentList;
	}

	// Adds a new continent.
	void Map::AddContinent(std::list<Territory*> aContinent)
	{
		continentList.push_back(aContinent);
	}
	
	
	//====================================
	// Territory implementation.
	//====================================

	// Territory value constructor.
	Territory::Territory(string aName)
	{
		numOfArmies = 0;
		name = aName;
	}

	// Territory default constructor.
	Territory::Territory()
	{
		numOfArmies = 0;
		name = "Ithaca";
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

	// Returns territory name.
	string Territory::GetName() const
	{
		return name;
	}

	ostream& operator<<(ostream& strm, const Territory& territory)
	{
		return strm << territory.GetName() << " with " << territory.GetNumOfArmies() << " armies.";
	}

