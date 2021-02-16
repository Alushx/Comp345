#pragma once

#include <string>
#include <array>
#include "../Player.h"
using namespace std;



class Card {
private:
	string good;
	string combinationtype;
	string action[2];

public:
	//Constructor
	Card()=default;
	Card(string good, string combinationtype, string action);
	Card(string good, string combinationType, string firstAction, string secondAction);
	~Card();//There are no pointers for this class
	//Copy constructor
	Card(const Card &c);
	string getGood();
	string getCombinationType();
	string getFirstAction();
	string getSecondAction();

	//display card
	void printCard();

	// Operators
private:
	friend ostream& operator<<(ostream&, const Card&);
};

class Deck {
private:
	Card *topCardptr;
	Card cards[34];
public:
	//Constructor
	Deck();//Default
	//Copy constructor
	Deck(const Deck &d);
	//Deconstructor
	~Deck();
	void generateDeck();
	void printDeck();
	void shuffleDeck();
	Card *draw();
private:
	static int  myRandomGenerator(int j);
		// Operators
	friend ostream& operator<<(ostream&, const Deck&);
};

class Hand {
private:
	Deck* deck;
	Card *cards[6];//Face-up cards
public:
	Hand() = default;
	Hand(Deck* deck);
	//CopyConstructor
	Hand(const Hand &h);
	//Deconstructor
	~Hand();
	int getCardCost(int indexOfcard);
	Card* exchange(int cardIndex, Player* player);
	void printHand();
private:
	void shiftCards(int index);
		// Operators
	friend ostream& operator<<(ostream&, const Hand&);
};
