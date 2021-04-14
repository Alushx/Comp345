#include "PlayerStrategies.h"
#include "Cards.cpp"
using namespace std;

//HumanPlayer: requires user interaction to make decisions
int HumanPlayer::pickCard(Hand *hand){
    int index;
    cout << "Please enter the index of the card you want to pick or a negative number to exit: ";
	cin >> index;
    return index;
}

string HumanPlayer::displayCurrentStrategy() {
    return "Human Player";
}

//GreedyComputer: player that focuses on building cities or destroying opponents
int GreedyComputer::pickCard(Hand *hand){
    int cheapestCard = 0;
    Action act;
    Card *handcards = hand->getHandCards();
    //go through the hand
    //if current card's action(s) are building cities or destroying opponents
    //return that index
    for (int i = 0; i < 6; i++)
    {
        if(handcards[i].getFirstAction() == act.DESTROY_1_ARMY || handcards[i].getFirstAction() == act.BUILD_CITY ||
        handcards[i].getSecondAction() == act.DESTROY_1_ARMY || handcards[i].getSecondAction() == act.BUILD_CITY){
           return i;
        }
    }
    //otherwise return the index of the cheapest card
    return cheapestCard;
} 
string GreedyComputer::displayCurrentStrategy() {
    return "Greedy Computer";
}

//ModerateComputer: control a region in which it just needs to occupy it with more armies than the opponents
int ModerateComputer::pickCard(Hand *hand){
    int cheapestCard = 0;
    Action act;
    Ability ability;
    Card *handcards = hand->getHandCards();
    //go through the hand
    //if current card's action(s) have move or add army
    for (int i = 0; i < 6; i++)
    {
        if(handcards[i].getFirstAction().find("Add") !=std::string::npos || handcards[i].getFirstAction().find("Move") !=std::string::npos
        || handcards[i].getSecondAction().find("Add") !=std::string::npos || handcards[i].getSecondAction().find("Move") !=std::string::npos
        || handcards[i].getAbility() == ability.PLUS_ONE_MOVE || handcards[i].getAbility() == ability.PLUS_ONE_ARMY ||
            handcards[i].getAbility() == ability.IMMUNE_TO_ATTACK || handcards[i].getAbility() == ability.FYLING)
        {
            return i;
        }
    }
    //otherwise return the index of the cheapest card
    return cheapestCard;
} 
string ModerateComputer::displayCurrentStrategy() {
    return "Moderate Computer";
}
