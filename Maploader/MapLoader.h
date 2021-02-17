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

#pragma once
#include "../Map.h"
#include <string>
#include <fstream>

class MapLoader {
    Map *map;
public:
    MapLoader();
    ~MapLoader();
    MapLoader(MapLoader&);
    void readMapFile(std::string fileName);
    Map* getMap();
    MapLoader& operator=(const MapLoader&);
    
private:
    void createContinent(std::ifstream&);
    void joinTerritories(std::ifstream&);
    void createBoard(std::ifstream&, std::map<int, std::map<std::string, Territory*>>&, int&, bool&);
    bool shouldCreateBoard();
    friend ostream& operator<<(ostream&, const MapLoader&);
};