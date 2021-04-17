#include "PlayerStrategies.h"
#include "Cards.h"
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

//===================================
// PlayerStrategies
//===================================

// Selects a player at random.
Player* PlayerStrategies::selectPlayer()
{
    // Setting things up.
    bool hasBot = false;
    int numOfPlayer = Player::getPlayerNum();
    if (Player::getBot() != nullptr)
    {
        numOfPlayer++;
        hasBot = true;
    }
        
    // Selecting player randomly.
    int choice = rand() % numOfPlayer;
    
    if (choice == Player::getPlayerNum() && hasBot)
        return Player::getBot();
    else
        return Player::getPlayerList()[choice];
}

// Selects an army at random.
Army* PlayerStrategies::selectArmy(list<Army*> armies)
{
    int choice = rand() % armies.size();

    for (Army* army : armies)
    {
        if (choice == 0)
            return army;
        choice--;
    }

    return nullptr;
}

// Select a territory currently on, at random.
Territory* PlayerStrategies::selectTerritoryCurrentlyOn(list<Army*> armies)
{
    vector<Territory*> territoriesCurrentlyOn = vector<Territory*>();

    // Make a set of all territories currently on.
    for (Army* army : armies)
    {
        territoriesCurrentlyOn.push_back(army->getPosition());
    }

    int choice = rand() % territoriesCurrentlyOn.size();

    return territoriesCurrentlyOn[choice];
}

// Select a territory with a city, at random.
Territory* PlayerStrategies::selectTerritoryWithCity(list<City*> cities)
{
    if (cities.size() == 0)
        return Player::getStartingRegion();

    int choice = (rand() % cities.size()) + 1;

    if (choice == cities.size())
        return Player::getStartingRegion();

    for (City* city : cities)
    {
        if (choice == 0)
            return city->getPosition();
        choice--;
    }

    return nullptr;
}

// Returns a territory-int pair at random.
pair<Territory*, int> PlayerStrategies::selectNeighbouringTerritory(Territory* currentTerritory, Map* map)
{
    std::map<Territory*, int> adjacentTerritories = map->getAdjacentTerritories(currentTerritory);
    
    int choice = rand() % adjacentTerritories.size();

    for (pair<Territory*, int> territory: adjacentTerritories)
    {
        if (choice == 0)
            return territory;
        choice--;
    }
}

// Allows human player to select any player.
Player* HumanPlayer::selectPlayer()
{
    Player* bot = Player::getBot();
    vector<Player*> playerList = Player::getPlayerList();
    bool hasBot = false;
    int playerNum = Player::getPlayerNum();
	int playerChoice = -1;

	// Lists all players and allows user to select which one.
	do
	{
		cout << "There are " << playerNum << " players." << endl;

		for (int i = 0; i < playerNum; i++)
		{
			cout << "\t " << (i + 1) << ") " << *playerList[i] << endl;
		}
		if (bot != NULL)
		{
			cout << "\t " << playerNum + 1 << ") " << *bot << endl;
			hasBot = true;
		}

		cout << "Select a player: ";
		cin >> playerChoice;

	} while (playerChoice < 1 || playerChoice > (hasBot ? playerNum + 1 : playerNum));

	// Returns pointer to player.
	if (playerChoice == playerNum + 1)
		return bot;
	else
		return playerList[playerChoice - 1];
}

// Allows human player to select an army.
Army* HumanPlayer::selectArmy(list<Army*> armies)
{
    if (armies.size() == 0)
    {
        cout << "There are no armies to choose from." << endl;
        return nullptr;
    }

    int playerChoice = -1;
    int i = 0;

    // Prints all armies and allows player to select one.
    do
    {
        cout << armies.front()->getOwnerName() << " has " << armies.size() << " armies." << endl;

        i = 0;
        for (Army* army : armies)
        {
            cout << "\t " << (i + 1) << ") " << *army << " in " << army->getPosition()->getName() << endl;
            i++;
        }

        cout << "Choose an army: ";
        cin >> playerChoice;
    } while (playerChoice > armies.size() || playerChoice <= 0);

    // Iterates over the list of armies to return the army.
    int j = 0;
    for (list<Army*>::iterator armyIterator = armies.begin(); armyIterator != armies.end(); armyIterator++)
    {
        j++;
        if (j == playerChoice)
        {
            return *armyIterator;
        }
    }

    return nullptr;
}

// Allows human player to select a territory with an army currently on it.
Territory* HumanPlayer::selectTerritoryCurrentlyOn(list<Army*> armies)
{
    if (armies.size() == 0)
    {
        cout << "There are no territories to choose from." << endl;
        return nullptr;
    }

    map<Territory*, Territory*> territoriesCurrentlyOn = map<Territory*, Territory*>();

    // Make a set of all territories currently on.
    for (Army* army : armies)
    {
        territoriesCurrentlyOn[army->getPosition()] = army->getPosition();
    }

    int playerChoice = -1;
    int i = 0;
    Territory* territory = nullptr;

    // Prints all territories and allows player to select one.
    do
    {
        i = 0;

        for (pair<Territory*, Territory*> territoryPair : territoriesCurrentlyOn)
        {
            territory = territoryPair.first;
            cout << "\t " << (i + 1) << ") " << *territory << endl;
            i++;
        }

        // Player makes a choice.
        cout << "Choose a territory: ";
        cin >> playerChoice;

    } while (playerChoice > armies.size() || playerChoice <= 0);

    int j = 1;

    // Looping through and finding the territory again.
    for (pair<Territory*, Territory*> territoryPair : territoriesCurrentlyOn)
    {
        if (j == playerChoice)
        {
            return territoryPair.first;
        }
        j++;
    }

    // Returning null if nothing found.
    return nullptr;
}

// Allows human player to select a territory with a city.
Territory* HumanPlayer::selectTerritoryWithCity(list<City*> cities)
{
    int i = 0;
    int playerChoice = -1;

    // Display options for player.
    do
    {
        cout << "Choose one of the following territories with cities." << endl;

        i = 1;

        cout << "\t 1) Starting Region" << endl;

        for (City* city : cities)
        {
            cout << "\t " << (++i) << ") " << *(city->getPosition()) << endl;
        }

        cout << "Select a territory: ";
        cin >> playerChoice;

    } while (playerChoice <= 0 || playerChoice > (cities.size() + 1));

    // Special case when starting region is selected.
    if (playerChoice == 1)
    {
        return Player::getStartingRegion();
    }

    int j = 2; // Other cities start from 2 in the player's eyes.

    // Loops through list and returns the appropriate position.
    for (City* city : cities)
    {
        if (playerChoice == j++)
        {
            return city->getPosition();
        }
    }

    cout << "\n DEBUG Player::selectTerritoryWithCity() - city not found. j = " << j << endl;
    return nullptr;
}

// Allows human player to select a neighbouring territory.
pair<Territory*, int> HumanPlayer::selectNeighbouringTerritory(Territory* currentTerritory, Map* map)
{
    std::map<Territory*, int> adjacentTerritories = map->getAdjacentTerritories(currentTerritory);

    int i = 0;
    int playerChoice = -1;

    do
    {
        i = 1;
        playerChoice = -1;

        cout << "Select the neighbouring territory: " << endl;

        // Display all options.
        for (pair<Territory*, int> neighbour : adjacentTerritories)
        {
            cout << "\t " << i++ << ") " << neighbour.first->getName() << ". Move cost: " << neighbour.second << endl;
        }

        cout << "Select the neighbouring territory you want: ";
        cin >> playerChoice;

    } while (playerChoice <= 0 || playerChoice > adjacentTerritories.size());

    int j = 1;

    // Find the option and return it.
    for (pair<Territory*, int> neighbour : adjacentTerritories)
    {
        if (j == playerChoice)
        {
            return neighbour;
        }

        j++;
    }

    // This should never happen.
    cout << "Error! Neighbouring territory not found!" << endl;
    return pair<Territory*, int>(nullptr, -1);
}

// Allows the player to select an action.
int HumanPlayer::selectOrAction(Card* aCard)
{
    int choiceNum = 0;
    do
    {
        cout << "Which of the following actions would you like to take?" << endl;
        cout << "\t 1) " << aCard->getFirstAction() << endl;
        cout << "\t 2) " << aCard->getSecondAction() << endl;

        cin >> choiceNum;

    } while (!(choiceNum == 1 || choiceNum == 2));

    return choiceNum;
}

// Bot selects destroy armies or build city cards. Or it selects one at random if neither are present.
int GreedyComputer::selectOrAction(Card* aCard)
{
    int choiceNum = 0;
    string keyWord1 = "";
    string keyWord2 = "";
    istringstream action1Stream(aCard->getFirstAction());
    istringstream action2Stream(aCard->getFirstAction());
    action1Stream >> keyWord1;
    action2Stream >> keyWord2;
    
    if (keyWord1 == "Build" || keyWord1 == "Destroy")
        return 1;
    else if (keyWord2 == "Build" || keyWord2 == "Destroy")
        return 2;
    else
        return (rand() % 2) + 1;
}

// Selects the action with move or add armies. If neither are present, it goes with a random option.
int ModerateComputer::selectOrAction(Card* aCard)
{
    int choiceNum = 0;
    string keyWord1 = "";
    string keyWord2 = "";
    istringstream action1Stream(aCard->getFirstAction());
    istringstream action2Stream(aCard->getFirstAction());
    action1Stream >> keyWord1;
    action2Stream >> keyWord2;

    if (keyWord1 == "Move" || keyWord1 == "Add")
        return 1;
    else if (keyWord2 == "Move" || keyWord2 == "Add")
        return 2;
    else
        return (rand() % 2) + 1;
}


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

// ===========================================================================
// Constructors, destructors, and operations to meet assignment requirements.
// ===========================================================================

PlayerStrategies::PlayerStrategies() {}
HumanPlayer::HumanPlayer() {}
GreedyComputer::GreedyComputer() {}
ModerateComputer::ModerateComputer() {}

PlayerStrategies::PlayerStrategies(const PlayerStrategies&) {}
HumanPlayer::HumanPlayer(const HumanPlayer&) {}
GreedyComputer::GreedyComputer(const GreedyComputer&) {}
ModerateComputer::ModerateComputer(const ModerateComputer&) {}

PlayerStrategies::~PlayerStrategies() {}
HumanPlayer::~HumanPlayer() {}
GreedyComputer::~GreedyComputer() {}
ModerateComputer::~ModerateComputer() {}

ostream& operator <<(ostream& output, const PlayerStrategies& other) { return output << "Abstract PlayerStrategies"; }
ostream& operator <<(ostream& output, const HumanPlayer& other) { return output << "HumanPlayer"; }
ostream& operator <<(ostream& output, const GreedyComputer& other) { return output << "GreedyComputer"; }
ostream& operator <<(ostream& output, const ModerateComputer& other) { return output << "ModerateComputer"; }

HumanPlayer HumanPlayer::operator =(const HumanPlayer& other) { return other; };
GreedyComputer GreedyComputer::operator =(const GreedyComputer& other) { return other; };
ModerateComputer ModerateComputer::operator =(const ModerateComputer& other) { return other; };