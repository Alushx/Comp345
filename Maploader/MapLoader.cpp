#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"
using namespace std;

// Default constructor.
MapLoader::MapLoader()
{
    map = new Map();
}

// Destructors. Not necessary, but I wanted to mention the point below.
MapLoader::~MapLoader()
{
    // Map loader should be deleted near the start of the game, so doesn't make sense to deallocate map memory. 
    // It should be passed on to an independent map pointer at that point.
    map = nullptr;
}

// Copy constructor.
MapLoader::MapLoader(MapLoader& otherMap)
{
    if (otherMap.map)
    {
        map = new Map(*otherMap.map);
    }
    else
    {
        map = nullptr;
    }
}

// Creates map by reading a map text file.
void MapLoader::readMapFile(string fileName){
    bool shouldContinue = true;
    ifstream inFile;
    inFile.open(fileName);

    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    string task;
    while (!inFile.eof() && shouldContinue)
    {
        inFile >> task;
        if (task == "CONTINENT")
        {
            CreateContinent(inFile);
        }
        else if (task == "JOIN")
        {
            JoinTerritories(inFile);
        }
        else if (task == "BOARD")
        {
            CreateBoard(inFile);
        }
        else if (task == "OPTIONAL")
        {
            shouldContinue = ShouldCreateBoard();
        }
    }

    inFile.close();

}

// Creates a continent.
void MapLoader::CreateContinent(ifstream& input)
{
    string territoryName;
    list<Territory*> continent;
    Territory* territory;
    string line;
    string name;

    getline(input, line); // Get until end of line.
    istringstream stream(line); // Convert to string stream.

    // Parse line for each territory.
    while (stream >> name)
    {
        // Check if the territory already exists or not.
        if (!map->GetTerritory(name))
        {
            territory = new Territory(name);
        }
        else
        {
            territory = map->GetTerritory(name);
        }
        continent.push_back(territory);
    }

    // Add continent.
    map->AddContinent(continent);
}

// Adds an edge between the territories in the file.
void MapLoader::JoinTerritories(ifstream& input)
{
    string terr1;
    string terr2;
    int cost;

    // Get file info.
    input >> terr1;
    input >> terr2;
    input >> cost;

    // Add edge.
    map->addEdge(map->GetTerritory(terr1), map->GetTerritory(terr2), cost);
}

// Adds boards to map.
void MapLoader::CreateBoard(ifstream& input)
{

}

// Asks whether player wants the fourth board or not.
bool MapLoader::ShouldCreateBoard()
{
    int response = 0;
    do
    {
        cout << "Do you want to use the fourth board?" << endl;
        cout << "\t 1) Yes" << endl;
        cout << "\t 2) No" << endl;
    } while (!(response == 1 || response == 2));

    if (response == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Returns map to be used for game.
Map* MapLoader::GetMap()
{
    return map;
}

// Stream insertion operator.
ostream& operator<<(ostream& strm, const MapLoader& map)
{
    return strm << "MapBuilder"; // I can't think of anything clever for this.
}