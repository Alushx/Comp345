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
#include <vector>
#include "BiddingFacility.h"
#include "Player.h"

using namespace std;

//Default Constructor
BiddingFacility::BiddingFacility() {
    BiddingFacility::bid = new int(0);
}

//Copy constructor
BiddingFacility::BiddingFacility(const BiddingFacility &bf) {
    bid = bf.bid;
}

// Destructor
BiddingFacility::~BiddingFacility() {
    if (bid) {
        delete bid;
        bid = NULL;
    }
}

//Stream insertion operator
ostream& operator << (ostream &out, const BiddingFacility &bf) {
    out << "Bid is: " << bf.getBid() << endl;
    return out;
}

BiddingFacility& BiddingFacility::operator= (const BiddingFacility& anotherBid)
{
    if (&anotherBid == this)
        return *this;

    if (anotherBid.bid)
    {
        int tempBid = *(anotherBid.bid);
        bid = &tempBid;
    }
    else
        bid = nullptr;

    return *this;
}

// Returns the index of the player who won the bid
int BiddingFacility::biddingPhase(vector<Player*>& player) {

    // Local Variables
    int bid, highBid = 0, index = 0;
    string bidWinner="";
    bool zeroBid = false;

    //Prompt each player to enter a valid bid value and set this value as that player's bid
    for (int i = 0; i < player.size(); i++) {
        cout << player[i]->getName() << ", how much would you like to bid?" << std::endl;
        cin >> bid;
        while (bid < 0 || bid > player[i]->getCoins()) {
            std::cout << "This amount is not valid! Please enter a number between 0 and " << player[i]->getCoins() << ": " << std::endl;
            std::cin >> bid;
        }
        player[i]->getBidFaci()->setBid(bid);
    }

    cout << std::endl << "Bidding result is: " << std::endl;

    //Compare a player's bid vale with the next player's bid value and determine who is the bid winner
    for (int i = 0; i < player.size(); i++) {
        if (player[i]->getBidFaci()->getBid() > highBid) {
            highBid = player[i]->getBidFaci()->getBid();
            bidWinner = player[i]->getName();
            index = i;
        }
        if (i < (player.size() - 1)) {
            //If a player's bid is equal to the next player's bid (can also be 0), then determine the player whose alphabetical last name order wins
            if (player[i + 1]->getBidFaci()->getBid() == highBid) {
                for (int j = 0; j < player[index]->getName().length(); ++j) {
                    if (player[index]->getName()[j] > player[i + 1]->getName()[j]) {
                        bidWinner = player[i + 1]->getName();
                        highBid = player[i + 1]->getBidFaci()->getBid();
                        index = i+1;
                        break;
                    }
                    if (player[index]->getName()[j] < player[i + 1]->getName()[j]) {
                        bidWinner = player[index]->getName();
                        highBid = player[index]->getBidFaci()->getBid();
                        index = i;
                        break;
                    }
                }
            }
        }
        //Display each player's bid value at the same time
        cout << player[i]->getName() << " bids " << player[i]->getBidFaci()->getBid() << std::endl;
    }
    //Display the bid winner
    cout << "The bid winner is: " << bidWinner << " with a bid value of " << highBid << std::endl;
    player[index]->payCoin(highBid);
    return index;
}  

//Getting the bid value
int BiddingFacility::getBid() const {
    return *bid;
}

//Setting the bid value
void BiddingFacility::setBid(int bid) {
    *BiddingFacility::bid = bid;
}
