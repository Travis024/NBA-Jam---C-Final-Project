#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>//Used for the 'sleep' function
#include <ctime>//used for seeding random

using namespace std;

class Game{

public: //Public Attributes
    string gameDescription; //Allow the user to create a description of the game

public: //Public Methods

    //Initialized with the players for using the Combined Stats functions
    Game(Player player_one, Player player_two);
    ~Game();

    int gamesPlayed = 0; //Track how many games played in one sitting


    //Mutators
    void setGameLength(int length);

    //Functions for playing the game

    void playGame();//The gameloops
    void playPeriod();
    int playerShoot(int playerNumber);//Emulates the player shooting
    void clearGame(); //Used to clear the gameSummary vector

    void createGameSummary(Player player_one, Player player_two); //Prints a game summary to a file
    int giveSummary();//Gives a summary using the gameSummary vector

private: //Private Attributes

    int gameLength; //For either halves or quarters
    vector<int>gameSummary;//Will keep track of points scored by each player. Even always playerOne, odd always playerTwo

    //Will store the combined stats of the players
    int playerOneCombineO;
    int playerOneCombineD;
    int playerTwoCombineO;
    int playerTwoCombineD;


};

#endif // GAME_H
