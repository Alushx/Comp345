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
	
public:
	Territory();
	void RemoveArmy();
	void AddArmy();
	int GetNumOfArmies() const;

// Operators.
private:
	friend std::ostream& operator<<(std::ostream&, const Territory&);
};
