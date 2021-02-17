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

#include "Map.h"
#include "BiddingFacility.h"
#include "Player.h"
#include "Cards/Cards.h"
#include "Maploader/MapLoader.h"

int main()
{
	MapLoader* mapLoaderObj = new MapLoader();
	mapLoaderObj->readMapFile("map.txt");
    Map* map = mapLoaderObj->getMap();
    map->validate();
	
    // Local variables
    int numOfPlayers = 0;
    int bidWinner;
    string lName;
    vector<Player*> player; //A vector of pointer-to-objects (which is Player)
    int coins = 0;

    //Prompt the user to enter a valid number Of players
    cout << "Welcome to Eight-Minute-Empire, how many Players are there?" << std::endl;
    cin >> numOfPlayers;
    while (numOfPlayers < 2 || numOfPlayers > 4) {
        std::cout << "The entered value is not valid! Please enter a number between 2 and 4 (inclusively)." << std::endl;
        std::cin >> numOfPlayers;
    }

    //Determine number of coins allocated based on number of players
    if (numOfPlayers == 4) coins = 9;
    if (numOfPlayers == 3) coins = 11;
    if (numOfPlayers == 2) coins = 14;

    // Create all player objects in Player vector
    for (int i = 1; i <= numOfPlayers; i++) {
        cout << "Player " << i << " last name: " << std::endl;
        cin >> lName;
        Player* p = NULL;
        p = new Player(lName, coins);
        player.push_back(p);
    }

    // Determine the first Player within the bidding phase
    bidWinner = BiddingFacility::biddingPhase(player);
    
    Player* firstPlayer = player[bidWinner];
    int numOfCoins = firstPlayer->getBidFaci()->getBid();
    firstPlayer->payCoin(numOfCoins);

    // create a deck
    Deck* deck = new Deck();

    // generate the cards
    deck->generateDeck();

    // shuffle the deck
    deck->shuffleDeck();
    deck->printDeck();

    // Create new hand.
    Hand* hand = new Hand(deck);
    int index = 0;
    for (int i = 0 ; i < player.size() ; i++)
    { 
        index = 0;
        while (index >= 0) {
            hand->printHand();
            cout << "Please enter the index of the card you want to pick or a negative number to exit: ";
            cin >> index;
            if (hand->exchange(index, player[i]))
                break;
        }
    }
    firstPlayer->placeNewArmies(map->getTerritory("territory1"));
    firstPlayer->moveArmies(firstPlayer->getArmies()->front(), map->getTerritory("territory2"));
    firstPlayer->destroyArmy(firstPlayer->getArmies()->front());

    if (hand)
    {
        delete hand;
        hand = nullptr;
    }

    if (deck)
    {
        delete deck;
        deck = nullptr;
    }
        

    for (Player* individual : player)
    {
        if (individual)
            delete individual;
        individual = nullptr;
    }

	delete mapLoaderObj;
	mapLoaderObj = nullptr;
    return 0;
}