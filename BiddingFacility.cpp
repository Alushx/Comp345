#include <iostream>
#include <vector>
#include "BiddingFacility.h"
#include "Player.h"

using namespace std;

// Constructor
BiddingFacility::BiddingFacility() {
    BiddingFacility::bid = new int(0);
}




// Gameplay Methods


// Returns the index of the player who goes first (ie. to determine player order)
int BiddingFacility::biddingPhase(vector<Player*>& player) {

    // Local Variables
    int bid, highBid = 0, index = 0;
    string winner="";

    // Each player gets a chance to enter a bid
    for (int i = 0; i < player.size(); i++) {
        cout << "How much would you like to bid " << player[i]->getName() << "?" << std::endl;
        cin >> bid;
        while (bid < 0 || bid > player[i]->getCoins()) {
            std::cout << "This amount is not valid! Please enter a number between 0 and " << player[i]->getCoins() << ": " << std::endl;
            std::cin >> bid;
        }
        cout << "Bid " << player[i]->getName() << "  " << bid << std::endl;
        player[i]->getBidFaci()->setBid(bid);
    }

    for (int i = 0; i < player.size(); i++) {
        if (player[i]->getBidFaci()->getBid() > highBid) {
            highBid = player[i]->getBidFaci()->getBid();
            winner = player[i]->getName();
            index = i;
        }
        if (i < (player.size() - 1)) {
            if (player[i + 1]->getBidFaci()->getBid() == highBid) {
                for (int j = 0; j < player[i]->getName().length(); ++j) {
                    if (winner[j] > player[i + 1]->getName()[j]) {
                        winner = player[i + 1]->getName();
                        highBid = player[i + 1]->getBidFaci()->getBid();
                        index = i+1;
                        break;
                    }
                    if (winner[j] < player[i + 1]->getName()[j]) break;
                }
            }
        }
    }
    cout << "Winner is: " << winner << " with highest bid of: " << highBid << std::endl;
    return index;
}  

int BiddingFacility::getBid() const {
    return *bid;
}


void BiddingFacility::setBid(int bid) {
    *BiddingFacility::bid = bid;
}
