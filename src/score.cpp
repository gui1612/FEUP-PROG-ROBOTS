#include "score.h"
#include "global.h"


void getPlayerName(Player &player){

    do{
        string playerName;
        int count = 0;

        cout << "What's your name?" << endl;
        bool validInput = getInput<string>(playerName);

        for (int i = 0; playerName[i]!='\0'; i++) {count++;}

        if (validInput && 0 < count && count<= 15){
            player.name = playerName;
            clearBuffer();
            break;
        } else if (!cin.eof()) {
            clearBuffer();
            warnUser("name");
        }
    } while (!cin.eof());
}


void updateScoreboard(const string fullPath, ScoreBoard scoreboard, const string mazeNumber) {
    ifstream if_leaderBoard;

    if_leaderBoard.open(fullPath.c_str());

    if (if_leaderBoard.good()) {
        string str;

        string line1, line2, line3;
        getline(if_leaderBoard,line1);
        getline(if_leaderBoard, line2);
        getline(if_leaderBoard, line3);

        parseLines(if_leaderBoard, scoreboard);
        if_leaderBoard.close();

        ofstream of_leaderBoard;
        of_leaderBoard.open(fullPath.c_str());

        of_leaderBoard << "MAZE " << mazeNumber << " SCOREBOARD" << endl
                       << "Player              - Time" << endl
                       << "--------------------------" << endl;

        int scoreboardSize = scoreboard.size();
        int counter = 1;
        sort(scoreboard.begin(), scoreboard.end(), [](Player p1, Player p2){return p1.score < p2.score;});

        for (auto player : scoreboard){
            if (counter != scoreboardSize) {
                of_leaderBoard << left << setw(20)  << player.name   << "- " << right << setw(4) << player.score << endl;
                counter++;
            } else {
                of_leaderBoard << left << setw(20)  << player.name   << "- " << right << setw(4) << player.score;
            }
        }

        of_leaderBoard.close();
    } else {
        if_leaderBoard.close();
        ofstream of_leaderBoard;
        of_leaderBoard.open(fullPath);

        Player player = scoreboard.at(0);

        of_leaderBoard <<"MAZE " << mazeNumber << " SCOREBOARD" << endl
                       << "Player              - Time" << endl
                       << "--------------------------" << endl
                       << left << setw(20)  << player.name   << "- " << right << setw(4) << player.score;;

        of_leaderBoard.close();
    }
}


void getScoreboard(Player &player, const Maze &maze) {
    ScoreBoard scoreboard;
    const string PREFIX = "../input/";
    const string fullPath = PREFIX + "MAZE_" + maze.number + "_WINNERS.txt";
    const string mazeNumber = maze.number;


    getPlayerName(player);      // Gets and validates the player's name
    scoreboard.push_back(player);

    updateScoreboard(fullPath, scoreboard, mazeNumber);

    clearScreen();
    displayScoreboard(fullPath);
    cout << endl << "Press ENTER to return to the main menu..." << endl;
    waitForConfirmation();
}


void parseLines(ifstream &leaderBoard, ScoreBoard &scoreBoard) {


    while (!leaderBoard.eof()) {
        string line;
        getline(leaderBoard, line);

        size_t lastDashPos = line.rfind('-');
        string strScore = line.substr(lastDashPos + 2);
        int score = stoi(strScore);

        string firstPart = line.substr(0, lastDashPos);
        size_t lastAlphaPos = getLastAlphaIdx(firstPart);

        string name = firstPart.substr(0, lastAlphaPos);

        Player player;
        player.name = name;
        player.score = score;

        scoreBoard.push_back(player);
    }
}


size_t getLastAlphaIdx(string str) {
    for (size_t i = str.length() - 1; i > 0; i--) {
        if (!isspace(str.at(i))) { return i; }
    }
    return -1;
}


void displayScoreboard(const string &fullPath){
    string line;
    ifstream scoreboard;
    scoreboard.open(fullPath);
    if(scoreboard.good()) {
        while(!scoreboard.eof()) {
            getline(scoreboard, line);
            cout << line << endl;
        }
    }
}