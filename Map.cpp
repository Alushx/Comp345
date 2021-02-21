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
#include "Map.h"
#include "Player.h"
using namespace std;
	
	//====================================
	// Map implementation.
	//====================================

	// Map default constructor
	Map::Map(){
		countriesList = map<Territory*, map<Territory*, int>>();
		continentList = list<list<Territory*>>();
		territories = map<string, Territory*>();
	}

	// Copy constructor.
	Map::Map(const Map& anotherMap)
	{
		for (pair<string, Territory*> otherPair : anotherMap.territories)
		{
			// Create deep copy.
			territories[otherPair.first] = new Territory(*(otherPair.second));
		}

		// Copies each continent.
		list<Territory*> tempContinent;
		Territory* myTerritory = nullptr;
		Territory* secondTerritory = nullptr;
		for (list<Territory*> otherContinent : anotherMap.continentList)
		{
			tempContinent = list<Territory*>();
			for (Territory* otherTerritory : otherContinent)
			{
				myTerritory = territories[otherTerritory->getName()];
				tempContinent.push_back(myTerritory);
			}
			continentList.push_back(tempContinent);
		}

		// Copies adjacency list.
		for (pair<Territory*, map<Territory*, int>> otherPair: anotherMap.countriesList)
		{
			myTerritory = territories[otherPair.first->getName()];
			for (pair<Territory*, int> otherAdjacentTerritory : otherPair.second)
			{
				secondTerritory = territories[otherAdjacentTerritory.first->getName()];
				countriesList[myTerritory][secondTerritory] = otherAdjacentTerritory.second;
			}
		}
	}

	// Destructor.
	Map::~Map()
	{
		Territory* tempTerritory = nullptr;

		// Deallocating each territory in map. Since all territories of the map are in this list,
		// There's no reason to deallocate the memory in other pointers. The rest are now dangling.
		for (pair<string, Territory*> pair : territories)
		{
			tempTerritory = territories[pair.first];
			if (tempTerritory)
			{
				delete tempTerritory;
				tempTerritory = nullptr;
			}
		}
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
			cout << "Country " << country->getName() << " ---> ";
			for (auto j : adjacent) {
				Territory* destination = j.first;
				int cost = j.second;

				cout << "Adj to country " << destination->getName() << " and costs " << cost << " moves | ";
			}
			cout << endl;
		}
	}

	// Validates if our map meets all the criteria.
	bool Map::validate()
	{
		bool isConnectedGraph = isConnectedMap();
		bool hasUniqueRegions = hasUniqueTerritories();
		bool isConnectedSubgraph = true;

		for (list<Territory*> continent : continentList)
		{
			isConnectedSubgraph = isConnectedSubgraph && isConnectedContinent(&continent);
		}

		if (isConnectedGraph && hasUniqueRegions && isConnectedSubgraph)
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
	bool Map::isConnectedMap()
	{
		map<Territory*, bool> visitedList;

		// Setting all nodes to unvisited — AKA false.
		for (auto i : countriesList)
		{
			visitedList[i.first] = false;
		}

		// Traversing graph through one node (should visit all other nodes if it is truly connected).
		helpVisitMap(countriesList.begin()->first, &visitedList);

		// Check each node has been visited.
		for (auto i : visitedList)
		{
			if (!i.second)
			{
				cout << "Map is not a connected graph." << endl;
				return false;
			}
		}

		// If every node was visited, validate.
		return true;
	}

	// Recursive part of DFS.
	void Map::helpVisitMap(Territory* node, map<Territory*, bool>* visitedList)
	{
		// Visit node.
		(*visitedList)[node] = true;

		// Recursively check adjacent nodes.
		map<Territory*, int> adjacentNodes = countriesList[node];
		for (auto i : adjacentNodes)
		{
			if (!(*visitedList)[i.first])
			{
				helpVisitMap(i.first, visitedList);
			}
		}
	}

	// Checks if a continent is a connected subgraph.
	bool Map::isConnectedContinent(list<Territory*>* continent)
	{
		map<Territory*, bool> visitedList = map<Territory*, bool>();

		// Setting all territories to unvisited.
		for (auto territory : (*continent))
		{
			visitedList[territory] = false;
		}

		// Traversing continent through 1 territory.
		helpVisitContinent(*(*continent).begin(), &visitedList);

		// Check each territory has been visited.
		for (auto territory : visitedList)
		{
			if (!territory.second)
			{
				cout << "Continents are not connected subgraphs." << endl;
				return false;
			}
		}

		// If every territory was visited.
		return true;
	}

	// Helper function for IsConnectedContinent
	void Map::helpVisitContinent(Territory* node, std::map<Territory*, bool>* visitedList)
	{
		// Visit node.
		(*visitedList)[node] = true;

		// Recursively check adjacent territories that do not travel by sea.
		map<Territory*, int> adjacentNodes = countriesList[node];
		for (auto i : adjacentNodes)
		{
			if (i.second != 3 && !(*visitedList)[i.first] )
			{
				helpVisitContinent(i.first, visitedList);
			}
		}
	}

	// Helper method that checks if each territory belongs to only one continent.
	bool Map::hasUniqueTerritories()
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
					cout << "A territory exists in two different continents!" << endl;
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

	// Returns territory.
	Territory* Map::getTerritory(string name)
	{
		return territories[name];
	}

	// Adds a new continent.
	void Map::addContinent(std::list<Territory*>& aContinent)
	{
		continentList.push_back(aContinent);

		// Adds territories of new continent to our list of territories.
		for (Territory* input : aContinent)
		{
			territories[input->getName()] = input;
		}
	}

	// Stream insertion operator overload.
	std::ostream& operator<<(std::ostream& strm, const Map& otherMap)
	{
		return strm << "Map"; // Can't think of anything more clever.
	}

	Map& Map::operator=(const Map& anotherMap)
	{
		if (&anotherMap == this)
			return *this;
		
		for (pair<string, Territory*> otherPair : anotherMap.territories)
		{
			// Create deep copy.
			territories[otherPair.first] = new Territory(*(otherPair.second));
		}

		// Copies each continent.
		list<Territory*> tempContinent;
		Territory* myTerritory = nullptr;
		Territory* secondTerritory = nullptr;
		for (list<Territory*> otherContinent : anotherMap.continentList)
		{
			tempContinent = list<Territory*>();
			for (Territory* otherTerritory : otherContinent)
			{
				myTerritory = territories[otherTerritory->getName()];
				tempContinent.push_back(myTerritory);
			}
			continentList.push_back(tempContinent);
		}

		// Copies adjacency list.
		for (pair<Territory*, map<Territory*, int>> otherPair : anotherMap.countriesList)
		{
			myTerritory = territories[otherPair.first->getName()];
			for (pair<Territory*, int> otherAdjacentTerritory : otherPair.second)
			{
				secondTerritory = territories[otherAdjacentTerritory.first->getName()];
				countriesList[myTerritory][secondTerritory] = otherAdjacentTerritory.second;
			}
		}

		return *this;
	}
	
	
	//====================================
	// Territory implementation.
	//====================================

	// Territory value constructor.
	Territory::Territory(string aName)
	{
		numOfArmies = 0;
		name = aName;
		armies = map <Player*, list<Army*>>();
	}

	// Territory default constructor.
	Territory::Territory()
	{
		numOfArmies = 0;
		name = "Ithaca";
		armies = map <Player*, list<Army*>>();
	}

	// Territory copy constructor.
	Territory::Territory(const Territory& aTerritory)
	{
		// Basic/Immutable type, so it's safe to assign it.
		name = aTerritory.name;
		numOfArmies = aTerritory.numOfArmies;
		
		// Making shallow copy.
		armies = map <Player*, list<Army*>>(aTerritory.armies);
	}

	// Decrements army count. And remove army from list.
	void Territory::removeArmy(Army* army)
	{
		numOfArmies--;
		armies[army->getOwner()].remove(army);
	}

	// Increments army count. And add army to list.
	void Territory::addArmy(Army* army)
	{
		numOfArmies++;
		armies[army->getOwner()].push_back(army);
	}

	// Returns numOfArmies.
	int Territory::getNumOfArmies() const
	{
		return numOfArmies;
	}

	// Returns territory name.
	string Territory::getName() const
	{
		return name;
	}

	Player* Territory::getOwner()
	{
		int max = 0;
		Player* owner = nullptr;

		for (pair <Player*, list<Army*>> playerArmies : armies)
		{
			if (playerArmies.second.size() > max)
			{
				// Finding the player with the most armies.
				owner = playerArmies.first;
				max = playerArmies.second.size();
			}
			else if (playerArmies.second.size() == max)
			{
				// If there is a tie, then there is no clear owner.
				owner = nullptr;
			}
		}

		if (owner)
			std::cout << owner->getName() << " is the owner of " << name << endl;
		else
			std::cout << name << " has no owner" << endl;

		return owner;
	}
	// Stream insertion operator overload.
	ostream& operator<<(ostream& strm, const Territory& territory)
	{
		return strm << territory.getName() << " with " << territory.getNumOfArmies() << " armies";
	}

	Territory& Territory::operator=(const Territory& otherTerritory)
	{
		// Check for same object.
		if (&otherTerritory == this)
			return *this;

		// Assign each value.
		name = otherTerritory.name;
		numOfArmies = otherTerritory.numOfArmies;
		
		// Clear old one and create shallow copy.
		armies = map <Player*, list<Army*>>(otherTerritory.armies);

		// Return.
		return *this;
	}

