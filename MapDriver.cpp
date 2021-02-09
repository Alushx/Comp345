#include <iostream>
#include "Map.h"


int main() {

	Continent A(7);
	A.addEdge(0, 1);
	A.addEdge(1, 2);
	A.addEdge(2, 3);
	A.addEdge(2, 4);
	A.addEdge(2, 5);
	A.addEdge(5, 6);

	cout << "Continent A:\n";

	A.printList();

	Continent B(5);
	B.addEdge(0, 1);
	B.addEdge(1, 2);
	B.addEdge(1, 3);
	B.addEdge(2, 3);
	B.addEdge(2, 4);

	cout << "\nContinent B:\n";

	B.printList();

	Continent C(3);
	C.addEdge(0, 1);
	C.addEdge(1, 2);

	cout << "\nContinent C:\n";

	C.printList();

	Continent D(3);
	D.addEdge(0, 1);
	D.addEdge(1, 2);

	cout << "\nContinent D:\n";

	D.printList();
}
