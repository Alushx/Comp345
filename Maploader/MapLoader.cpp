#include <iostream>
#include <iomanip>
#include <fstream>
#include "MapLoader.h"
using namespace std;

MapLoader :: MapLoader(){
    
}
void MapLoader :: readMapFile(string fileName){
    ifstream inFile;
    inFile.open(fileName);

    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
}