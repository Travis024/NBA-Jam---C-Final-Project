#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class GameLoop{

public: //Public Methods

    //Constructor
    GameLoop();
    ~GameLoop();

    //THE FIRST THREE FUNCTIONS CONSIST OF STARTING/LOADING THE GAME
    int newGameLoadGame(); //returns 0 for a new game, 1 for load game
    void loadGame(); //Uses file input to load in saved game information
    void newGame(); //Creates a new game for the user to play

    //STARTING THE GAME
    void startGame();
    //SAVING THE USER'S GAME
    int saveGame();//file output; returns 0 if save unsuccessful, 1 if successful.

private: //Private attributes

    //When this becomes true, we'll close the application
    bool exitGame = false;

};
#endif // GAMELOOP_H
