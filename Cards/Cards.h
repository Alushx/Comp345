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

#include <string>
#include <array>
#include "../Player.h"
using namespace std;



class Card {
private:
	string good;
	string ability;
	string combinationtype;
	string action[2];

public:
	//Constructor
	Card()=default;
	Card(string good, string combinationtype, string action, string ability);
	Card(string good, string combinationType, string firstAction, string secondAction, string ability);
	~Card();//There are no pointers for this class
	//Copy constructor
	Card(const Card &c);
	string getGood();
	string getCombinationType();
	string getFirstAction();
	string getSecondAction();
	string getAbility();
	//display card
	void printCard();
	
	// Operators
	Card& operator=(const Card&);
private:
	friend ostream& operator<<(ostream&, const Card&);
	
};

class Deck {
private:
	Card *topCardptr;
	Card cards[34];
	int numPlayer;
public:
	//Constructor
	Deck();//Default
	Deck(int numPlayer);
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
	int getNumCards();
		// Operators
	friend ostream& operator<<(ostream&, const Deck&);
public:
	Deck& operator=(const Deck&);
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
public:
	Hand& operator=(const Hand&);
};
