#include "GameEngine.h"
#include <iostream>

int main(){
    GameEngine * gameEngine = new GameEngine();
    int gameMode = gameEngine->selectGameMode();

    if (gameMode == 2)
    {
        gameEngine->tournamentGame(gameMode);
    }
    else
    {
        gameEngine->singleGame(gameMode);
    }
}
