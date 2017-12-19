#include "Team.h"

using namespace std;

//Constructor and destructor
Team::Team(){

};

Team::~Team(){

};

//The menu "screen" - user can create new, load old, view summary, or exit
void Team::teamMenu(){
    bool leaveMenu = false;

    while(!leaveMenu){
        //ask the user what they want to do
        string userDecision = "";
        cout<<"Would you like to create a new team, load a team, view a team summary, or exit?"<<endl;
        cout<<"Enter 'C' for create, 'L' for load, 'S' for summary, or 'E' for exit"<<endl;
        getline(cin,userDecision);

        if(userDecision[0] == 'C' || userDecision[0] == 'c'){
            createTeam();
        }
        else if(userDecision[0] == 'L' || userDecision[0] == 'l'){
            cout<<"Loading..."<<endl;
            sleep(1);
            cout<<"Loading..."<<endl;
            sleep(1);
            loadTeam();
            cout<<"Your team has been loaded!"<<endl;
        }
        else if(userDecision[0] == 'S' || userDecision[0] == 's'){
            //Use viewInfo and viewPlayers to get a team summary
            sleep(2);
            viewInfo();
            sleep(2);
            viewPlayers();
            sleep(2);
            cout<<"Press any key when you are ready to leave the summary page."<<endl<<endl;
            //A placeholder string; it just acts as a pause for leaving the summary page.
            string exitSummary;
            getline(cin,exitSummary);
        }
        else if(userDecision[0] == 'E' || userDecision[0] == 'e'){
            cout<<"Exiting Create a Team mode..."<<endl<<endl;
            sleep(2);
            leaveMenu = true;
        }
        else{
            cout<<"Please enter 'C', 'L', 'S', or 'E' this time!"<<endl;
            getline(cin,userDecision);
        }
    }
}

void Team::createTeam(){
    //Get user input to fill the data members
    cout<<"Time to create your very own team!"<<endl<<endl;

    cout<<"What is your team's location?"<<endl;
    getline(cin,location);

    cout<<"What is your team's mascot?"<<endl;
    getline(cin,mascot);

    cout<<"What is your team's history?"<<endl;
    getline(cin,history);

    cout<<"Alright, time to create your players!"<<endl;
    //Use a for loop to create 5 players
    for(int i = 0; i < 5; i++){
        cout<<endl<<"Enter the name of Player "<<i + 1<<":"<<endl<<endl;
        getline(cin,playersArray[i].name);
    }

    cout<<endl<<"Your team has been created..."<<endl;
    sleep(2);
    saveTeam();
    cout<<"...and saved! How cool!"<<endl<<endl;
}

//Write team info to a file.
void Team::saveTeam(){
    ofstream out_stream("saveTeam");

    //check to see if opening failed
    if(out_stream.fail()){
        cout<<"Saving your team failed! Sorry!";
        exit(1);
    }

    out_stream<<location<<endl;
    out_stream<<mascot<<endl;
    out_stream<<history<<endl;

    //Use a for loop to output the player names.
    for(int i = 0; i < 5; i++){
        out_stream<<playersArray[i].name<<endl;
    }
}

//Retrieves the team name, mascot, and history to show the user.
void Team::viewInfo(){
    cout<<"TEAM INFO:"<<endl<<endl;
    cout<<"Team Name: The "<<location<<" "<<mascot<<"'s"<<endl;
    cout<<"Team History: "<<history<<endl;
}

void Team::viewPlayers(){
    cout<<endl<<"TEAM PLAYERS:"<<endl<<endl;
    for(int i = 0; i < 5; i++){
        cout<<playersArray[i].name<<endl;
    }
}

void Team::loadTeam(){

    ifstream in_stream("saveTeam");

    if (in_stream.fail()){
        cout<<"Failed to load your team"<<endl;
        exit(1);
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
        cout<<"Could not load team - no team was previously saved."<<endl;
        exit(1);
    }
     //Close so as to reset the stream, since seekg and tellg mess with it.
     //Then we can just open the file again!
    in_stream.close();
    in_stream.open("saveTeam");


    //This will be used when reading in the current line.
    string currentLine = "";

    //Every team has 3 lines that aren't players; their locations are always the same.
    for(int i = 0; i < 3; i++){
        getline(in_stream , currentLine);
        if(i == 0)
            location = currentLine;
        else if(i == 1)
            mascot = currentLine;
        else
            history = currentLine;
    }

    //set each player in the player's array
    for(int i = 0; i < 5; i++){
        getline(in_stream,currentLine);
        playersArray[i].name = currentLine;
    }

}
