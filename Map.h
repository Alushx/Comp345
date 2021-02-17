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
	Map(Map&);
	~Map();
	void addEdge(Territory*, Territory*, int);
	void printList();
	Territory* GetTerritory(std::string);
	void AddContinent(std::list<Territory*>&);
	bool Validate();
	Map& operator=(const Map&);
private:
	bool IsConnectedMap();
	void HelpVisitMap(Territory* node, std::map<Territory*,bool>* visitedList);
	bool IsConnectedContinent(std::list<Territory*>*);
	void HelpVisitContinent(Territory* node, std::map<Territory*, bool>* visitedList);
	bool HasUniqueTerritories();
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
	Territory(Territory&);
	// No pointers so I do not need to define a destructor.
	void RemoveArmy();
	void AddArmy();
	int GetNumOfArmies() const;
	std::string GetName() const;

// Operators.
private:
	friend std::ostream& operator<<(std::ostream&, const Territory&);
public:
	Territory& operator=(const Territory&);
};
