#include "Player.h"

using namespace std;

//Every player must be given a name when constructed
Player::Player(){

}

Player::~Player(){

}

void Player::getOffenseStats(){
    cout<<name<<" has shooting skill of "<<Offense_Stats[0]<<" and an offensive rebounding skill of "<<Offense_Stats[1]<<endl;
}

void Player::getDefenseStats(){
    cout<<name<<" has guarding skill of "<<Defense_Stats[0]<<" and a defensive rebounding skill of "<<Defense_Stats[1]<<endl;
}

//Get the combined stats for the stats arrays; these values will then be passed into our Game class.
int Player::getCombinedOffense(){
    int sum = 0;
    for(int i = 0; i < 2; i++){
        sum = sum + Offense_Stats[i];
    }
    return sum;
}

int Player::getCombinedDefense(){
    int sum = 0;
    for(int i = 0; i < 2; i++){
        sum = sum + Defense_Stats[i];
    }
    return sum;
}

//Give a summary of a player's stats
//Can view offense stats, name, or defense stats
//User asked what stat to view until choosing to exit.
void Player::giveSummary(){
    string userStatView = "";
    bool exitStatView = false;


    while(!exitStatView){

        cout<<"Which stat would you like to view?"<<endl;
        cout<<"'O' for Offense, 'D' for Defense, 'I' for Info, or 'E' to exit"<<endl;
        getline(cin,userStatView);

        if(userStatView[0] == 'O' || userStatView[0] == 'o'){
            getOffenseStats();
        }
        else if(userStatView[0] == 'D' || userStatView[0] == 'd'){
            getDefenseStats();
        }
        else if(userStatView[0] == 'I' || userStatView[0] == 'i'){
            cout<<"This player's name is: "<<name<<" and they play the position: "<<position<<endl;
        }
        else if(userStatView[0] == 'E' || userStatView[0] == 'e'){
            cout<<"Exiting stat view!"<<endl;
            exitStatView = true;
        }
        else{
            cout<<"Not valid input."<<endl;
        }
    }
}

//Filling the player's stat attributes.
//Done through a simple while loop and an if/else if branch to check the user's answer.
void Player::fillStats(){
    int statPoints = 5;

    while(statPoints > 0){
        char userAnswerChar;
        cout<<endl<<"You have "<< statPoints<<" stat points."<<endl;
        cout<<"Press 1 to increase shooting, 2 to increase offensive rebounding, 3 to increase guarding, or 4 to increase defensive rebounding."<<endl;
        cin>>userAnswerChar;

        if(userAnswerChar == '1'){
            Offense_Stats[0]++;
        }
        else if(userAnswerChar == '2'){
            Offense_Stats[1]++;
        }
        else if(userAnswerChar == '3'){
            Defense_Stats[0]++;
        }
        else if(userAnswerChar == '4'){
            Defense_Stats[1]++;
        }
        else{
            cout<<"You didn't enter a valid number! Shooting has been increased."<<endl;
            Offense_Stats[0]++;
        }
        sleep(2);
        statPoints--;
    }

    cout<<"You have 0 stat points left to use."<<endl;
}

//Clear the stats after viewing a summary
//This way extra stat points aren't added on when players are created to play the game.
void Player::clearStats(){
    for(int i = 0; i < 2; i++){
        Offense_Stats[i] = 0;
        Defense_Stats[i] = 0;
    }
}

//Saving the player to a file - making sure to append so the file is not truncated!
void Player::savePlayer(Player player_number){
    ofstream out_stream;
    out_stream.open("saveFile" , ios::app);

    //check to see if opening failed
    if(out_stream.fail()){
        cout<<"Saving failed."<<endl;
    }

    //Print the name on one line
    //Then offensive stats on the next line
    //Then defensive stats on the final line
    out_stream<<player_number.name<<","<<player_number.position<<","<<endl;

    for(int i = 0; i < 2; i++){
        out_stream<<Offense_Stats[i];
    }
    out_stream<<endl;
    for(int i = 0; i < 2; i++){
        out_stream<<Defense_Stats[i];
    }
    out_stream<<endl;

    out_stream.close();
}

//Loading the player from a file.
void Player::loadPlayer(Player &player_number, int playerOrder){
    ifstream in_stream("saveFile");

    //Check to see if opening the file failed
    if(in_stream.fail()){
        cout<<"Loading in players failed."<<endl;
    }

    //Check to see if file is empty
    //Learned about this method through StackOverFlow
    //seekg 'puts the cursor at the end of the file'
    //tellg returns the cursor's position
    //so if tellg = 0, there's nothing in the file!
    int length;
    in_stream.seekg(0, ios::end);
    length = in_stream.tellg();

    if(length == 0){
        cout<<"Could not load players - none were saved."<<endl;
        exit(1);
    }
     //Close so as to reset the stream, since seekg and tellg mess with it.
     //Then we can just open the file again!
    in_stream.close();
    in_stream.open("saveFile");

    string readLines;
    int stat;
    //Skip the lines that are saved data for player one if loading player two
    string skipLines;
    if(playerOrder == 2){
        for(int i = 0; i < 3; i++){
            getline(in_stream,skipLines);
        }
    }
    //End skip

    //The file is set up so that the lines are structured name -> offense stats -> defense stats
    //So a for loop can be used to go through and add the values to the players, thus 'loading' them!
    for(int i = 0; i < 3; i++){
        getline(in_stream,readLines);

        if(i == 0){
            //Since name and position are on the same line, have to parse
            //Parse my the comma separator added in the save function!
            string current_value = "";
            int index = 0;
            for(int j = 0; j < readLines.length(); j++){
                if(readLines[j] != ','){
                    current_value = current_value + readLines[j];
                }
                else{
                    if(index == 0){
                        player_number.name = current_value;
                        current_value = "";
                        index++;
                    }
                    else{
                        player_number.position = current_value;
                    }
                }
            }
        }
        else if(i == 1){
            for(int j = 0; j < 2; j++){
                stat = readLines[j] - '0'; //Character to integer conversion
                player_number.Offense_Stats[j] = stat;
            }
        }
        else{
            for(int k = 0; k < 2; k++){
                stat = readLines[k] - '0'; //Character to integer conversion
                player_number.Defense_Stats[k] = stat;
            }
        }
    }
}


