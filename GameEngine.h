#pragma once


#include "GameObservers.h"
#include "Game.h"

class GameEngine{

public:
    int selectGameMode();
    void singleGame(int selectedMode);
    void tournamentGame(int selectedMode);

};