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
using namespace std;

class Observer
{
public:
	~Observer();
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
	~Subject();
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

public:
	// Constructors and destructors.
	Turn();
	Turn(Map*, Hand*, Player* = nullptr);
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

	// Service methods.
	void playTurn();

	// Operators.
	friend ostream& operator <<(ostream& output, const Turn& turn);
	const Turn& operator =(const Turn&);
};

class Game : public Observer
{
public :
	Game();
	Game(Turn* t);
	~Game();
	void Update();
	void display();
private:
	Turn* _subject;
};
