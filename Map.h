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

// Forward declaration to make compiler happy.
class Territory;
class Army;
class Player;

struct Map {

private:
	// Data members.
	std::map<Territory*, std::map<Territory*, int>> countriesList;
	std::list<std::list<Territory*>> continentList; 
	std::map<std::string, Territory*> territories;

public:
	// Constructors.
	Map();
	Map(const Map&);

	// Destructor.
	~Map();

	// Public methods.
	void addEdge(Territory*, Territory*, int);
	void printList();
	Territory* getTerritory(std::string);
	std::map<std::string, Territory*> getTerritories();
	Territory* selectTerritory();
	std::list<std::list<Territory*>> getContinents();
	Player* getContinentOwner(std::list<Territory*>);
	void addContinent(std::list<Territory*>&);
	std::map<Territory*, int> getAdjacentTerritories(Territory*);
	bool validate();
	Map& operator=(const Map&);
	
private:
	// Helper methods for validating.
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
	std::map<Player*, std::list<Army*>> armies;
	
public:
	Territory();
	Territory(std::string);
	Territory(const Territory&);
	// No pointers so I do not need to define a destructor.
	void removeArmy(Army*);
	void addArmy(Army*);
	int getNumOfArmies() const;
	std::string getName() const;
	Player* getOwner();

// Operators.
private:
	friend std::ostream& operator<<(std::ostream&, const Territory&);
public:
	Territory& operator=(const Territory&);
};