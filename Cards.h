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
#include "Player.h"
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

struct Ability {
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
	static int getElixerCount(list<Card*>& crds, Player* player);
	static int getCardScore(list<Card*> &crds, Player *player);
	//display card
	void printCard();
	
	// Operators
	Card& operator=(const Card&);
private:
	friend ostream& operator<<(ostream&, const Card&);
	static int getnumXcard(list<Card*> &crds, string type);
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
	Card* getHandCards();
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
