#pragma once
#include "../Map/Map.h"
using namespace std;

class MapLoader {
public:
    Map *map;
    MapLoader() = default;
    void readMapFile(string fileName);
};