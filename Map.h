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