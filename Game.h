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

#include "MapLoader/MapLoader.h"
#include "Cards/Cards.h"
#include "Player.h"

void deallocateResources(MapLoader* mapLoader, Deck* deck, Hand* hand);
int selectBidWinner();
void createDeck(Deck* deck);
void placeArmies(MapLoader* mapLoader);
void placeBotArmies(MapLoader* mapLoader);
void calculateScore(MapLoader* mapLoader);
void determineWinner();
MapLoader* startGame();
void playGame(Hand* hand, int, MapLoader* mapLoader);


