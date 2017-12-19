#include "Game.h"

using namespace std;

//Constructor - Initialized with combined stats, as they will be used to determine a made or missed shot in the playerShoot function.
//When these values are part of the Game class, they don't have to be passed through each function (that would be a pain)
Game::Game(Player player_one , Player player_two){
    playerOneCombineO = player_one.getCombinedOffense();
    playerOneCombineD = player_one.getCombinedDefense();
    playerTwoCombineO = player_two.getCombinedOffense();
    playerTwoCombineD = player_two.getCombinedDefense();
}

Game::~Game(){

}

void Game::setGameLength(int length){
    gameLength = length;
}


void Game::playGame(){
    int index = 0;
    //giveSummary will return 1 when player one is ahead, 2 when player two is ahead, 3 when tied.
    int calculateWinner;

    while(index < gameLength){
        //Call play period; when period is done, increment index
        sleep(2);
        cout<<"START OF THE "<<index + 1<<" PERIOD!"<<endl;
        sleep(2);
        playPeriod();
        calculateWinner = giveSummary();
        index++;
    }
    //The game is over - declare the winner.
    cout<<endl<<"THE GAME IS OVER!!!!!!!"<<endl;
    sleep(3);

    if(calculateWinner == 1){
        cout<<"PLAYER ONE WINS! WAY TO GO PLAYER ONE!"<<endl;
    }
    else if(calculateWinner == 2){
        cout<<"PLAYER TWO WINS! WHAT A GAME, PLAYER TWO!"<<endl;
    }
    else{
        cout<<"It ends in a tie..."<<endl;
    }
}

void Game::playPeriod(){
    //Generate a random period length to make each period feel different
    //srand seeds a nw value every time
    srand(time(NULL));
    int period_length = (rand()%10) + 4;
    //keep track of the points scored
    int pointsScored = 0;
    //The users take turns shooting until a certain number of points are scored
    while(pointsScored < period_length){
        cout<<"The period length is: "<<period_length<<" and "<<pointsScored<<" points have been scored."<<endl;
        int addScore;
        //Every time playerShoot is called, pointScored will be incremented by 2, 3, or 0
        //The gameSummary vector will always have PlayerOne's shots as even and player 2's shots as odd.
        cout<<endl<<"PLAYER ONE'S TURN:"<<endl<<endl;
        sleep(2);

        addScore = playerShoot(1);
        pointsScored = pointsScored + addScore;
        gameSummary.push_back(addScore);

        cout<<endl<<"PLAYER TWO'S TURN:"<<endl<<endl;
        sleep(2);

        addScore = playerShoot(2);
        pointsScored = pointsScored + addScore;
        gameSummary.push_back(addScore);
    }
}

int Game::playerShoot(int playerNumber){
    //This tells what player is shooting so we can calculate the shot based on the correct player's stats
    int Offense, Defense;

    if(playerNumber == 1){
        Offense = playerOneCombineO;
        Defense = playerTwoCombineD;
    }
    else{
        Offense = playerTwoCombineO;
        Defense = playerOneCombineD;
    }

    //Ask what shot they'd like to shoot.
    string shotType;
    cout<<"Would you like to shoot a lay-up, a jumper, or a three pointer?"<<endl;
    cout<<"'L' for lay-up, 'J' for jumper, or 'T' for three-pointer."<<endl;
    getline(cin,shotType);

    //The game has a secret cheat file
    //If the cheat file contains 'makeshot' and C or c is entered after a shot selection
    //Then the shot will go in NO MATTER WHAT!
    bool checkCheat = false;
    if(shotType[1] == 'C' || shotType[1] == 'c'){
        ifstream in_stream("secretCheatFile");

        string currentLine = "";
        getline(in_stream,currentLine);
        if(currentLine == "makeshot"){
            checkCheat = true;
        }
    }

    //Generate a random number to determine whether or not the player scores
    //srand seeds a new value every time
    srand(time(NULL));
    int multiplier = (rand()%3) + 1;

    //Conditions are different for each shot type
    if(shotType[0] == 'L' || shotType[0] == 'l'){
        cout<<"You shoot a lay-up..."<<endl;
        sleep(2);
        //Check to see if the shot is good
        //If it is, return 2. Otherwise, return 0.
        if((Offense * multiplier) >= (Defense * 2) || checkCheat == true){
            cout<<"And it goes in! 2 points!"<<endl;
            sleep(2);
            return 2;
        }else{
            cout<<"but it's a miss!"<<endl;
            sleep(2);
            return 0;
        }
    }
    else if(shotType[0] == 'J' || shotType[0] == 'j'){
        cout<<"You pull up for a jumper..."<<endl;
        sleep(2);
        //Check to see if the shot is good
        //If it is, return 2. Otherwise return 0
        if((1 + Offense * multiplier) >= (Defense * 3) || checkCheat == true){
            cout<<"Swish, you drain it!"<<endl;
            sleep(2);
            return 2;
        }
        else{
            cout<<"But it clunks off the rim!"<<endl;
            sleep(2);
            return 0;
        }
    }
    else if(shotType[0] == 'T' || shotType[0] == 't'){
        cout<<"You shoot from downtown..."<<endl;
        sleep(2);
        //Check to see if the shot is good
        //If it is, return 3. Otherwise return 0
        if((1 + Offense * multiplier) >= (Defense * 3) || checkCheat == true){
            cout<<"BANG! WHAT A SHOT! THAT'S 3 POINTS!"<<endl;
            sleep(2);
            return 3;
        }
        else{
            cout<<"and it's not even close..."<<endl;
            sleep(2);
            return 0;
        }
    }
    else{
        //return 0 since the player didn't score
        cout<<"Invalid input! You turn it over!"<<endl;
        sleep(2);
        return 0;
    }
}
//At the end of every period, this will tell the players what the score is!
int Game::giveSummary(){
    int playerOnePointsScored = 0;
    int playerTwoPointsScored = 0;

    //Player one is always in the even numbered positions
    //Player two is always in the odd numbered positions
    for(int i = 0; i < gameSummary.size(); i++){
        if(i % 2 == 0){
            playerOnePointsScored = playerOnePointsScored + gameSummary[i];
        }
        else{
            playerTwoPointsScored = playerTwoPointsScored + gameSummary[i];
        }
    }

    //Tell the players what the score is.
    cout<<endl<<endl<<"THE CURRENT SCORE IS:"<<endl;
    sleep(1);
    cout<<"Player One: "<<playerOnePointsScored<<" Player Two: "<<playerTwoPointsScored<<endl;
    sleep(3);

    //return values to check who the winner is
    if(playerOnePointsScored > playerTwoPointsScored){
        return 1;
    }
    else if(playerTwoPointsScored > playerOnePointsScored){
        return 2;
    }
    else{
        return 3;
    }
}

//Clear the gameSummary vector when the user chooses to play again.
void Game::clearGame(){
    gameSummary.clear();
}

//Print a game summary to a file to share with friends!
void Game::createGameSummary(Player player_one, Player player_two){
    ofstream out_stream("gameSummary");

    //check to see if opening failed
    if(out_stream.fail()){
        cout<<"Sorry, there was an error! No game summary was created."<<endl;

    }

    //Print player names and game description
    out_stream<<"For this exciting match-up, "<<player_one.name<<" faced off against "<<player_two.name<<"!"<<'\n'<<'\n';
    out_stream<<"Here's what the players had to say about the game: "<<gameDescription<<'\n'<<'\n';

    //Calculate the final score
    int playerOnePoints = 0;
    int playerTwoPoints = 0;
    for(int i = 0; i < gameSummary.size(); i++){
        if(i % 2 == 0){
            playerOnePoints = playerOnePoints + gameSummary[i];
        }
        else{
            playerTwoPoints = playerTwoPoints + gameSummary[i];
        }
    }
    //Print the score
    out_stream<<"The final score was "<<player_one.name<<": "<<playerOnePoints<<" and "<<player_two.name<<": "<<playerTwoPoints<<'\n';
    out_stream<<"What an exciting game it was!";
}

