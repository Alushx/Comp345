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

#include "GameObservers.h"
#include "PlayerStrategies.h"
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

using namespace std;

// ============================================
// GameObservers Implementation
// ============================================

Observer::~Observer()
{

}

Observer::Observer()
{

}

// ============================================
// Subject Implementation
// ============================================

Subject::Subject()
{
	_observers = new list<Observer*>;
}

Subject::~Subject()
{
	for (Observer* observer : *_observers)
	{
		if (observer != nullptr)
		{
			delete observer;
			observer = nullptr;
		}
	}
	delete _observers;
}

void Subject::Attach(Observer* o)
{
	_observers->push_back(o);
}

void Subject::Detach(Observer* o) 
{
	_observers->remove(o);
}

void Subject::Notify() 
{
	list<Observer*>::iterator i;
	for (i = _observers->begin(); i != _observers->end(); ++i) 
	{
		(*i)->Update();
	}
}

// ============================================
// Turn Implementation
// ============================================

// Default constructor. Makes everything a nullptr.
Turn::Turn()
{
	playerTurn = nullptr;
	selectedCard = nullptr;
	gameHand = nullptr;
	gameMap = nullptr;
	maxNumOfTurns = 0;
	selectedIndex = -1;
}

// Parameterized constructor. Sets selectedCard to nullptr.
Turn::Turn(int maxTurn, Map* map, Hand* hand, Player* player)
{
	gameMap = map;
	gameHand = hand;
	playerTurn = player;
	selectedCard = nullptr;
	maxNumOfTurns = maxTurn;
	selectedIndex = -1;
}

// Copy constructor. Creates a shallow copy of everything because the Turn shouldn't 
// actually contain any values.
Turn::Turn(const Turn& anotherTurn)
{
	gameMap = anotherTurn.gameMap;
	gameHand = anotherTurn.gameHand;
	playerTurn = anotherTurn.playerTurn;
	selectedCard = anotherTurn.selectedCard;
	maxNumOfTurns = anotherTurn.maxNumOfTurns;
	selectedIndex = anotherTurn.selectedIndex;
}

// Deconstructor. Doesn't actually do anything, because the members are used elsewhere. 
Turn::~Turn()
{
	gameMap = nullptr;
	gameHand = nullptr;
	playerTurn = nullptr;
	selectedCard = nullptr;
}

// Accessor for playerTurn.
Player* Turn::getPlayerTurn()
{
	return playerTurn;
}

// Mutator for playerTurn.
void Turn::setPlayerTurn(Player* player)
{
	playerTurn = player;
}

// Accessor for selectedCard.
Card* Turn::getSelectedCard()
{
	return selectedCard;
}

// Mutator for selectedCard.
void Turn::setSelectedCard(Card* card)
{
	selectedCard = card;
	Notify();
}

// Accessor for gameHand.
Hand* Turn::getGameHand()
{
	return gameHand;
}

// Mutator for gameHand.
void Turn::setGameHand(Hand* hand)
{
	gameHand = hand;
	Notify();
}

// Accessor for gameMap.
Map* Turn::getGameMap()
{
	return gameMap;
}

// Mutator for gameMap.
void Turn::setGameMap(Map* map)
{
	gameMap = map;
	Notify();
}

// Accessor for number of turns.
int Turn::getMaxNumOfTurns()
{
	return maxNumOfTurns;
}

// Mutator for number of turns.
void Turn::setMaxNumOfTurns(int newMax)
{
	maxNumOfTurns = newMax;
	Notify();
}

// Accessor for the index of the currently selected card.
int Turn::getSelectedIndex()
{
	return selectedIndex;
}

// Mutator for the index of the currently selected card.
void Turn::setSelectedIndex(int newIndex)
{
	selectedIndex = newIndex;
}



// Method that selects a card based on the player strategy, pays the cost of the card, and plays the card.
void Turn::playTurn()
{
	gameHand->printHand();
	int index = - 1;
	Card* card = nullptr;
	
	do
	{
		index = playerTurn->getStrategy()->pickCard(gameHand, playerTurn->getCoins());
		
		// Player skips their turn.
		if (index < 0 || index > 5)
			return;

		card = gameHand->exchange(index, playerTurn);
	} while (card == nullptr);

	setSelectedIndex(index);
	setSelectedCard(card);
	playerTurn->playCard(card, gameMap);
}

// Overloaded stream insertion operator. Just displays the player whose turn it is.
ostream& operator <<(ostream& output, const Turn& turn)
{
	if (turn.playerTurn == nullptr)
		return output << "Noone's turn.";
	else
		return output << turn.playerTurn->getName() << "'s turn.";
}

// Overloaded assignment operator.
const Turn& Turn::operator =(const Turn& anotherTurn)
{
	// Self check.
	if (this == &anotherTurn)
		return *this;

	// There's no need to deallocate any memory.
	gameMap = anotherTurn.gameMap;
	gameHand = anotherTurn.gameHand;
	playerTurn = anotherTurn.playerTurn;
	selectedCard = anotherTurn.selectedCard;
	maxNumOfTurns = anotherTurn.maxNumOfTurns;

	return *this;
}

// ============================================
// Game Implementation
// ============================================

TurnView::TurnView() 
{
	_subject = nullptr;
};

TurnView::TurnView(Turn* t) 
{
	_subject = t;
	_subject->Attach(this);
};

TurnView::~TurnView()
{
	_subject->Detach(this);
};

void TurnView::Update()
{
	display();
};

void TurnView::display() 
{

	cout << "Player: " <<_subject->getPlayerTurn() << ", selected : " << _subject->getSelectedCard()
		<< ", the card that he owes are :"<< _subject->getGameHand()<< ", the territories he owes are: " <<
		_subject->getGameMap() <<endl;
}

// ============================================
// GameState Implementation
// ============================================


// Constructors & destructor
GameState::GameState() {
	map = nullptr;
	coins = vector<int>(Player::getPlayerNum());
	continents = vector<int>(Player::getPlayerNum());
	victoryPoints = vector<int>(Player::getPlayerNum());
	territories = vector<int>(Player::getPlayerNum());
	elixirAmount = vector<int>(Player::getPlayerNum());
}

GameState::GameState(Map* aMap)
{
	map = aMap;
	coins = vector<int>(Player::getPlayerNum());
	continents = vector<int>(Player::getPlayerNum());
	victoryPoints = vector<int>(Player::getPlayerNum());
	territories = vector<int>(Player::getPlayerNum());
	elixirAmount = vector<int>(Player::getPlayerNum());
}

GameState::GameState(const GameState& other) {
	
	// Intentionally makes shallow copy.
	this->map = other.map;
	this->coins = other.coins;
	this->continents = other.continents;
	this->victoryPoints = other.victoryPoints;
	this->territories = other.territories;
	this->elixirAmount = other.elixirAmount;
}

GameState::~GameState()
{
	// Map is deleted outside of this class.
	map = nullptr;
}

// Accessors & Mutators
vector<int> GameState::getCoins() {
	return coins;
}

vector<int> GameState::getContinents() {
	return continents;
}

vector<int> GameState::getVictoryPoints() {
	return victoryPoints;
}

vector<int> GameState::getTerritories() {
	return territories;
}

vector<int> GameState::getElixirAmount() {
	return elixirAmount;
}

void GameState::setCoins(vector<int> x) {
	this->coins = x;
}

void GameState::setContinents(vector<int> x) {
	this->continents = x;
}

void GameState::setVictoryPoints(vector<int> x) {
	this->victoryPoints = x;
}

void GameState::setTerritories(vector<int> x) {
	this->territories = x;
}

void GameState::setElixirAmount(vector<int> x){
	this->elixirAmount = x;
}

// Functions
void GameState::computeGameState() {
	calculateScore(map);

	vector<Player*> players = Player::getPlayerList();
	for (int i = 0; i < Player::getPlayerNum(); i++)
	{
		coins[i] = players[i]->getCoins();
		continents[i] = players[i]->computeContinentsOwned(map);
		victoryPoints[i] = players[i]->getScore();
		territories[i] = players[i]->getPlayerTerritories()->size();
		elixirAmount[i] = players[i]->getOwnNumElixer();
	}


	Notify();
}

// ============================================
// View Implementation
// ============================================

// Default Constructors  
View :: View(){
	gmstate = nullptr;
}
// Parameterized constructor
View :: View(GameState * gt){
	gmstate = gt;
	gt->Attach(this);
}
//Destructor
View :: ~View(){
	// Game state deletes this. Not the other way around.
}

//Display bar graph of a player
void View :: display(int i){
	// Player
	cout << Player::getPlayerList()[i]->getName() << ":" << endl;
	// Victory Points
	cout << "\t" << gmstate->getVictoryPoints()[i]<<" Victory Points:";
	printbar(gmstate->getVictoryPoints()[i]);
	// Continents
	cout << "\t" << gmstate->getContinents()[i]<<" Continents:";
	printbar(gmstate->getContinents()[i]);
	// Region
	cout << "\t" << gmstate->getTerritories()[i]<<" Region:";
	printbar(gmstate->getTerritories()[i]);
	// Elixer
	cout << "\t" << gmstate->getElixirAmount()[i] <<" Elixer:";
	printbar(gmstate->getElixirAmount()[i]);
	// Coins
	cout << "\t" << gmstate->getCoins()[i] <<" Coins:";
	printbar(gmstate->getCoins()[i]);
}

//Print bar for each
void View :: printbar(int length){
	for(int i=0;i<length;i++){
		cout << "|";
	}
	cout << endl;
}

void View::Update()
{
	for (int i = 0; i < Player::getPlayerNum(); i++)
	{
		display(i);
	}
}

//=========================================
// CardPickViewer and PlayerTurnViewer
//=========================================

// Default constructor for PlayerTurnViewer.
PlayerTurnViewer::PlayerTurnViewer()
{
	subject = nullptr;
	playerTurn = nullptr;
	turnCount = 0;
}

// Parameterized constructor. Takes care of attaching.
PlayerTurnViewer::PlayerTurnViewer(Turn* turn)
{
	subject = turn;
	playerTurn = turn->getPlayerTurn();
	turnCount = 0;
	turn->Attach(this);
}

// Copy constructor. Takes care of attaching to subject.
PlayerTurnViewer::PlayerTurnViewer(const PlayerTurnViewer& other)
{
	subject = other.subject;
	playerTurn = other.playerTurn;
	turnCount = other.turnCount;
	subject->Attach(this);
}

// Destructor. Holds no values itself, so only detaches.
PlayerTurnViewer::~PlayerTurnViewer()
{
	// Nothing dynamically allocated in this class, so nothing to delete.
}

// Prints the turn # and the player whose turn it is.
void PlayerTurnViewer::Update()
{
	if (subject->getPlayerTurn() != playerTurn)
	{
		playerTurn = subject->getPlayerTurn();
		cout << "Observer::PlayerTurnViewer: Turn " << (turnCount++ / Player::getPlayerNum()) + 1 << ": " << playerTurn->getName() << " is now playing!" << endl;
	}
}

// Outputs class name.
ostream& operator <<(ostream& strm, const PlayerTurnViewer& obj)
{
	return strm << "PlayerTurnViewer";
}

// Assigns shallow copy of members. Automatically attaches and detaches as needed.
PlayerTurnViewer PlayerTurnViewer::operator =(const PlayerTurnViewer& other)
{
	if (&other == this)
		return *this;

	// No need to delete any memory since everything is dynamic.
	// As an observer, you should not have a deep copy. So things are shallow.
	subject->Detach(this);
	subject = other.subject;
	playerTurn = other.playerTurn;
	turnCount = other.turnCount;
	subject->Attach(this);

	return *this;
}

// Default constructor.
CardPickViewer::CardPickViewer()
{
	subject = nullptr;
	selectedCard = nullptr;
}

// Parameterized constructor. Attaches as needed.
CardPickViewer::CardPickViewer(Turn* turn)
{
	subject = turn;
	selectedCard = turn->getSelectedCard();
	subject->Attach(this);
}

// Copy constructor. Attaches as needed.
CardPickViewer::CardPickViewer(const CardPickViewer& other)
{
	subject = other.subject;
	selectedCard = other.selectedCard;
	subject->Attach(this);
}

// Deconstructor. Only detaches.
CardPickViewer::~CardPickViewer()
{

}

// Outputs the card name, index, and cost.
void CardPickViewer::Update()
{
	int indexCosts[] = { 0,1,1,2,2,3 };
	Card;
	if (selectedCard != subject->getSelectedCard())
	{
		selectedCard = subject->getSelectedCard();

		cout << "Observer::CardPickViewer: " << subject->getPlayerTurn()->getName() << " has selected " << selectedCard->getGood() << " in index " << subject->getSelectedIndex()
			<< " and has paid " << indexCosts[subject->getSelectedIndex()] << " for it." << endl;
	}
}

// Outputs class name.
ostream& operator <<(ostream& stream, const CardPickViewer& obj)
{
	return stream << "CardPickViewer";
}

// Assigns members. Attaches and detaches as required.
CardPickViewer CardPickViewer::operator =(const CardPickViewer& other)
{
	if (&other == this)
		return *this;

	// No need to delete stuff.
	subject->Detach(this);
	subject = other.subject;
	selectedCard = other.selectedCard;
	subject->Attach(this);

	return *this;
}

// Default constructor.
PlayerActionViewer::PlayerActionViewer()
{
	subject = nullptr;
	playerAction = "";
}

// Parameterized constructor. Attaches self to player.
PlayerActionViewer::PlayerActionViewer(Player* player)
{
	subject = player;
	playerAction = player->getCurrentAction();
	subject->Attach(this);
}

// Copy constructor.
PlayerActionViewer::PlayerActionViewer(const PlayerActionViewer& other)
{
	subject = other.subject;
	playerAction = other.playerAction;
	subject->Attach(this);
}

// Destructor. Does nothing.
PlayerActionViewer::~PlayerActionViewer()
{

}

// Prints the player's current action.
void PlayerActionViewer::Update()
{
	if (subject->getCurrentAction() != playerAction)
	{
		playerAction = subject->getCurrentAction();
		cout << "Observer::PlayerActionViewer: " << playerAction << endl;
	}
}

// Returns class name.
ostream& operator <<(ostream& strem, const PlayerActionViewer& obj)
{
	return strem << "PlayerActionViewer";
}

// Assignment operator. Attaches and detaches as needed.
PlayerActionViewer PlayerActionViewer::operator =(const PlayerActionViewer& other)
{
	if (&other == this)
		return *this;

	subject->Detach(this);
	subject = other.subject;
	playerAction = other.playerAction;
	subject->Attach(this);

	return *this;
}

// CardBonusViewer default constructor.
CardBonusViewer::CardBonusViewer()
{
	subject = nullptr;
	moveBonus = 0;
	armyBonus = 0;
	flightBonus = 0;
	immunityBonus = false;
}

// Parameterized constructor. Adds self to the subject.
CardBonusViewer::CardBonusViewer(Player* player)
{
	subject = player;
	moveBonus = player->getCardMoveBonus();
	armyBonus = player->getCardArmyBonus();
	flightBonus = player->getCardFlightBonus();
	immunityBonus = player->getCardImmunityBonus();
	subject->Attach(this);
}

// Copy constructor. Automatically adds self to the subject.
CardBonusViewer::CardBonusViewer(const CardBonusViewer& other)
{
	subject = other.subject;
	moveBonus = other.moveBonus;
	armyBonus = other.armyBonus;
	flightBonus = other.flightBonus;
	immunityBonus = other.immunityBonus;
	subject->Attach(this);
}

// Destructor. Does nothing.
CardBonusViewer::~CardBonusViewer() {}

// Prints appropriate message if a bonus changes.
void CardBonusViewer::Update()
{
	if (subject->getCardMoveBonus() != moveBonus)
	{
		moveBonus = subject->getCardMoveBonus();
		cout << "Observer::CardBonusViewer: " << subject->getName() << " now has " << moveBonus << " bonus moves." << endl;
	}
	if (subject->getCardArmyBonus() != armyBonus)
	{
		armyBonus = subject->getCardArmyBonus();
		cout << "Observer::CardBonusViewer: " << subject->getName() << " now has " << armyBonus << " bonus armies." << endl;
	}
	if (subject->getCardFlightBonus() != flightBonus)
	{
		flightBonus = subject->getCardFlightBonus();
		cout << "Observer::CardBonusViewer: " << subject->getName() << " now has " << flightBonus << " bonus flight." << endl;
	}
	if (subject->getCardImmunityBonus() != immunityBonus)
	{
		immunityBonus = subject->getCardImmunityBonus();
		cout << "Observer::CardBonusViewer: " << subject->getName() << (immunityBonus ? " has " : " no longer has ") << "immunity." << endl;
	}
}

// Prints class name.
ostream& operator <<(ostream& strm, const CardBonusViewer& obj) 
{
	return strm << "CardBonusViewer";
}

// Assigns values. Attaches and detaches as appropriate.
CardBonusViewer CardBonusViewer::operator =(const CardBonusViewer& other)
{
	if (&other == this)
		return *this;

	subject->Detach(this);
	subject = other.subject;
	moveBonus = other.moveBonus;
	armyBonus = other.armyBonus;
	flightBonus = other.flightBonus;
	immunityBonus = other.immunityBonus;
	subject->Attach(this);

	return *this;
}



