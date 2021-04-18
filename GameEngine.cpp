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
#include "GameEngine.h"
#include "GameObservers.h"
#include "Cards.h"
#include "Player.h"
#include "Map.h"
#include "BiddingFacility.h"
#include "MapLoader.h"
#include "Game.h"
#include <vector>
#include <iostream>
using namespace std;


int GameEngine :: selectGameMode(){

    cout <<"|--------------------------------|"<< endl;
    cout<<"|                                |"<< endl;
    cout << "| Welcome to Eight-Minute Empire |"<< endl;
    cout<<"|                                |"<< endl;
    cout <<"|--------------------------------|"<< endl;

    
    cout << "Please Select a Game Mode: " << endl;
    cout << "\t1) Single Game" << endl;
    cout << "\t2) Tournament Game" << endl;


    int selectedMode=1;
    cin >> selectedMode;

    while(selectedMode != 1 && selectedMode != 2){
        cout << "Please enter either a '1' or a '2': ";
        cin >> selectedMode;
    }

    return selectedMode;
}

void GameEngine::singleGame(int selectedMode){
    // Setting up players, bidding facility, and map.
    MapLoader* mapLoader;
    mapLoader = startGame(selectedMode);

    // Creating deck.
    Deck* deck = new Deck(Player::getPlayerNum());
    createDeck(deck);

    // Selecting first player.
    int bidWinner = selectBidWinner();

    // Display 6 cards.
    Hand* hand = new Hand(deck);
    hand->printHand();

    // Placing each player's 4 armies.
    placeArmies(mapLoader);

    // Places bot armies.
    placeBotArmies(mapLoader);

    // Main game loop
    playGame(hand, bidWinner, mapLoader, selectedMode);

    // Compute score
    calculateScore(mapLoader);

    // Determine winner
    determineWinner();

    // Deallocating Players and Bot armies.
    deallocateResources(mapLoader, deck, hand);
}

void GameEngine::tournamentGame(int selectedMode){

    // Setting up players, bidding facility, and map.
    MapLoader* mapLoader = startTournament();

    // Creating deck.
    Deck* deck = new Deck(4);
    createDeck(deck);

    // Display 6 cards.
    Hand* hand = new Hand(deck);

    // Placing each player's 4 armies.
    placeArmies(mapLoader);

    // Main game loop
    playTournamentGame(hand, deck, mapLoader);

    displayTournamentResults();

    // Determine winner
    determineWinner();

    // Deallocating Players and Bot armies.
    deallocateResources(mapLoader, deck, hand);
}

MapLoader* GameEngine::startTournament()
{
    Player* player1 = new Player("Player 1", 14);
    Player* player2 = new Player("Player 2", 13);

    changePlayerStrategy(player1);
    changePlayerStrategy(player2);

    return loadValidMap("map1.txt");
}

void GameEngine::playTournamentGame(Hand* hand, Deck* deck, MapLoader* mapLoader)
{
    // Setting up variables.
    vector<Player*> player = Player::getPlayerList();
    int playerNum = Player::getPlayerNum();
    Turn* turn = createTurns(2, mapLoader->getMap(), hand);
    GameState* state = new GameState(mapLoader->getMap());

    // Adding observers. Automatically deleted by subject.
    new View(state);
    new PlayerTurnViewer(turn);
    new CardPickViewer(turn);
    for (Player* subjectPlayer : player)
    {
        new PlayerActionViewer(subjectPlayer);
        new CardBonusViewer(subjectPlayer);
    }

    Deck* newDeck = nullptr;
    Hand* newHand = nullptr;

    // Main game loop.
    for (int i = 0; i < turn->getMaxNumOfTurns(); i++)
    {
        // Near the end, we run out of cards. So this just resets the number of cards.
        if (i == 13) 
        { 
            newDeck = new Deck(4);
            createDeck(deck);
            newHand = new Hand(newDeck);
            turn->setGameHand(newHand);
        }

        for (int j = 0; j < player.size(); j++)
        {
            turn->setPlayerTurn(player[j]);
            turn->playTurn();
            state->computeGameState();
        }
    }

    if (newDeck != nullptr)
        delete newDeck;
    if (newHand != nullptr)
        delete newHand;
    delete turn;
    delete state;
}

