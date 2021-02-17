#pragma once

#include "BiddingFacility.h"
#include <vector>
#include "Player.h"

using namespace std;

// Forward Declaration
class Player;


class BiddingFacility {

private:
    int *bid;


public:
    // Constructor
    BiddingFacility();

    //Copy constructor
    BiddingFacility(const BiddingFacility& bf);
    
    //Destructor
    ~BiddingFacility();

    //Stream insertion operator
    friend ostream& operator << (ostream& out, const BiddingFacility &bf);
    friend istream& operator >> (istream& in, BiddingFacility &bf);

    // Game Methods
   static int biddingPhase(vector<Player*>& player);
   void setBid(int bid);
   int getBid() const;
};
