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

#include "GameObservers.h"
#include "Game.h"
#include "MapLoader.h"

class GameEngine{

public:
    int selectGameMode();
    void singleGame(int selectedMode);
    void tournamentGame(int selectedMode);
    MapLoader* startTournament();
    void playTournamentGame(Hand* hand, MapLoader* mapLoader);
};