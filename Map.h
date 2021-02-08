#pragma once
#include <iostream>
#include <list>


struct Map {

	int countries;
	std::list<int>* countriesList;

public:
	Map(int);
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