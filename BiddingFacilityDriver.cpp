#include <iostream>
#include "BiddingFacility.h"
#include "Player.h"
#include <vector>



using namespace std;
int main() {

    // Local variables for testing
    int numOfPlayers;
    int bidWinner;
    string lName;
    vector<Player*> player;
    int coins = 0;

    // Determine Number Of Players
    cout << "Welcome to Eight-Minute-Empire, how many Players are there?" << std::endl;
    cin >> numOfPlayers;

    if (numOfPlayers == 4) {
        coins = 9;
    }

    if (numOfPlayers == 3) {
        coins = 11;
    }

    if (numOfPlayers == 2) {
        coins = 14;
    }

    // Create all Players in Player vector
    for (int i = 1; i <= numOfPlayers; i++) {
        cout << "Player " << i << " last name: " << std::endl;
        cin >> lName;
        Player* p = NULL;
        p = new Player(lName, coins);
        player.push_back(p);
    }

    

    // Determine the first Player within the bidding phase
    

    bidWinner = BiddingFacility::biddingPhase(player);
     cout << "Index is: " << bidWinner;

    return 0;
}


