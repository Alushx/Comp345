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

#include <iostream>
#include "BiddingFacility.h"
#include "Player.h"
#include <vector>

using namespace std;

int main() {

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

    // Deallocating heap.
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i])
            delete player[i];
    }
    return 0;
}


