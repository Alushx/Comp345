#pragma once
#include <list>
#include <map>

// Forward declaration to make compiler happy.
class Territory;

struct Map {
	std::map<Territory*, std::map<Territory*, int>> countriesList; // Adjacency matrix.
	std::list<std::list<Territory*>> continentList;
	std::map<std::string, Territory*> territories;

public:
	Map();
	void addEdge(Territory*, Territory*, int);
	void printList();
	Territory* GetTerritory(std::string);
	void AddContinent(std::list<Territory*>&);
	bool Validate();
private:
	bool IsConnectedMap();
	void HelpVisitMap(Territory* node, std::map<Territory*,bool>* visitedList);
	bool IsConnectedContinent(std::list<Territory*>*);
	void HelpVisitContinent(Territory* node, std::map<Territory*, bool>* visitedList);
	bool HasUniqueTerritories();
};

class Territory
{
private:
	int numOfArmies;
	std::string name;
	
public:
	Territory();
	Territory(std::string);
	void RemoveArmy();
	void AddArmy();
	int GetNumOfArmies() const;
	std::string GetName() const;

// Operators.
private:
	friend std::ostream& operator<<(std::ostream&, const Territory&);
};
