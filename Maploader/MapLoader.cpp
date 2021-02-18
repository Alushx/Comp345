//===================================================================
// Course: COMP 345
// Professor: Nora Houari
// Team: 14
// Students:
//      Adam Yafout - 40040306
//      Bryan Lee - 40079332
//      Carl Randyl Tuquero - 40067781
//      Sobhan Mehrpour - 40122438
//      Vithura Muthiah - 40062305
//===================================================================

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
MapLoader::MapLoader(const MapLoader& otherMap)
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
    int numOfPlayers = 0;
    int numOfBoards = 0;
    bool shouldContinue = true;
    bool shouldMakeL = false;
    std::map<int, std::map<std::string, Territory*>> boardConnections;

    ifstream inFile;
    inFile.open(fileName);

    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Seeing how many players there are.
    do
    {
        cout << "\n Please enter the number of players in the game: ";
        cin >> numOfPlayers;
    } while (numOfPlayers <= 1 || numOfPlayers > 4);

    // Asking players to pick arrangement (if there are less than 4 players)
    if (numOfPlayers < 4)
    {
        int choice = 0;
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

    string task;
    while (!inFile.eof() && shouldContinue)
    {
        inFile >> task;
        if (task == "CONTINENT")
        {
            createContinent(inFile);
        }
        else if (task == "JOIN")
        {
            joinTerritories(inFile);
        }
        else if (task == "BOARD")
        {
            createBoard(inFile, boardConnections, numOfBoards, shouldMakeL, numOfPlayers);
        }
        else if (task == "OPTIONAL")
        {
            shouldContinue = shouldCreateBoard(numOfPlayers);
        }
    }

    inFile.close();

}

// Creates a continent.
void MapLoader::createContinent(ifstream& input)
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
        if (!map->getTerritory(name))
        {
            territory = new Territory(name);
        }
        else
        {
            territory = map->getTerritory(name);
        }
        continent.push_back(territory);
    }

    // Add continent.
    map->addContinent(continent);
}

// Adds an edge between the territories in the file.
void MapLoader::joinTerritories(ifstream& input)
{
    string terr1;
    string terr2;
    int cost;

    // Get file info.
    input >> terr1;
    input >> terr2;
    input >> cost;

    // Add edge.
    map->addEdge(map->getTerritory(terr1), map->getTerritory(terr2), cost);
}

// Adds boards to map.
void MapLoader::createBoard(ifstream& input, std::map<int, std::map<std::string, Territory*>>& boardConnections, int& numOfBoards, bool& shouldMakeL, int& numOfPlayers)
{
    Territory* connectionDirection = nullptr;
    string directions[4] = { "NORTH", "EAST", "SOUTH", "WEST" };
    string territoryName = "";

    // Adding four directions.
    for (int i = 0; i < 4; i++)
    {
        input >> territoryName;
        if (! map->getTerritory(territoryName))
        {
            cout << "The map connection does not exist!";
            exit(1); // Territory should exist.
        }

        connectionDirection = map->getTerritory(territoryName);
        boardConnections[numOfBoards][directions[i]] = connectionDirection;
    }

    Territory* tempTerritory1 = nullptr;
    Territory* tempTerritory2 = nullptr;

    // Creating full board with 4 players.
    if (numOfPlayers == 4)
    {
        // Adding second board. (To the right of first)
        if (numOfBoards == 1)
        {
            tempTerritory1 = boardConnections[numOfBoards - 1]["EAST"];
            tempTerritory2 = boardConnections[numOfBoards]["WEST"];
            map->addEdge(tempTerritory1, tempTerritory2, 3);
        }

        // Adding third board. (Above second)
        else if (numOfBoards == 2)
        {
            tempTerritory1 = boardConnections[numOfBoards - 1]["NORTH"];
            tempTerritory2 = boardConnections[numOfBoards]["SOUTH"];
            map->addEdge(tempTerritory1, tempTerritory2, 3);
        }

        // Adding fourth board. (To the left of third and above first)
        else if (numOfBoards == 3)
        {
            // Connecting to third board.
            tempTerritory1 = boardConnections[numOfBoards - 1]["WEST"];
            tempTerritory2 = boardConnections[numOfBoards]["EAST"];
            map->addEdge(tempTerritory1, tempTerritory2, 3);

            // Connecting to first board to make circle complete.
            tempTerritory1 = boardConnections[0]["NORTH"];
            tempTerritory2 = boardConnections[numOfBoards]["SOUTH"];
            map->addEdge(tempTerritory1, tempTerritory2, 3);
        }
    }
    // Creating board for less players.
    else
    {
        // Placing second board
        if (numOfBoards == 1)
        {
            // Place below first if we should make an L
            if (shouldMakeL)
            {
                tempTerritory1 = boardConnections[numOfBoards - 1]["SOUTH"];
                tempTerritory2 = boardConnections[numOfBoards]["NORTH"];
            }
            // Place to the right of the first board if we should make a row.
            else
            {
                tempTerritory1 = boardConnections[numOfBoards - 1]["EAST"];
                tempTerritory2 = boardConnections[numOfBoards]["WEST"];
            }
            
            map->addEdge(tempTerritory1, tempTerritory2, 3);
        }

        // Placing third board (to the right of second)
        if (numOfBoards == 2)
        {
            tempTerritory1 = boardConnections[numOfBoards - 1]["EAST"];
            tempTerritory2 = boardConnections[numOfBoards]["WEST"];
            map->addEdge(tempTerritory1, tempTerritory2, 3);
        }
    }

    numOfBoards++;
}

// Asks whether player wants the fourth board or not.
bool MapLoader::shouldCreateBoard(int& numOfPlayers)
{
    if (numOfPlayers < 4)
        return false;
    else
        return true;
}

// Returns map to be used for game.
Map* MapLoader::getMap()
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