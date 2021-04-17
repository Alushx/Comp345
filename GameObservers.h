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
#include <list>
#include <iostream>
#include <vector>
using namespace std;

class Observer
{
public:
	virtual ~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

// the subject Class
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	virtual ~Subject();
private:
	list<Observer*>* _observers;

};

// Forward declarations to make the compiler happy.
class Player;
class Card;
class Hand;
class Map;

// A class that encapsulates each turn.
// Provides methods that allow the player to pick their card and play it.
class Turn : public Subject
{
private:
	Player* playerTurn;
	Card* selectedCard;
	Hand* gameHand;
	Map* gameMap;
	int maxNumOfTurns;

public:
	// Constructors and destructors.
	Turn();
	Turn(int, Map*, Hand*, Player* = nullptr);
	Turn(const Turn&);
	~Turn();

	// Setters and getters.
	Player* getPlayerTurn();
	void setPlayerTurn(Player*);
	Card* getSelectedCard();
	void setSelectedCard(Card*);
	Hand* getGameHand();
	void setGameHand(Hand*);
	Map* getGameMap();
	void setGameMap(Map*);
	int getMaxNumOfTurns();
	void setMaxNumOfTurns(int);

	// Service methods.
	void playTurn();

	// Operators.
	friend ostream& operator <<(ostream& output, const Turn& turn);
	const Turn& operator =(const Turn&);
};

class TurnView : public Observer
{
public :
	TurnView();
	TurnView(Turn* t);
	~TurnView();
	void Update();
	void display();
private:
	Turn* _subject;
};


class GameState : public Subject {
private:
	Map* map;
	vector<int> coins;
	vector<int> continents;
	vector<int> victoryPoints;
	vector<int> territories;
	vector<int> elixirAmount;

public:
	// Constructors & destructor
	GameState();
	GameState(Map* map);
	GameState(const GameState&);
	~GameState();

	// Accessors & Mutators
	vector<int> getCoins();
	vector<int> getContinents();
	vector<int> getVictoryPoints();
	vector<int> getTerritories();
	vector<int> getElixirAmount();
	void setCoins(vector<int>);
	void setContinents(vector<int>);
	void setVictoryPoints(vector<int>);
	void setTerritories(vector<int>);
	void setElixirAmount(vector<int>);

	// Functions
	void computeGameState();
};

class View: public Observer{
	// Member variable.
private:
	GameState *gmstate;

public:
	// Constructors & destructor
	View();
	View(GameState*);
	~View();

	// Function
	void display(int i);
	virtual void Update();

private:
	void printbar(int);
};
