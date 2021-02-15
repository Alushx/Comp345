#pragma once
#include "../Map.h"
#include <string>
#include <fstream>

class MapLoader {
    Map *map;
public:
    MapLoader();
    void readMapFile(std::string fileName);
    Map* GetMap();
private:
    void CreateContinent(std::ifstream&);
    void JoinTerritories(std::ifstream&);
};