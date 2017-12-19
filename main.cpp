#include <iostream>
#include "Player.h"
#include "Game.h"
#include "Team.h"

using namespace std;

//The sequence used when the user decides to create a new player.
//Sets the name and fills the stats of the player.
void createPlayer(Player &player_number){
    //First, name the player
    cout<<"Name your player!"<<endl;
    getline(cin,player_number.name);

    //Then, give them a position
    cout<<"What position do they play?"<<endl;
    getline(cin,player_number.position);

    //Set the player's stats!
    cout<<"Now, let's set your player's stats."<<endl;

    player_number.fillStats();

}

//deletes old players when creating new ones
//opening the file without ios::app truncates it
void deleteOldPlayers(){
    ofstream out_stream;
    out_stream.open("saveFile");
    out_stream.close();
}

int main()
{
    //The start of the game
    //Ask the user to enter Y to play, N to exit, and only continue if they enter Y or N!
    string startGame;
    cout << "Welcome to NBA JAM! Would you like to enter create a team mode or play one-on-one?"<<endl;
    cout<<"Enter 'T' for create a team or 'P' for play one-on-one"<<endl;
    getline(cin,startGame);

    //Unless the user enters some form of yes or no, keep asking them to enter.
    //Yes will start the game.
    //No ends the program immediately.
    bool continueGame = false;

    while(!continueGame){

        if(startGame[0] == 'P' || startGame[0] == 'p'){
            cout<<"Awesome! Let's play ball!"<<endl;
            sleep(1);
            continueGame = true;
        }
        else if(startGame[0] == 'T' || startGame[0] == 't'){
            cout<<"Sweet, entering create a team mode!"<<endl;
            sleep(1);
            Team newTeam;
            newTeam.teamMenu();

            //Back to the main menu selection
            cout << "Welcome to NBA JAM! Would you like to enter create a team mode or play one-on-one?"<<endl;
            cout<<"Enter 'T' for create a team or 'P' for play one-on-one"<<endl;
            getline(cin,startGame);
        }
        else{
            cout<<"Please enter 'T' or 'P' this time!"<<endl;
            getline(cin,startGame);
        }

    }

//!THE MAIN MENU - LOAD NEW CHARACTERS, CREATE NEW CHARACTERS, OR VIEW CHARACTER SUMMARIES

    string playerDecision;
    cout << "Would you like to load previous characters, create new characters, or view player summaries?"<<endl;
    cout<<"Enter 'Load', 'New', or 'Summaries'"<<endl;
    getline(cin,playerDecision);

    //Unless the user enters some form of load, new, or summaries, keep asking them to enter.
    //Load will load players from the file.
    //New will create new players and override the old ones.
    //Summaries will show summaries, then prompt again.
    bool exitPlayerDecision = false;
    //Two instances of player for loading or creating.
    Player playerOne;
    Player playerTwo;

    while(!exitPlayerDecision){
        //Load the players by calling their class function
        if(playerDecision[0] == 'L' || playerDecision[0] == 'l'){
            playerOne.loadPlayer(playerOne , 1);
            playerTwo.loadPlayer(playerTwo , 2);
            cout<<playerOne.name<<" - "<<playerOne.position<<endl;
            playerOne.getOffenseStats();
            playerOne.getDefenseStats();
            cout<<playerTwo.name<<" - "<<playerTwo.position<<endl;
            playerTwo.getOffenseStats();
            playerTwo.getDefenseStats();

            cout<<endl<<endl<<"Players have been loaded - press enter when you're ready to play!"<<endl;
            exitPlayerDecision = true;
        }
        //Create new players by calling their class function; this deletes previous characters
        else if(playerDecision[0] == 'N' || playerDecision[0] == 'n'){

            //Delete old players by opening and closing the file.
            deleteOldPlayers();

            //Player one creates player
            cout<<"User one, you're first!"<<endl;
            createPlayer(playerOne);
            cout<<"PLAYER SUMMARY:"<<endl<<endl;
            cout<<playerOne.name<<" - "<<playerOne.position<<endl;
            playerOne.getOffenseStats();
            playerOne.getDefenseStats();
            cout<<"Saving this player..."<<endl;
            playerOne.savePlayer(playerOne);
            cout<<"Player One Saved!"<<endl<<endl;

            cin.ignore();//Clear the input stream

            //Player two creates player
            cout<<"User two, you're up!"<<endl;
            createPlayer(playerTwo);
            cout<<"PLAYER SUMMARY:"<<endl<<endl;
            cout<<playerTwo.name<<" - "<<playerTwo.position<<endl;
            playerTwo.getOffenseStats();
            playerTwo.getDefenseStats();
            cout<<"Saving this player..."<<endl;
            playerTwo.savePlayer(playerTwo);
            cout<<"Player Two Saved!"<<endl<<endl;

            cout<<"Alright! You guys are ready to play!"<<endl;
            exitPlayerDecision = true;
        }
        //View player summaries by calling the class function
        else if(playerDecision[0] == 'S' || playerDecision[0] == 's'){
            //Pick a player to view their stats
            string viewPlayerStats;
            cout<<"Enter the player number who's stats you wish to view - 1 or 2"<<endl;
            getline(cin,viewPlayerStats);

            if(viewPlayerStats[0] == '1' || viewPlayerStats[0] == '2'){

                if(viewPlayerStats[0] == '1'){
                    //Load the player so the info is stored, then give summary
                    playerOne.loadPlayer(playerOne , 1);
                    playerOne.giveSummary();
                    //Clear the player in case the user creates a new player; don't want the stat values already set
                    playerOne.clearStats();
                }
                else{
                    //Load the player so the info is stored, then give summary
                    playerTwo.loadPlayer(playerTwo , 2);
                    playerTwo.giveSummary();
                    //Clear the player in case the user creates a new player; don't want the stat values already set
                    playerTwo.clearStats();
                }

                //Re-enter the loop.
                cout << "Would you like to load previous characters, create new characters, or view player summaries?"<<endl;
                cout<<"Enter 'Load', 'New', or 'Summaries'"<<endl;
                getline(cin,playerDecision);

            }
            //Valid player  number not entered, ask again!
            else{
                cout<<"Not a valid player number."<<endl;
            }
        }
        else{
            cout<<"Please enter 'Load', 'New', or 'Summaries' this time!"<<endl;
            getline(cin,playerDecision);
        }

    }

    //!PLAYING THE GAME USING THE 'GAME' CLASS
    //Create a new instance of the game class
    Game newGame(playerOne , playerTwo);

    //The user will keep playing a game until they choose to exit
    bool exitGame = false;

    while(!exitGame){

        //Let the user decide how long the game should be
        cin.ignore();//Clear the stream
        string lengthDecision;
        cout<<endl<<endl<<"Would you like to play halves or quarters?"<<endl;
        cout<<"'H' for Halves, 'Q' for quarters"<<endl;
        getline(cin,lengthDecision);

        if(lengthDecision[0] == 'H' || lengthDecision[0] == 'h'){
            newGame.setGameLength(2);
            cout<<"Halves it is!"<<endl;
        }else if(lengthDecision[0] == 'Q' || lengthDecision[0] == 'q'){
            newGame.setGameLength(4);
            cout<<"Quarters it is!"<<endl;
        }else{
            newGame.setGameLength(4);
            cout<<"Invalid input. You're playing quarters!"<<endl;
        }

        //Now let the user set a game description, used when printing out game summary.
        cout<<endl<<"Now give your game a description - is this game seven, or just the preseason?"<<endl;
        getline(cin,newGame.gameDescription);

        //Start playing - this loop will be handled by the playGame loop!
        cout<<"The stage is set! Let's play ball!"<<endl<<endl;
        newGame.playGame();

        //After the game ends, the user can print a game summary to share, play again, or exit.
        newGame.gamesPlayed++;

        string playAgain = "";
        cout<<endl<<"Would you like to play again, print a game summary, or exit?"<<endl;
        cout<<"'A' for play again, 'P' for print, or 'E' for exit"<<endl;
        getline(cin,playAgain);

        if(playAgain[0] == 'A' || playAgain[0] == 'a'){
            cout<<"Awesome! Press enter when you're ready to play again!"<<endl;
            sleep(2);
            //clear the vector so the points scored are reset to 0 for each player
            newGame.clearGame();
        }
        else if(playAgain[0] == 'P' || playAgain[0] == 'p'){
            cout<<"Check your file 'gameSummary' for an awesome game summary to share with friends!"<<endl;
            newGame.createGameSummary(playerOne,playerTwo);
            exitGame = true;
        }else if(playAgain[0] == 'E' || playAgain[0] == 'e'){
            exitGame = true;
        }
    }

    cout<<"Thanks for playing! You played a total of: "<<newGame.gamesPlayed<<" games!";
    return 0;
}



