#pragma once
#include <string.h>
#include <list>
#include "Cards.h"
#include "Player.h"
#include "Map.h"
using namespace std;

//Abstract Class
class PlayerStrategies{
public:
    virtual int pickCard(Hand *hand) = 0;
    virtual string displayCurrentStrategy() = 0;
    
    // Helpful methods for strategy.
    virtual Player* selectPlayer();
    virtual Army* selectArmy(list<Army*> armies);
    virtual Territory* selectTerritoryCurrentlyOn(list<Army*> armies);
    virtual Territory* selectTerritoryWithCity(list<City*> cities);
    virtual pair<Territory*, int> selectNeighbouringTerritory(Territory*, Map*);

};


// Strategy class
class Strategy {
private:
    PlayerStrategies* playerStrategy;

public:
    Strategy(PlayerStrategies*);
    ~Strategy();
    void set_strategy(PlayerStrategies*);
    int pickCard(Hand* hand);
    string displayCurrentStrategy();
};


//Human player: requires user interaction to make decisions
class HumanPlayer : public PlayerStrategies{
    public:
    virtual int pickCard(Hand *hand);
    virtual string displayCurrentStrategy();

    // Overrided methods in human player.
    virtual Player* selectPlayer();
    virtual Army* selectArmy(list<Army*> armies);
    virtual Territory* selectTerritoryCurrentlyOn(list<Army*> armies);
    virtual Territory* selectTerritoryWithCity(list<City*> cities);
    virtual pair<Territory*, int> selectNeighbouringTerritory(Territory*, Map*);
};

//Greedy Computer: player that focuses on building cities or destroying opponents
class GreedyComputer : public PlayerStrategies{
 public:
    virtual int pickCard(Hand *hand);
    virtual string displayCurrentStrategy();
};

//Moderate computer: control a region in which it just needs to occupy it with more armies than the opponents
class ModerateComputer : public PlayerStrategies{
 public:
    virtual int pickCard(Hand *hand);
    virtual string displayCurrentStrategy();
}; 