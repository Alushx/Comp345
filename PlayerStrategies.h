#pragma once
#include <string.h>
#include "Cards.h"
using namespace std;
//Abstract Class
class PlayerStrategies{
public:
    virtual int pickCard(Hand *hand) = 0;
    virtual string displayCurrentStrategy() = 0;
};

//Human player: requires user interaction to make decisions
class HumanPlayer : public PlayerStrategies{
    public:
    virtual int pickCard(Hand *hand);
    virtual string displayCurrentStrategy();
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