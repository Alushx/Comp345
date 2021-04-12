#include "GameEngine.h"
#include <iostream>

int main(){
    GameEngine * gameEngine = new GameEngine();
    int gameMode = gameEngine->selectGameMode();

    if (gameMode == 2)
    {
        //gameEngine->tournamentGame();//To do
    }
    else
    {
        //gameEngine->singleGame();//To do
    }
}