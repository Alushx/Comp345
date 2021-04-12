#include "GameEngine.h"
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

void GameEngine::singleGame(){
    //To do
}

void GameEngine::tournamentGame(){
    //To do
}