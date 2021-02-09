#pragma once
#include <iostream>
#include <list>

struct Continent {
	int countries;
	std::list<int>* countriesList;
public:
	Continent(int);
	void addEdge(int, int);
	void printList();
};

class Territory
{
private:
	int numOfArmies;
	std::list<Army*> armies;
	
public:
	Territory();
	~Territory();
	void RemoveArmy(Army*);
	void AddArmy(Army*);
	std::string Owner();
};
