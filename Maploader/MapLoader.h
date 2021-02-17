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
    Map* GetMap();
    
private:
    void CreateContinent(std::ifstream&);
    void JoinTerritories(std::ifstream&);
    void CreateBoard(std::ifstream&, std::map<int, std::map<std::string, Territory*>>&, int&, bool&);
    bool ShouldCreateBoard();
    friend ostream& operator<<(ostream&, const MapLoader&);
};