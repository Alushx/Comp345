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
#include <string.h>
#include <list>
#include "Cards.h"
#include "Player.h"
#include "Map.h"

//Abstract Class
class PlayerStrategies{
public:
    // Constructors and destructors.
    // None of these are needed. Just trying to meet assignment requirements.
    PlayerStrategies();
    PlayerStrategies(const PlayerStrategies&);
    ~PlayerStrategies();

    // Main operations.
    virtual int pickCard(Hand *hand) = 0;
    virtual std::string displayCurrentStrategy() = 0;
    
    // Helpful methods for strategy.
    virtual Player* selectPlayer();
    virtual Army* selectArmy(std::list<Army*> armies);
    virtual Territory* selectTerritoryCurrentlyOn(std::list<Army*> armies);
    virtual Territory* selectTerritoryWithCity(std::list<City*> cities);
    virtual std::pair<Territory*, int> selectNeighbouringTerritory(Territory*, Map*);
    virtual int selectOrAction(Card* card) = 0;

    // Operators.
    friend std::ostream& operator <<(std::ostream& output, const PlayerStrategies&);
};

//Human player: requires user interaction to make decisions
class HumanPlayer : public PlayerStrategies{
public:
    // Constructors and destructors. Not needed.
    HumanPlayer();
    HumanPlayer(const HumanPlayer&);
    ~HumanPlayer();

    // Main operations.
    virtual int pickCard(Hand *hand);
    virtual std::string displayCurrentStrategy();

    // Overrided methods in human player.
    virtual Player* selectPlayer();
    virtual Army* selectArmy(std::list<Army*> armies);
    virtual Territory* selectTerritoryCurrentlyOn(std::list<Army*> armies);
    virtual Territory* selectTerritoryWithCity(std::list<City*> cities);
    virtual std::pair<Territory*, int> selectNeighbouringTerritory(Territory*, Map*);
    virtual int selectOrAction(Card* card);

    // Operators.
    friend std::ostream& operator <<(std::ostream& output, const HumanPlayer&);
    HumanPlayer operator =(const HumanPlayer&);
};

//Greedy Computer: player that focuses on building cities or destroying opponents
class GreedyComputer : public PlayerStrategies{
 public:
     // Constructors and destructors. Not really needed.
     GreedyComputer();
     GreedyComputer(const GreedyComputer&);
     ~GreedyComputer();


    // Helpful methods.
    virtual int pickCard(Hand *hand);
    virtual std::string displayCurrentStrategy();
    virtual int selectOrAction(Card* card);

    // Operators.
    friend std::ostream& operator <<(std::ostream& output, const GreedyComputer&);
    GreedyComputer operator =(const GreedyComputer&);
};

//Moderate computer: control a region in which it just needs to occupy it with more armies than the opponents
class ModerateComputer : public PlayerStrategies{
 public:
     // Constructors and destructors. Not really needed.
     ModerateComputer();
     ModerateComputer(const ModerateComputer&);
     ~ModerateComputer();

    // Helpful methods.
    virtual int pickCard(Hand *hand);
    virtual std::string displayCurrentStrategy();
    virtual int selectOrAction(Card* card);

    // Operators.
    friend std::ostream& operator <<(std::ostream& output, const ModerateComputer&);
    ModerateComputer operator =(const ModerateComputer&);
}; 