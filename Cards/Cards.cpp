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
#include <random>
#include <algorithm>
#include <stdio.h>
#include "../Player.h"
using namespace std;

const struct Action {
        string MOVE_2_ARMY = "Move 2 army";
        string MOVE_3_ARMY = "Move 3 army";
        string MOVE_4_ARMY = "Move 4 army";
        string MOVE_5_ARMY = "Move 5 army";
        string MOVE_6_ARMY = "Move 6 army";
        string BUILD_CITY = "Build city";
        string ADD_1_ARMY = "Add 1 army";
        string ADD_2_ARMY = "Add 2 army";
        string ADD_3_ARMY = "Add 3 army";
        string ADD_4_ARMY = "Add 4 army";
        string DESTROY_1_ARMY = "Destroy 1 army";
};

struct Good {
    //2 players cards(27)
    string ANCIENT_PHOENIX = "Ancient Phoenix";
    string ANCIENT_TREE_SPIRIT = "Ancient Tree Spirit";
    string CURSED_BANSHEE = "Cursed Banshee";
    string CURSED_KING = "Cursed King";
    string CURSED_TOWER = "Cursed Tower";
    string DIRE_EYE = "Dire Eye";
    string DIRE_GOBLIN = "Dire Goblin";
    string FOREST_ELF = "Forest Elf";
    string FOREST_PIXIE = "Forest Pixie";
    string GRAVEYARD = "Graveyard";
    string NIGHT_HYDRA = "Night Hydra";
    string NIGHT_WIZARD = "Night Wizard";
    string NOBLE_KNIGHT = "Noble Knight";
    string STRONGHOLD = "Stronghold";
    string ANCIENT_SAGE = "Ancient Sage";
    string ANCIENT_WOODS = "Ancient Woods";
    string CURSED_GARGOYLES = "Cursed Gargoyles";
    string CURSED_MAUSOLEUM = "Cursed Mausoleum";
    string DIRE_DRAGON = "Dire Dragon";
    string DIRE_GIANT = "Dire Giant";
    string DIRE_OGRE = "Dire Ogre";
    string FOREST_GNOME = "Forest Gnome";
    string FOREST_TREE_TOWN = "Forest Tree Town";
    string LAKE = "Lake";
    string NIGHT_VILLAGE = "Night Village";
    string NOBLE_HILLS = "Noble Hills";
    string NOBLE_UNICORN = "Noble Unicorn";
    //3 players cards(32)
    string ARCANE_MANTICORE = "Arcane Manticore";
    string ARCANE_TEMPLE = "Arcane Temple";
    string MOUNTAIN_TREASURY = "Mountain Treasury";
    string ARCANE_SPHINX = "Arcane Sphinx";
    string MOUNTAIN_DWARF = "Mountain Dwarf";
    //4 player cards(34)
    string CASTLE = "Castle";
    string CASTLE_2 = "Castle 2";
};

struct CombinationType {
    string SINGLE = " ";
    string OR = "OR";
    string AND = "AND";
};


//Card

//Constructor
Card::Card(string gd,string ctype, string actn){
    good = gd;
    combinationtype = ctype;
    action[0] = actn;
}

Card::Card(string gd, string ctype, string firstAction, string secondAction) {
    good = gd;
    combinationtype = ctype;
    action[0] = firstAction;
    action[1] = secondAction;
}
//Copy constructor
Card :: Card(const Card &c){
    good = c.good;
    combinationtype = c.combinationtype;
    action[0] = c.action[0];
    action[1] = c.action[1];
}
//Deconstructor
Card :: ~Card(){}; // There are no pointers for this class
//Getters
string Card ::getGood(){
    return good;
}
string Card ::getCombinationType(){
    return combinationtype;
}
string Card ::getFirstAction(){
    return action[0];
}
string Card ::getSecondAction(){
    return action[1];
}

void Card::printCard() {
    CombinationType comp;
    cout << "\tGood: "<< good<< endl;
    cout << "\tAction: " << action[0]<< endl;
    if (combinationtype != comp.SINGLE) {
        if (combinationtype == comp.AND) cout << "\tAND" << endl;
        else if (combinationtype == comp.OR)cout << "\tOR" << endl;
        cout << "\tAction: " << action[1];
    }
   
    
}
// toString Cards
ostream& operator<<(ostream& strm, const Card& card)
{
	return strm << "Good: " << card.good 
    << "\nAction(s): " << card.action[0] << "\n" << card.combinationtype << "\n"
    << card.action[1] << endl;
}

Card& Card::operator=(const Card& anotherCard)
{
    if (&anotherCard == this)
        return *this;

    good = anotherCard.good;
    combinationtype = anotherCard.combinationtype;
    action[0] = anotherCard.action[0];
    action[1] = anotherCard.action[1];

    return *this;
}

//Deck
Deck::Deck() {
    topCardptr = &cards[0];//Points to the top of the deck.
    numPlayer = 2;
}
Deck::Deck(int nPlayer){
    topCardptr = &cards[0];
    numPlayer = nPlayer;
} 
//CopyConstructor
Deck::Deck(const Deck &d){
    topCardptr = d.topCardptr;
    for(int i=0;i<getNumCards();i++){
        cards[i] = d.cards[i];
    }
}
//Deconstructor
Deck :: ~Deck(){
    // topCardptr is not dynamically allocated therefore, no need to delete it.
    topCardptr = nullptr;
}
//Return the number of cards that will be used
int Deck :: getNumCards(){
    if(numPlayer == 2) return 27;
    if(numPlayer == 3) return 32;
    if(numPlayer == 4) return 34;
}  
//Displays the whole deck
void Deck::printDeck() {
    for (int i = 0; i < getNumCards(); i++) {
        cout << "Card " << i + 1 << endl;
        cards[i].printCard();
        cout << endl;
    }
}
int Deck :: myRandomGenerator(int j) {
   return rand() % j;
}
//Shuffle the content of the whole array.
void Deck::shuffleDeck() {
    srand(time(0)); 
    random_shuffle(&cards[0], &cards[getNumCards()], myRandomGenerator);
}
// topCardptr points to the top of the deck
//When a card is drawn the pointer topCard move to the next card.
//return the drawn card
Card *Deck::draw() {
    Card* card = topCardptr;
    topCardptr++;
    return card;
}

//Creates the whole deck
void Deck ::generateDeck() {
    Good gd;
    Action act;
    CombinationType ctype;
    
    cards[0] = Card(gd.FOREST_PIXIE, ctype.SINGLE, act.MOVE_4_ARMY);
    cards[1] = Card(gd.STRONGHOLD, ctype.SINGLE, act.BUILD_CITY);
    cards[2] = Card(gd.ANCIENT_PHOENIX, ctype.SINGLE, act.MOVE_5_ARMY);
    cards[3] = Card(gd.ANCIENT_TREE_SPIRIT, ctype.SINGLE, act.ADD_4_ARMY);
    cards[4] = Card(gd.ANCIENT_WOODS, ctype.AND, act.BUILD_CITY, act.ADD_1_ARMY);
    cards[5] = Card(gd.ANCIENT_SAGE , ctype.SINGLE, act.MOVE_3_ARMY);
    cards[6] = Card(gd.CURSED_BANSHEE, ctype.SINGLE, act.MOVE_6_ARMY);
    cards[7] = Card(gd.CURSED_GARGOYLES, ctype.SINGLE, act.MOVE_5_ARMY);
    cards[8] = Card(gd.CURSED_KING , ctype.OR, act.ADD_3_ARMY,act.MOVE_4_ARMY);
    cards[9] = Card(gd.CURSED_MAUSOLEUM, ctype.SINGLE, act.BUILD_CITY);
    cards[10] = Card(gd.CURSED_TOWER, ctype.SINGLE, act.BUILD_CITY);
    cards[11] = Card(gd.DIRE_DRAGON, ctype.AND, act.ADD_3_ARMY,act.DESTROY_1_ARMY);
    cards[12] = Card(gd.DIRE_GIANT, ctype.AND, act.ADD_3_ARMY,act.DESTROY_1_ARMY);
    cards[13] = Card(gd.DIRE_EYE, ctype.SINGLE, act.ADD_4_ARMY);
    cards[14] = Card(gd.DIRE_GOBLIN, ctype.SINGLE, act.MOVE_4_ARMY);
    cards[15] = Card(gd.DIRE_OGRE, ctype.SINGLE, act.MOVE_2_ARMY);
    cards[16] = Card(gd.LAKE, ctype.OR, act.ADD_2_ARMY,act.MOVE_3_ARMY);
    cards[17] = Card(gd.FOREST_ELF, ctype.OR,  act.ADD_3_ARMY,act.MOVE_2_ARMY);
    cards[18] = Card(gd.FOREST_GNOME, ctype.SINGLE,act.MOVE_2_ARMY);
    cards[19] = Card(gd.FOREST_TREE_TOWN , ctype.SINGLE, act.BUILD_CITY);
    cards[20] = Card(gd.GRAVEYARD, ctype.SINGLE, act.ADD_2_ARMY);
    cards[21] = Card(gd.NOBLE_HILLS, ctype.SINGLE, act.ADD_3_ARMY);
    cards[22] = Card(gd.NOBLE_KNIGHT, ctype.AND, act.ADD_4_ARMY, act.DESTROY_1_ARMY);
    cards[23] = Card(gd.NOBLE_UNICORN, ctype.AND, act.MOVE_4_ARMY, act.ADD_1_ARMY);
    cards[24] = Card(gd.NIGHT_HYDRA, ctype.AND, act.MOVE_4_ARMY,act.DESTROY_1_ARMY);
    cards[25] = Card(gd.NIGHT_VILLAGE, ctype.SINGLE, act.BUILD_CITY);
    cards[26] = Card(gd.NIGHT_WIZARD, ctype.AND, act.ADD_4_ARMY, act.DESTROY_1_ARMY);

    //3 Player cards
    if(numPlayer >= 3){
    cards[27] = Card(gd.ARCANE_SPHINX, ctype.OR, act.ADD_3_ARMY, act.MOVE_4_ARMY);// 3 Player
    cards[28] = Card(gd.ARCANE_MANTICORE, ctype.AND, act.ADD_4_ARMY, act.DESTROY_1_ARMY);//3 Player
    cards[29] = Card(gd.ARCANE_TEMPLE, ctype.SINGLE, act.MOVE_3_ARMY);// 3Player
    cards[30] = Card(gd.MOUNTAIN_DWARF, ctype.AND, act.ADD_2_ARMY, act.DESTROY_1_ARMY);//3 Player
    cards[31] = Card(gd.MOUNTAIN_TREASURY, ctype.SINGLE, act.MOVE_3_ARMY);// 3 Player
    }
    //4 Player cards
    if(numPlayer >= 4){
    cards[32] = Card(gd.CASTLE, ctype.OR, act.ADD_4_ARMY,act. BUILD_CITY);//4 player 
    cards[33] = Card(gd.CASTLE_2, ctype.AND, act.MOVE_3_ARMY,act.BUILD_CITY);//4 Player
   }

}

// toString Deck
ostream& operator<<(ostream& strm, const Deck& deck)
{
	return strm << "Deck has 34 cards";
}

// Assignment operator.
Deck& Deck::operator=(const Deck& anotherDeck)
{
    if (&anotherDeck == this)
        return *this;

    for (int i = 0; i < 34; i++)
    {
        cards[i] = anotherDeck.cards[i];
    }

    topCardptr = &cards[0];
}   

//Hand

//Constructor
Hand::Hand(Deck* dk) {
    deck = dk;
 //Initializing the cards for the face-up cards by drawing from the deck
    for (int i = 0; i < 6; i++) {
        cards[i] = deck->draw();
    }
}
//CopyConstructor
Hand::Hand(const Hand &h){
    deck = new Deck(*(h.deck));
    for (int i = 0; i < 6; i++)
    {
        cards[i] = deck->draw();
    }
    
}
//Destructor
Hand::~Hand(){
    //deck is not dynamically allocated pointer therefore, no need to delete it
    deck = nullptr;
}
//Returns the cost of a card depending on where the card is placed in the cards space
int Hand::getCardCost(int indexOfcard) {
    if (indexOfcard == 0) return 0;
    else if (indexOfcard == 1) return 1;
    else if (indexOfcard == 2) return 1;
    else if (indexOfcard == 3) return 2;
    else if (indexOfcard == 4) return 2;
    else if (indexOfcard == 5) return 3;
}

//Shifts cards when a card is picked
//Index: 0 1 2 3 4 5
void Hand::shiftCards(int index) {
    for (int i = index; i < 5; i++) {
        cards[i] = cards[i + 1];//cards are shift to the left
    }
}


//Allows player to select the card from its position in the row
//Then Pay the coin cost
Card* Hand::exchange(int cardIndex, Player* player) {

    int cost = getCardCost(cardIndex);
    if ( !player->payCoin( cost )) return nullptr;

    Card* pickedCard = (cards[cardIndex]);// save picked card

    shiftCards(cardIndex);// shift cards to the left

    cards[5] = deck->draw(); // draw a new card from the deck

    return pickedCard;
}


//To be implemented
void Hand::printHand() {
    //get the goods for each card
    string goodCard[6];
    string ctypeCard[6];
    string firstAction[6];
    string secondAction[6];
    for(int i=0;i<6;i++){
        goodCard[i] = cards[i]->getGood();
    }
    //get the combinationtype for each card in the card space
    for(int i=0;i<6;i++){
        ctypeCard[i] = cards[i]->getCombinationType();
    }
    //get First Action for each card in the card space
    for(int i=0;i<6;i++){
        firstAction[i] = cards[i]->getFirstAction();
    }
    //get Second Action for each card in the card space
    for(int i=0;i<6;i++){
        secondAction[i] = cards[i]->getSecondAction();
    }
    string spaces[6] = { "|","|" ,"|" ,"|" ,"|" ,"|" };

    for (int i = 0; i < 211; i++) {
        cout << "_";
    }
     //c_str() converts cpp string to c string.
    printf("\n|Good: %-28s|Good: %-28s|Good: %-28s|Good: %-28s|Good: %-28s|Good: %-28s|\n", goodCard[0].c_str(), goodCard[1].c_str(), goodCard[2].c_str(),
        goodCard[3].c_str(), goodCard[4].c_str(), goodCard[5].c_str());

    printf("|Action(s): %24sAction(s): %24sAction(s): %24sAction(s): %24sAction(s): %24sAction(s): %24s\n", 
        spaces[0].c_str(), spaces[1].c_str(), spaces[2].c_str(), spaces[3].c_str(), spaces[4].c_str(), spaces[5].c_str());

    printf("|%-34s|%-34s|%-34s|%-34s|%-34s|%-34s|\n", firstAction[0].c_str(), firstAction[1].c_str(), firstAction[2].c_str(),
        firstAction[3].c_str(), firstAction[4].c_str(), firstAction[5].c_str());

    printf("|%-34s|%-34s|%-34s|%-34s|%-34s|%-34s|\n", ctypeCard[0].c_str(), ctypeCard[1].c_str(), ctypeCard[2].c_str(),
        ctypeCard[3].c_str(), ctypeCard[4].c_str(), ctypeCard[5].c_str());

    printf("|%-34s|%-34s|%-34s|%-34s|%-34s|%-34s|\n", secondAction[0].c_str(), secondAction[1].c_str(), secondAction[2].c_str(),
       secondAction[3].c_str(), secondAction[4].c_str(), secondAction[5].c_str());

    printf("|Cost: 0 %27sCost: 1 %27sCost: 1 %27sCost: 2 %27sCost: 2 %27sCost: 3 %27s\n",
        spaces[0].c_str(), spaces[1].c_str(), spaces[2].c_str(), spaces[3].c_str(), spaces[4].c_str(), spaces[5].c_str());

    printf("| %34s %34s %34s %34s %34s %34s\n",
        spaces[0].c_str(), spaces[1].c_str(), spaces[2].c_str(), spaces[3].c_str(), spaces[4].c_str(), spaces[5].c_str());

    printf("|Index: 0 %26sIndex: 1 %26sIndex: 2 %26sIndex: 3 %26sIndex: 4 %26sIndex: 5 %26s\n",
        spaces[0].c_str(), spaces[1].c_str(), spaces[2].c_str(), spaces[3].c_str(), spaces[4].c_str(), spaces[5].c_str());

    for (int i = 0; i < 211; i++) {
        cout << "_";
    }
    cout << ""<<endl;
}

// toString Hand
ostream& operator<<(ostream& strm, const Hand& hand)
{
	return strm << "Hand have 6 cards to choose from";
}

Hand& Hand::operator=(const Hand& anotherHand)
{
    if (&anotherHand == this)
        return *this;

    if (anotherHand.deck)
    {
        deck = new Deck(*anotherHand.deck);

        for (int i = 0; i < 6; i++)
        {
            cards[i] = deck->draw();
        }
    }
    else
        deck = nullptr;
    
    return *this;
}

