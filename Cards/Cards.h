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
	
	string getGood();
	string getCombinationType();
	string getFirstAction();
	string getSecondAction();

	//display card
	void printCard();
};

class Deck {
private:
	Card *topCardptr;
	Card cards[34];
public:
	//Construction
	Deck();
	void generateDeck();
	void printDeck();
	void shuffleDeck();
	Card *draw();
private:
	static int  myRandomGenerator(int j);
};

class Hand {
private:
	Deck* deck;
	Card *cards[6];//Face-up cards
public:
	Hand(Deck* deck);
	int getCardCost(int indexOfcard);
	Card* exchange(int cardIndex, Player* player);
	void printHand();
private:
	void shiftCards(int index);
};
