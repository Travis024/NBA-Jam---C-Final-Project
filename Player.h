#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>//Used for the 'sleep' function

using namespace std;

class Player{

//Public Member Attributes
public:
    string name;
    string position;

//Public Member Functions
public:
    //Constructor
    Player();
    ~Player();

    //Mutators and Accessors
    void getOffenseStats();
    void getDefenseStats();
    void giveSummary();

    int getCombinedOffense();
    int getCombinedDefense();

    //Fill the stats arrays when creating a new player
    void fillStats();
    //Clear the stats array after viewing a summary
    void clearStats();

    //Save the player to a file or load from a file
    void savePlayer(Player player_number);
    void loadPlayer(Player &player_number, int playerOrder);

//Private Member Attributes:
private:
    //in Offense_Stats, [0] = shooting, [1] = Offensive rebounding
    //in Defense_Stats, [0] = guarding, [1] = Defensive rebounding
    int Offense_Stats[2] = {0,0};
    int Defense_Stats[2] = {0,0};

};
#endif // PLAYER_H
