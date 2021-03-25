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

struct Ability{
    string PLUS_ONE_MOVE = "+1 Move"; // affects create army
    string PLUS_ONE_ARMY = "+1 Army"; // affects move
    string FYLING = "Flying"; // affects movement;
    string ONE_ELIXER = "1 Elixer";
    string TWO_ELIXER = "2 Elixer";
    string THREE_ELIXER = "3 Elixer";
    string ONE_ELIXER_AND_2_COINS = "1 Elixer and 2 coins";
    string PLUS_1_VP_PER_ARCANE_CARD = "+1 VP per Arcane card";
    string PLUS_1_VP_PER_ANCIENT_CARD = "+1 VP per Ancient card";
    string PLUS_1_VP_PER_FYLING = "+1 VP per Fyling";
    string IMMUNE_TO_ATTACK = "Immune to attack"; // Affects destroyArmy()
    string PLUS_1_VP_PER_3_COINS = "+1 VP per 3 coins";
    string PLUS_1_VP_PER_FOREST_CARD = "+1 VP per Forest card";
    string PLUS_1_VP_PER_CURSED_CARD = "+1 VP per Cursed card";
    string PLUS_1_VP_PER_Night_CARD = "+1 VP per Night card";
    string PLUS_5_VP_PER_3_NOBLE_CARD = "All three noble cards = 5 VP";
    string PLUS_3_VP_PER_2_MOUNTAIN_CARD = "+3 If you have 2 Mountain cards";
    string PLUS_1_VP_PER_DIRE_CARD = "+1 VP per Dire card";
};

struct CombinationType {
    string SINGLE = " ";
    string OR = "OR";
    string AND = "AND";
};


//Card

//Constructor
Card::Card(string gd,string ctype, string actn,string abt){
    good = gd;
    combinationtype = ctype;
    action[0] = actn;
    ability = abt;
}

Card::Card(string gd, string ctype, string firstAction, string secondAction, string abt) {
    good = gd;
    combinationtype = ctype;
    action[0] = firstAction;
    action[1] = secondAction;
    ability = abt;
}
//Copy constructor
Card :: Card(const Card &c){
    good = c.good;
    combinationtype = c.combinationtype;
    action[0] = c.action[0];
    action[1] = c.action[1];
    ability = c.ability;
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

string Card :: getAbility(){
    return ability;
}
void Card::printCard() {
    CombinationType comp;
    cout << "\tGood: "<< good<< endl;
    cout << "\tAbility: "<< ability<< endl;
    cout << "\tAction: " << action[0]<< endl;
    if (combinationtype != comp.SINGLE) {
        if (combinationtype == comp.AND) cout << "\tAND" << endl;
        else if (combinationtype == comp.OR)cout << "\tOR" << endl;
        cout << "\tAction: " << action[1];
    }
   
    
}

//Count the number of Elixer and returns it
int Card::getElixerCount(list<Card*>& crds, Player* player){
    Ability cardAbt;
    int numElixer = 0;
    for (Card* card : crds) {
        string ab = card->getAbility();

            if (ab == cardAbt.ONE_ELIXER) numElixer += 1;
            else if (ab == cardAbt.TWO_ELIXER) numElixer += 2;
            else if (ab == cardAbt.THREE_ELIXER) numElixer += 3;
            else if (ab == cardAbt.ONE_ELIXER_AND_2_COINS) numElixer += 1;
        
    }
    return numElixer;
}

//Goes through the list of cards and count the amount of X type of cards in the list.
//type is for example: Arcaine, Ancient, Fyling and etc...
int Card :: getnumXcard(list<Card*> &crds, string type){
    int cnt=0;
    for (Card *card : crds) {
        string ab = card->getGood();
        if(ab.find(type) !=std::string::npos){
            cnt++;
        }
    }
    return cnt;
}
//A list of Cards owned by a player is pass by reference
//The method goes through the cards to check the ability of each card
//VP are calculated depending on the Ability and Good that a player have
int Card :: getCardScore(list<Card*> &crds, Player *player){
    Ability cardAbt;
    int VP =0;
    
    //Go through the list of cards to get the number of Elixer for a player
    player->setOwnNumElixer(getElixerCount(crds, player));

    //Go through the list of Cards
    for (Card *card : crds) {
        string ab = card->getAbility();

        //Checks if the ability is "+1 VP per Arcane card"
        //If yes then go through the list of cards again to count how many Arcaine cards are there
        if(ab == cardAbt.PLUS_1_VP_PER_ARCANE_CARD){
            VP += Card :: getnumXcard(crds,"Arcane");
        }
        //Checks if the ability is "+1 VP per Ancient card"
        //If yes then go through the list of cards again to count how many Ancient cards are there
        if(ab == cardAbt.PLUS_1_VP_PER_ANCIENT_CARD){
            VP += Card :: getnumXcard(crds,"Ancient");
        }
        //Checks if the ability is "+1 VP per Fyling card"
        //If yes then go through the list of cards again to count how many Fyling are there
        if(ab == cardAbt.PLUS_1_VP_PER_FYLING){
            for (Card *card : crds) {
                string abt1 = card->getAbility();
                if(abt1 == cardAbt.FYLING) VP += 1;
            }
        }
        //Checks if the ability is "+1 VP per Forest card"
        //If yes then go through the list of cards again to count how many Forest cards are there
        if(ab == cardAbt.PLUS_1_VP_PER_FOREST_CARD){
            VP += Card :: getnumXcard(crds,"Forest");
        }
        //Checks if the ability is "+1 VP per Cursed card"
        //If yes then go through the list of cards again to count how many Cursed cards are there
        if(ab == cardAbt.PLUS_1_VP_PER_CURSED_CARD){
            VP += Card :: getnumXcard(crds,"Cursed");
        }
        //Checks if the ability is "+1 VP per Night card"
        //If yes then go through the list of cards again to count how many Night cards are there
        if(ab == cardAbt.PLUS_1_VP_PER_Night_CARD){
            VP += Card :: getnumXcard(crds,"Night");
        }
        //Checks if the ability is "+1 VP per Dire card"
        //If yes then go through the list of cards again to count how many Dire cards are there
        if(ab == cardAbt.PLUS_1_VP_PER_DIRE_CARD){
            VP += Card :: getnumXcard(crds,"Dire");
        }
        //Checks if the ability is "All three noble cards = 5 VP"
        //If yes then go through the list of cards again to check if the player has All three noble cards
        if(ab == cardAbt.PLUS_5_VP_PER_3_NOBLE_CARD){
            int numNoble = Card :: getnumXcard(crds,"Noble");
            if(numNoble == 3) VP += 5;// If Player have all 3 Noble card then add 5 VP
        }
        //Checks if the ability is "+3 If you have 2 Mountain cards"
        //If yes then go through the list of cards again to check if the player has 2 Mountain cards
        if(ab == cardAbt.PLUS_3_VP_PER_2_MOUNTAIN_CARD){
            int numMountain = Card :: getnumXcard(crds,"Mountain");
            if(numMountain == 2)VP += 3;
        }

        //Checks if the ability is "+1 VP per 3 coins"
        if (ab == cardAbt.PLUS_1_VP_PER_3_COINS) {
            int cnt = player->getCoins() / 3;// since the variable cnt is int it discard everthing aft the decimal point
            cout << cnt << endl;
            VP += cnt;
            
        }

    }
    return VP;
}

// toString Cards
ostream& operator<<(ostream& strm, const Card& card)
{
	return strm << "Good: " << card.good 
    <<"Ability: "<<card.ability<< "\nAction(s): " << card.action[0] << "\n" << card.combinationtype << "\n"
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
    ability = anotherCard.ability;
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
    Ability abt;
    
    cards[0] = Card(gd.FOREST_PIXIE, ctype.SINGLE, act.MOVE_4_ARMY, abt.PLUS_ONE_ARMY);
    cards[1] = Card(gd.STRONGHOLD, ctype.SINGLE, act.BUILD_CITY, abt.PLUS_1_VP_PER_DIRE_CARD);
    cards[2] = Card(gd.ANCIENT_PHOENIX, ctype.SINGLE, act.MOVE_5_ARMY, abt.FYLING);
    cards[3] = Card(gd.ANCIENT_TREE_SPIRIT, ctype.SINGLE, act.ADD_4_ARMY, abt.THREE_ELIXER);
    cards[4] = Card(gd.ANCIENT_WOODS, ctype.AND, act.BUILD_CITY, act.ADD_1_ARMY, abt.PLUS_ONE_ARMY);
    cards[5] = Card(gd.ANCIENT_SAGE , ctype.SINGLE, act.MOVE_3_ARMY, abt.PLUS_1_VP_PER_ANCIENT_CARD);
    cards[6] = Card(gd.CURSED_BANSHEE, ctype.SINGLE, act.MOVE_6_ARMY, abt.TWO_ELIXER);
    cards[7] = Card(gd.CURSED_GARGOYLES, ctype.SINGLE, act.MOVE_5_ARMY, abt.FYLING);
    cards[8] = Card(gd.CURSED_KING , ctype.OR, act.ADD_3_ARMY,act.MOVE_4_ARMY, abt.ONE_ELIXER);
    cards[9] = Card(gd.CURSED_MAUSOLEUM, ctype.SINGLE, act.BUILD_CITY, abt.PLUS_ONE_MOVE);
    cards[10] = Card(gd.CURSED_TOWER, ctype.SINGLE, act.BUILD_CITY, abt.PLUS_1_VP_PER_FYLING);
    cards[11] = Card(gd.DIRE_DRAGON, ctype.AND, act.ADD_3_ARMY,act.DESTROY_1_ARMY, abt.FYLING);
    cards[12] = Card(gd.DIRE_GIANT, ctype.AND, act.ADD_3_ARMY,act.DESTROY_1_ARMY, abt.IMMUNE_TO_ATTACK);
    cards[13] = Card(gd.DIRE_EYE, ctype.SINGLE, act.ADD_4_ARMY, abt.FYLING);
    cards[14] = Card(gd.DIRE_GOBLIN, ctype.SINGLE, act.MOVE_4_ARMY, abt.ONE_ELIXER);
    cards[15] = Card(gd.DIRE_OGRE, ctype.SINGLE, act.MOVE_2_ARMY, abt.PLUS_1_VP_PER_3_COINS);
    cards[16] = Card(gd.LAKE, ctype.OR, act.ADD_2_ARMY,act.MOVE_3_ARMY, abt.PLUS_1_VP_PER_FOREST_CARD);
    cards[17] = Card(gd.FOREST_ELF, ctype.OR,  act.ADD_3_ARMY,act.MOVE_2_ARMY, abt.PLUS_ONE_ARMY);
    cards[18] = Card(gd.FOREST_GNOME, ctype.SINGLE,act.MOVE_2_ARMY, abt.THREE_ELIXER);
    cards[19] = Card(gd.FOREST_TREE_TOWN , ctype.SINGLE, act.BUILD_CITY, abt.PLUS_ONE_MOVE);
    cards[20] = Card(gd.GRAVEYARD, ctype.SINGLE, act.ADD_2_ARMY, abt.PLUS_1_VP_PER_CURSED_CARD);
    cards[21] = Card(gd.NOBLE_HILLS, ctype.SINGLE, act.ADD_3_ARMY, abt.PLUS_5_VP_PER_3_NOBLE_CARD);
    cards[22] = Card(gd.NOBLE_KNIGHT, ctype.AND, act.ADD_4_ARMY, act.DESTROY_1_ARMY, abt.PLUS_ONE_MOVE);
    cards[23] = Card(gd.NOBLE_UNICORN, ctype.AND, act.MOVE_4_ARMY, act.ADD_1_ARMY, abt.PLUS_ONE_MOVE);
    cards[24] = Card(gd.NIGHT_HYDRA, ctype.AND, act.MOVE_4_ARMY,act.DESTROY_1_ARMY, abt.PLUS_ONE_ARMY);
    cards[25] = Card(gd.NIGHT_VILLAGE, ctype.SINGLE, act.BUILD_CITY, abt.PLUS_ONE_ARMY);
    cards[26] = Card(gd.NIGHT_WIZARD, ctype.AND, act.ADD_4_ARMY, act.DESTROY_1_ARMY, abt.PLUS_1_VP_PER_Night_CARD);

    //3 Player cards
    if(numPlayer >= 3){
    cards[27] = Card(gd.ARCANE_SPHINX, ctype.OR, act.ADD_3_ARMY, act.MOVE_4_ARMY, abt.FYLING);// 3 Player
    cards[28] = Card(gd.ARCANE_MANTICORE, ctype.AND, act.ADD_4_ARMY, act.DESTROY_1_ARMY, abt.PLUS_ONE_MOVE);//3 Player
    cards[29] = Card(gd.ARCANE_TEMPLE, ctype.SINGLE, act.MOVE_3_ARMY, abt.PLUS_1_VP_PER_ARCANE_CARD);// 3Player
    cards[30] = Card(gd.MOUNTAIN_DWARF, ctype.AND, act.ADD_2_ARMY, act.DESTROY_1_ARMY, abt.PLUS_3_VP_PER_2_MOUNTAIN_CARD);//3 Player
    cards[31] = Card(gd.MOUNTAIN_TREASURY, ctype.SINGLE, act.MOVE_3_ARMY, abt.ONE_ELIXER_AND_2_COINS);// 3 Player
    }
    //4 Player cards
    if(numPlayer >= 4){
    cards[32] = Card(gd.CASTLE, ctype.OR, act.ADD_4_ARMY,act. BUILD_CITY, abt.ONE_ELIXER);//4 player 
    cards[33] = Card(gd.CASTLE_2, ctype.AND, act.MOVE_3_ARMY,act.BUILD_CITY, abt.ONE_ELIXER);//4 Player
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

    // Adds coins if needed.
    Ability ability;
    if (pickedCard->getAbility() == ability.ONE_ELIXER_AND_2_COINS)
    {
        player->setCoins(player->getCoins() + 2);
    }

    player->addCard(pickedCard);
    return pickedCard;
}


//Prints the Hand which consist of the 6 cards can choose from
void Hand::printHand() {
    //get the goods for each card
    string goodCard[6];
    string ctypeCard[6];
    string firstAction[6];
    string secondAction[6];
    string cardAbility[6];

    for(int i=0;i<6;i++){
        goodCard[i] = cards[i]->getGood();
    }
    //get the combinationtype for each card in the hand
    for(int i=0;i<6;i++){
        ctypeCard[i] = cards[i]->getCombinationType();
    }
    //get First Action for each card in the hand
    for(int i=0;i<6;i++){
        firstAction[i] = cards[i]->getFirstAction();
    }
    //get Second Action for each card in the hand
    for(int i=0;i<6;i++){
        secondAction[i] = cards[i]->getSecondAction();
    }
    //get the ability of each card in the hand
    for(int i=0;i<6;i++){
        cardAbility[i] = cards[i]->getAbility();
    }
    string spaces[6] = { "|","|" ,"|" ,"|" ,"|" ,"|" };

    for (int i = 0; i < 211; i++) {
        cout << "_";
    }
     //c_str() converts cpp string to c string.
    printf("\n|Good: %-28s|Good: %-28s|Good: %-28s|Good: %-28s|Good: %-28s|Good: %-28s|\n", goodCard[0].c_str(), goodCard[1].c_str(), goodCard[2].c_str(),
        goodCard[3].c_str(), goodCard[4].c_str(), goodCard[5].c_str());

    printf("|Ability: %26sAbility: %26sAbility: %26sAbility: %26sAbility: %26sAbility: %26s\n", 
        spaces[0].c_str(), spaces[1].c_str(), spaces[2].c_str(), spaces[3].c_str(), spaces[4].c_str(), spaces[5].c_str());

    printf("|%-34s|%-34s|%-34s|%-34s|%-34s|%-34s|\n", cardAbility[0].c_str(), cardAbility[1].c_str(), cardAbility[2].c_str(),
        cardAbility[3].c_str(), cardAbility[4].c_str(), cardAbility[5].c_str()); 

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

