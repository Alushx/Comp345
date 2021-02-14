#include <iostream>
#include<map>
#include "Map.h"

int main() {

	Map m1;
	Territory city1("City 1");
	Territory city2("City 2");
	Territory city3("City 3");
	Territory city4("City 4");
	Territory city5("City 5");
	Territory city6("City 6");
	Territory city7("City 7");
	Territory city8("City 8");
	Territory city9("City 9");
	Territory city10("City 10");
	Territory city11("City 11");
	Territory city12("City 12");
	Territory city13("City 13");
	Territory city14("City 14");
	Territory city15("City 15");
	Territory city16("City 16");
	Territory city17("City 17");
	Territory city18("City 18");
	Territory city19("City 19");
	Territory city20("City 20");

	// Continent A
	m1.addEdge(&city1, &city2, 1);
	m1.addEdge(&city2, &city3, 1);
	m1.addEdge(&city3, &city4, 1);
	m1.addEdge(&city3, &city5, 1);
	m1.addEdge(&city3, &city6, 1);
	m1.addEdge(&city6, &city7, 1);
	m1.addEdge(&city6, &city8, 3);

	// Continent B
	m1.addEdge(&city8, &city9, 1);
	m1.addEdge(&city8, &city13, 1);
	m1.addEdge(&city8, &city14, 1);
	m1.addEdge(&city14, &city15, 1);
	m1.addEdge(&city9, &city10, 3);
	m1.addEdge(&city14, &city16, 3);

	// Continent C
	m1.addEdge(&city10, &city11, 1);
	m1.addEdge(&city11, &city12, 1);

	// Continent D
	m1.addEdge(&city16, &city17, 1);
	m1.addEdge(&city17, &city18, 1);

	m1.printList();
	m1.Validate();

	return 0;
}
