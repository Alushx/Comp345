#pragma once
#include <iostream>
#include <list>

struct Map {
	std::unordered_map<int, std::list< std::pair<int, int>> > countriesList;
public:
	Map();
	void addEdge(int, int, int);
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
