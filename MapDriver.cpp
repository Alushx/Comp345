#include <iostream>
#include "Map.h"



int main() {

	Map m1(3);
	m1.addEdge(0, 1);
	m1.addEdge(1, 2);

	m1.printList();

	return 0;
}
