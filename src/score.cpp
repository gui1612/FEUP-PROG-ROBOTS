#include "score.h"
#include "global.h"


void getPlayerName(Player &player){

    do{
        string playerName;
        int count = 0;

        cout << "What's your name?" << endl;
        bool validInput = getInput<string>(playerName);

        for (int i = 0; playerName[i]!='\0'; i++) {count++;}

        cout << count << endl;

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


void updateScoreboard(const Maze &maze, ScoreBoard scoreboard) {
    const string PREFIX = "../input/";
    const string fullPath = PREFIX + "MAZE_" + maze.number + "_WINNERS.txt";

    ifstream if_leaderBoard(fullPath);

    if_leaderBoard.open(fullPath);


    if (if_leaderBoard.is_open()) {
        cout << "ABFSAHFJOAJFNOIASLJFNSOAFHJNSAOPJFOASFJ" << endl;
        parseLines(if_leaderBoard, scoreboard);
        if_leaderBoard.close();

        ofstream of_leaderBoard;
        of_leaderBoard.open(fullPath.c_str());

        of_leaderBoard << "Player              - Time" << endl
                       << "--------------------------" << endl;

        for (auto player : scoreboard){

            int MAX_LENGTH = 26;

            size_t playerNameLen = player.name.length();
            size_t playerScoreLen = (floor(log10(player.score))) + 1;
            int offset = MAX_LENGTH - (playerNameLen + playerScoreLen);

            of_leaderBoard << player.name << setw(offset) << "- " << player.score;
        }

        of_leaderBoard.close();
    } else {
        if_leaderBoard.close();

        int MAX_LENGTH = 26;
        ofstream of_leaderBoard;
        of_leaderBoard.open(fullPath);

        Player player = scoreboard.at(0);
        size_t playerNameLen = player.name.length();
        size_t playerScoreLen = (floor(log10(player.score))) + 1;
        size_t offset = MAX_LENGTH - (playerNameLen + playerScoreLen);

        of_leaderBoard << "Player              - Time" << endl
                       << "--------------------------" << endl
                       << player.name << setw(offset) << "- " << player.score;

        of_leaderBoard.close();
    }
}


void getScoreboard(Player &player, const Maze &maze) {
    ScoreBoard scoreboard;

    getPlayerName(player);      // Gets and validates the player's name
    scoreboard.push_back(player);

    updateScoreboard(maze, scoreboard);
}


void parseLines(ifstream &leaderBoard, ScoreBoard &scoreBoard) {
    string line1, line2;
    getline(leaderBoard, line1);
    getline(leaderBoard, line2);

    while (!leaderBoard.eof()) {
        string line;
        getline(leaderBoard, line);

        size_t lastDashPos = line.length() + line.find_last_of('-');
        int score = stoi(line.substr(lastDashPos + 2));

        string firstPart = line.substr(0, lastDashPos);
        size_t lastAlphaPos = getLastAlphaIdx(firstPart);

        string name = firstPart.substr(0, lastAlphaPos);

        Player player;
        player.name = name;
        player.score = score;

        cout << player.name << " " << player.score << endl;

        scoreBoard.push_back(player);
    }
}

size_t getLastAlphaIdx(string str) {
    for (size_t i = str.length(); i > 0; i--) {
        if (isalpha(str.at(i))) { return i; }
    }
    return -1;
}