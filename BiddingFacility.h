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

    // Gameplay Methods
   static int biddingPhase(vector<Player*>& player);
   void setBid(int bid);
   int getBid() const;


    // Accessors
 //   int getBid() const;

    // Mutators
 //   void setBid(int bid);


};
