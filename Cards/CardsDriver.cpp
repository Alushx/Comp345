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

#include <string>
#include "Cards.h"
#include <iostream>
using namespace std;

int main() {

	int hello;
    Player* player = new Player();

    // create a deck
    Deck deck = Deck();

    // generate the cards
    deck.generateDeck();
    cout << "\n\n___________________________________________________Initial Deck\n\n" << endl;
    deck.printDeck();

    // shuffle the deck
    deck.shuffleDeck();
    cout << "\n\n____________________________________________________ Shuffled Deck\n\n" << endl;
    deck.printDeck();


    cout << "\n\n___________________________________________________Card Space\n\n" << endl;
    // draw initial hand
    Hand hand = Hand(&deck);
   // hand.printHand();
	//

    //Testing exchange method
    int coins = 8;
    int index = 0;
    while (index >= 0) {
        hand.printHand();
        cout << "Please enter the index of the card you want tp pick or a negative number to exit: ";
        cin >> index;
        hand.exchange(index, player);
    }
}