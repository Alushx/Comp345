#include <iostream>
#include "Map.h"

int main() {

	Map m1;

	// Continent A
	m1.addEdge(1, 2, 1);
	m1.addEdge(2, 3, 1);
	m1.addEdge(3, 4, 1);
	m1.addEdge(3, 5, 1);
	m1.addEdge(3, 6, 1);
	m1.addEdge(6, 7, 1);
	m1.addEdge(6, 8, 3);

	// Continent B
	m1.addEdge(8, 9, 1);
	m1.addEdge(8, 13, 1);
	m1.addEdge(8, 14, 1);
	m1.addEdge(14, 15, 1);
	m1.addEdge(9, 10, 3);
	m1.addEdge(14, 16, 3);

	// Continent C
	m1.addEdge(10, 11, 1);
	m1.addEdge(11, 12, 1);

	// Continent D
	m1.addEdge(16, 17, 1);
	m1.addEdge(17, 18, 1);

	m1.printList();

	return 0;
}
