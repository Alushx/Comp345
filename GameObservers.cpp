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
#include "Cards.h"
#include "Map.h"
#include "Game.h"
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
	coins = vector<int>(Player::getPlayerNum());
	continents = vector<int>(Player::getPlayerNum());
	victoryPoints = vector<int>(Player::getPlayerNum());
	territories = vector<int>(Player::getPlayerNum());
	elixirAmount = vector<int>(Player::getPlayerNum());
}

GameState::GameState(Map* map)
{
	Map* map = map;
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
	Map* map = nullptr;
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
}
//Destructor
View :: ~View(){
	delete gmstate;
	gmstate=NULL;
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
