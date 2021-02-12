#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <array>
using namespace std;



class Card {
public:
	string good;
	string combinationtype;
	string action[2];

	//Constructor
	Card()= default;
	Card(string good, string combinationtype, string action);
	Card(string good, string combinationType, string firstAction, string secondAction);

	//display card
	void printCard();
};

class Deck {
public:
	Card *topCardptr;
	Card cards[43];
	//Construction
	Deck();
	void generateDeck();
	void printDeck();
	void shuffleDeck();
	Card *draw();
};

class Hand {
public:
	Deck* deck;
	Card *cards[6];//Face-up cards
	Hand(Deck* deck);
	int getCardCost(int indexOfcard);
	Card* exchange(int cardIndex, int* playerCoins);
	void printHand();
private:
	void shiftCards(int index);
};
#endif //CARDS_H