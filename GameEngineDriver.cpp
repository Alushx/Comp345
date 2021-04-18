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
#include "GameEngine.h"
#include <iostream>

int main(){
    int const TOURNAMENT = 2;
    GameEngine * gameEngine = new GameEngine();
    int gameMode = gameEngine->selectGameMode();

    if (gameMode == TOURNAMENT)
    {
        gameEngine->tournamentGame(gameMode);
    }
    else
    {
        gameEngine->singleGame(gameMode);
    }

    delete gameEngine;
}
