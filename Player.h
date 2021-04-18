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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Map.h"
#include "BiddingFacility.h"
#include "GameObservers.h"

// Forward declarations to make compiler happy.
class Army;
class City;
class Card;
class BiddingFacility;
class PlayerStrategies;
class Subject;

// Player class.
class Player : public Subject
{

private:
	// Member variables.
	std::string name;
	int numOfCoins;
	int numOfCubes;
	int numOfDisks;
	BiddingFacility* bidFaci;
	int score;
	int ownNumElixer;
	PlayerStrategies* strategy;
	std::string currentAction;
	int cardMoveBonus;
	int cardArmyBonus;
	int cardFlightBonus;
	bool hasCardImmunityBonus;

	// Static variables.
	static std::vector<Player*> playerList;
	static int playerNum;
	static Territory* startingRegion;
	static Player* bot;

public:

	// Constructors and destructors.
	Player();
	Player(std::string name, int coinNum, PlayerStrategies* aStrategy = nullptr, bool isBot = false);
	Player(const Player&);
	~Player();

	// Service methods.
	bool payCoin(int& cost);
	void placeNewArmies(Territory* territory);
	void moveArmies(Army*, Territory*);
	void moveOverLand(Army*, Territory*);
	void moveOverWater(Army*, Territory*);
	void buildCity(Territory* territory);
	void destroyArmy(Army*);
	void addCard(Card*);
	Player* computeScore(Map* map);
	void playCard(Card*, Map*);
	int computeContinentsOwned(Map*);
	int executeStrategy(Hand*);

	// Accessors.
	std::string getName();
	int getCoins();
	int getNumOfCubes();
	int getNumOfDisks();
	BiddingFacility* getBidFaci() const;
	std::list<Territory*>* getPlayerTerritories();
	std::list<Card*>* getPlayerHand();
	std::list<City*>* getCities();
	std::list<Army*>* getArmies();
	int getScore();
	int getOwnNumElixer();
	PlayerStrategies* getStrategy();
	std::string getCurrentAction();
	int getCardMoveBonus();
	int getCardArmyBonus();
	int getCardFlightBonus();
	bool getCardImmunityBonus();

	// Mutators.
	void setName(std::string n);
	void setCoins(int c);
	void setNumOfCubes(int);
	void setNumOfDisks(int);
	void setBidFaci(BiddingFacility*);
	void setOwnNumElixer(int numElixer);
	void setStrategy(PlayerStrategies*);
	void setCurrentAction(std::string);
	void setCardMoveBonus(int newBonus);
	void setCardArmyBonus(int newBonus);
	void setCardFlightBonus(int newBonus);
	void setCardImmunityBonus(bool hasImmunity);

	// Operators.
	friend std::ostream& operator<<(std::ostream&, const Player&);
	Player& operator= (const Player&);

	// Static methods.
	static Player* getBot();
	static void setBot(Player*);
	static void placeBotArmies(int, Map*);
	static int getPlayerNum();
	static std::vector<Player*>& getPlayerList();
	static void setStartingRegion(Territory*);
	static Territory* getStartingRegion();
	static Player* announcement(std::vector<Player*> player);
	static Player* computeElixerScore();

private:
	// Helping methods.
	void andOrAction(Card*, std::string&, Map*);
	void playCardAction(std::string, Map*);
	void moveArmiesAction(int, Map*);
	void buildCityAction();
	void addArmiesAction(int);
	void destroyArmyAction();
	int calculateMoveBonus();
	int calculateArmyBonus();
	int calculateFlightBonus();
	bool calculateImmunityBonus();
};

class Army
{
// Local variables.
private:
	Player* owner;
	Territory* position;

// Public methods.
public:
	// Constructors and destructors.
	Army();
	Army(Player*, Territory*);
	Army(const Army&);
	~Army();
	// Useful methods.
	std::string getOwnerName();
	Player* getOwner();
	Territory* getPosition();
	void setPosition(Territory*);
	Army& operator=(Army&);

// Operators.
private:
	friend std::ostream& operator<<(std::ostream&, const Army&);
};

class City
{
	Player* owner;
	Territory* position;
	// Public methods.
public:
	// Constructors and destructors.
	City();
	City(Player*, Territory*);
	City(const City&);
	~City();
	// Useful methods.
	std::string getOwnerName();
	Player* getOwner();
	Territory* getPosition();
	City& operator=(City&);

	// Operators.
private:
	friend std::ostream& operator<<(std::ostream&, const City&);
};
#endif
