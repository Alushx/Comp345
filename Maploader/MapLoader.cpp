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

// Destructors. Assumes the map loader is present throughout the game.
MapLoader::~MapLoader()
{
    if (map)
        delete map;
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
    int numOfBoards = 0;
    bool shouldMakeL = false;
    std::map<int, std::map<std::string, Territory*>> boardConnections;

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
            CreateBoard(inFile, boardConnections, numOfBoards, shouldMakeL);
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
void MapLoader::CreateBoard(ifstream& input, std::map<int, std::map<std::string, Territory*>>& boardConnections, int& numOfBoards, bool& shouldMakeL)
{
    Territory* connectionDirection = nullptr;
    string directions[4] = { "NORTH", "EAST", "SOUTH", "WEST" };
    string territoryName = "";

    // Adding four directions.
    for (int i = 0; i < 4; i++)
    {
        input >> territoryName;
        if (! map->GetTerritory(territoryName))
        {
            cout << "The map connection does not exist!";
            exit(1); // Territory should exist.
        }

        connectionDirection = map->GetTerritory(territoryName);
        boardConnections[numOfBoards][directions[i]] = connectionDirection;
    }


    int choice = 0;
    // Ask for board arrangement.
    if (numOfBoards == 0)
    {
        do
        {
            cout << "Enter [1] or [2] to decide the board arrangement: " << endl;
            cout << "\t 1) Form a straight line." << endl;
            cout << "\t 2) For an L shape." << endl;
            cin >> choice;
        } while (choice != 1 && choice != 2);

        if (choice == 1)
        {
            shouldMakeL = false;
        }
        else
        {
            shouldMakeL = true;
        }
    }

    Territory* tempTerritory1 = nullptr;
    Territory* tempTerritory2 = nullptr;

    // Connecting first three boards in a row.
    if (numOfBoards == 1 || numOfBoards == 2)
    {
        tempTerritory1 = boardConnections[numOfBoards - 1]["EAST"];
        tempTerritory2 = boardConnections[numOfBoards]["WEST"];
        map->addEdge(tempTerritory1, tempTerritory2, 3);
    }

    // Connecting the last piece. An L or a row.
    if (numOfBoards == 3)
    {
        if (shouldMakeL)
        {
            tempTerritory1 = boardConnections[numOfBoards - 1]["NORTH"];
            tempTerritory2 = boardConnections[numOfBoards]["SOUTH"];
        }
        else
        {
            tempTerritory1 = boardConnections[numOfBoards - 1]["EAST"];
            tempTerritory2 = boardConnections[numOfBoards]["WEST"];
        }
        map->addEdge(tempTerritory1, tempTerritory2, 3);
    }

    numOfBoards++;
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

// Assignment operator
MapLoader& MapLoader::operator=(const MapLoader& anotherMapLoader)
{
    if (&anotherMapLoader == this)
        return *this;

    if (anotherMapLoader.map)
    {
        map = new Map(*(anotherMapLoader.map));
    }
    else
        map = nullptr;

    return *this;
}