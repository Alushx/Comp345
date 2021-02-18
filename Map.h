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

#pragma once
#include <list>
#include <map>
#include <string>
#include <iostream>

using namespace std;

// Forward declaration to make compiler happy.
class Territory;

struct Map {
	std::map<Territory*, std::map<Territory*, int>> countriesList; // Adjacency matrix.
	std::list<std::list<Territory*>> continentList;
	std::map<std::string, Territory*> territories;

public:
	Map();
	Map(const Map&);
	~Map();
	void addEdge(Territory*, Territory*, int);
	void printList();
	Territory* getTerritory(std::string);
	void addContinent(std::list<Territory*>&);
	bool validate();
	Map& operator=(const Map&);
private:
	bool isConnectedMap();
	void helpVisitMap(Territory* node, std::map<Territory*,bool>* visitedList);
	bool isConnectedContinent(std::list<Territory*>*);
	void helpVisitContinent(Territory* node, std::map<Territory*, bool>* visitedList);
	bool hasUniqueTerritories();
	friend std::ostream& operator<<(std::ostream&, const Map&);
	
};

class Territory
{
private:
	int numOfArmies;
	std::string name;
	
public:
	Territory();
	Territory(std::string);
	Territory(const Territory&);
	// No pointers so I do not need to define a destructor.
	void removeArmy();
	void addArmy();
	int getNumOfArmies() const;
	std::string getName() const;

// Operators.
private:
	friend std::ostream& operator<<(std::ostream&, const Territory&);
public:
	Territory& operator=(const Territory&);
};
