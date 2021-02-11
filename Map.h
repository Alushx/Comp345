#pragma once
#include <list>
#include <map>

struct Map {
	std::map<int, std::list< std::pair<int, int>> > countriesList;
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
