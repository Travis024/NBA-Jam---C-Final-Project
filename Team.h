#ifndef TEAM_H
#define TEAM

#include "Player.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>//Used for the 'sleep' function

using namespace std;

class Team{

public: //Public data members

    //Data members for a 'Create a team' mode
    string location;
    string mascot;
    string history;

public:

    //Constructor
    Team();
    ~Team();

    //Save and load a team
    void saveTeam();
    void loadTeam();

    //Accessors
    void viewInfo();
    void viewPlayers();

    //The menu "screen"
    void teamMenu();

    //Create the team by filling data members and players array
    void createTeam();


private: //Private data members

    //An array of players to store in Team
    Player playersArray[5];

};
#endif // TEAM_H
