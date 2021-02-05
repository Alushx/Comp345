#include <iostream>
#include "Map.h"
using namespace std;

	Map::Map(int V) {
		countries = V;
		countriesList = new list<int>[V];
	}

	void Map::addEdge(int x, int y) {
		countriesList[x].push_back(y);
		countriesList[y].push_back(x);
	}

	void Map::printList() {
		for (int i = 0; i < countries; i++)
		{
			cout << "Country " << i << "----";
			for (int j : countriesList[i]) {
				cout << j << ",";
			}
			cout << endl;
		}
	}

