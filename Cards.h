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

const struct Action {
    std::string MOVE_2_ARMY = "Move 2 army";
    std::string MOVE_3_ARMY = "Move 3 army";
    std::string MOVE_4_ARMY = "Move 4 army";
    std::string MOVE_5_ARMY = "Move 5 army";
    std::string MOVE_6_ARMY = "Move 6 army";
    std::string BUILD_CITY = "Build city";
    std::string ADD_1_ARMY = "Add 1 army";
    std::string ADD_2_ARMY = "Add 2 army";
    std::string ADD_3_ARMY = "Add 3 army";
    std::string ADD_4_ARMY = "Add 4 army";
    std::string DESTROY_1_ARMY = "Destroy 1 army";
};

struct Good {
    //2 players cards(27)
    std::string ANCIENT_PHOENIX = "Ancient Phoenix";
    std::string ANCIENT_TREE_SPIRIT = "Ancient Tree Spirit";
    std::string CURSED_BANSHEE = "Cursed Banshee";
    std::string CURSED_KING = "Cursed King";
    std::string CURSED_TOWER = "Cursed Tower";
    std::string DIRE_EYE = "Dire Eye";
    std::string DIRE_GOBLIN = "Dire Goblin";
    std::string FOREST_ELF = "Forest Elf";
    std::string FOREST_PIXIE = "Forest Pixie";
    std::string GRAVEYARD = "Graveyard";
    std::string NIGHT_HYDRA = "Night Hydra";
    std::string NIGHT_WIZARD = "Night Wizard";
    std::string NOBLE_KNIGHT = "Noble Knight";
    std::string STRONGHOLD = "Stronghold";
    std::string ANCIENT_SAGE = "Ancient Sage";
    std::string ANCIENT_WOODS = "Ancient Woods";
    std::string CURSED_GARGOYLES = "Cursed Gargoyles";
    std::string CURSED_MAUSOLEUM = "Cursed Mausoleum";
    std::string DIRE_DRAGON = "Dire Dragon";
    std::string DIRE_GIANT = "Dire Giant";
    std::string DIRE_OGRE = "Dire Ogre";
    std::string FOREST_GNOME = "Forest Gnome";
    std::string FOREST_TREE_TOWN = "Forest Tree Town";
    std::string LAKE = "Lake";
    std::string NIGHT_VILLAGE = "Night Village";
    std::string NOBLE_HILLS = "Noble Hills";
    std::string NOBLE_UNICORN = "Noble Unicorn";
    //3 players cards(32)
    std::string ARCANE_MANTICORE = "Arcane Manticore";
    std::string ARCANE_TEMPLE = "Arcane Temple";
    std::string MOUNTAIN_TREASURY = "Mountain Treasury";
    std::string ARCANE_SPHINX = "Arcane Sphinx";
    std::string MOUNTAIN_DWARF = "Mountain Dwarf";
    //4 player cards(34)
    std::string CASTLE = "Castle";
    std::string CASTLE_2 = "Castle 2";
};

struct Ability {
    std::string PLUS_ONE_MOVE = "+1 Move"; // affects create army
    std::string PLUS_ONE_ARMY = "+1 Army"; // affects move
    std::string FYLING = "Flying"; // affects movement;
    std::string ONE_ELIXER = "1 Elixer";
    std::string TWO_ELIXER = "2 Elixer";
    std::string THREE_ELIXER = "3 Elixer";
    std::string ONE_ELIXER_AND_2_COINS = "1 Elixer and 2 coins";
    std::string PLUS_1_VP_PER_ARCANE_CARD = "+1 VP per Arcane card";
    std::string PLUS_1_VP_PER_ANCIENT_CARD = "+1 VP per Ancient card";
    std::string PLUS_1_VP_PER_FYLING = "+1 VP per Fyling";
    std::string IMMUNE_TO_ATTACK = "Immune to attack"; // Affects destroyArmy()
    std::string PLUS_1_VP_PER_3_COINS = "+1 VP per 3 coins";
    std::string PLUS_1_VP_PER_FOREST_CARD = "+1 VP per Forest card";
    std::string PLUS_1_VP_PER_CURSED_CARD = "+1 VP per Cursed card";
    std::string PLUS_1_VP_PER_Night_CARD = "+1 VP per Night card";
    std::string PLUS_5_VP_PER_3_NOBLE_CARD = "All three noble cards = 5 VP";
    std::string PLUS_3_VP_PER_2_MOUNTAIN_CARD = "+3 If you have 2 Mountain cards";
    std::string PLUS_1_VP_PER_DIRE_CARD = "+1 VP per Dire card";
};

struct CombinationType {
    std::string SINGLE = " ";
    std::string OR = "OR";
    std::string AND = "AND";
};

class Card {
private:
	std::string good;
	std::string ability;
	std::string combinationtype;
	std::string action[2];

public:
	//Constructor
	Card()=default;
	Card(std::string good, std::string combinationtype, std::string action, std::string ability);
	Card(std::string good, std::string combinationType, std::string firstAction, std::string secondAction, std::string ability);
	~Card();//There are no pointers for this class
	//Copy constructor
	Card(const Card &c);
	std::string getGood();
	std::string getCombinationType();
	std::string getFirstAction();
	std::string getSecondAction();
	std::string getAbility();
	static int getElixerCount(std::list<Card*>& crds, Player* player);
	static int getCardScore(std::list<Card*> &crds, Player *player);
	//display card
	void printCard();
	
	// Operators
	Card& operator=(const Card&);
private:
	friend std::ostream& operator<<(std::ostream&, const Card&);
	static int getnumXcard(std::list<Card*> &crds, std::string type);
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
	friend std::ostream& operator<<(std::ostream&, const Deck&);
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
	friend std::ostream& operator<<(std::ostream&, const Hand&);
public:
	Hand& operator=(const Hand&);
};
