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
#include "Player.h"
#include "Cards/Cards.h"
#include "Map.h"
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
}

// Parameterized constructor. Sets selectedCard to nullptr.
Turn::Turn(Map* map, Hand* hand, Player* player)
{
	gameMap = map;
	gameHand = hand;
	playerTurn = player;
	selectedCard = nullptr;
}

// Copy constructor. Creates a shallow copy of everything because the Turn shouldn't 
// actually contain any values.
Turn::Turn(const Turn& anotherTurn)
{
	gameMap = anotherTurn.gameMap;
	gameHand = anotherTurn.gameHand;
	playerTurn = anotherTurn.playerTurn;
	selectedCard = anotherTurn.selectedCard;
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

// Method that selects a card based on the player strategy, pays the cost of the card, and plays the card.
void Turn::playTurn()
{
	// Depends on the implementation of PlayerStrategies and their selectCard().
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
	return *this;
}

// ============================================
// Game Implementation
// ============================================

Game::Game() 
{
	_subject = nullptr;
};

Game::Game(Turn* t) 
{
	_subject = t;
	_subject->Attach(this);
};

Game::~Game()
{
	_subject->Detach(this);
};

void Game::Update()
{
	display();
};

void Game::display() 
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
	Map* map = nullptr;
	coins = 0;
	continents = 0;
	victoryPoints = 0;
	regions = 0;
	elixirAmount = 0;
	score = 0;
}

GameState::GameState(const GameState& other) {
	this->coins = other.coins;
	this->continents = other.continents;
	this->victoryPoints = other.victoryPoints;
	this->regions = other.regions;
	this->elixirAmount = other.elixirAmount;
	this->score = other.score;
}

GameState::~GameState()
{
	Map* map = nullptr;
	coins = 0;
	continents = 0;
	victoryPoints = 0;
	regions = 0;
	elixirAmount = 0;
	score = 0;//Score and VictoryPoints are the same****
}

// Accessors & Mutators
int GameState::getCoins() {
	return coins;
}

int GameState::getContinents() {
	return continents;
}

int GameState::getVictoryPoints() {
	return victoryPoints;
}

int GameState::getRegions() {
	return regions;
}

int GameState::getElixirAmount() {
	return elixirAmount;
}

int GameState::getScore() {
	return score;
}

void GameState::setCoins(int x) {
	this->coins = x;
}

void GameState::setContinents(int x) {
	this->continents = x;
}

void GameState::setVictoryPoints(int x) {
	this->victoryPoints = x;
}

void GameState::setRegions(int x) {
	this->regions = x;
}

void GameState::setElixirAmount(int x) {
	this->elixirAmount = x;
}

void GameState::setScore(int x) {
	this->score = x;
}

// Functions
void displayStats(Map* map) {
	// Displays stats
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
}
//Destructor
View :: ~View(){
	delete gmstate;
	gmstate=NULL;
}

//Display bar graph of a player
void View :: display(){

//Victory Points
cout <<gmstate->getVictoryPoints()<<" Victory Points:";
printbar(gmstate->getVictoryPoints());
//Continents
cout <<gmstate->getContinents()<<" Continents:";
printbar(gmstate->getContinents());
//Region
cout <<gmstate->getRegions()<<" Region:";
printbar(gmstate->getRegions());
//Elixer
cout <<gmstate->getElixirAmount()<<" Elixer:";
printbar(gmstate->getElixirAmount());
//Coins
cout <<gmstate->getCoins()<<" Coins:";
printbar(gmstate->getCoins());
}

//Print bar for each
void View :: printbar(int length){
	for(int i=0;i<length;i++){
		cout << "|";
	}
	cout << endl;
}