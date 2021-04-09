#include "score.h"
#include "global.h"

void updateScoreboard(Player player, const Maze &maze, string fullPath) {

    ofstream oscoreboardFile(fullPath.c_str());

    oscoreboardFile.open(fullPath.c_str());
    oscoreboardFile.close();

    oscoreboardFile.open(fullPath.c_str());
    if (oscoreboardFile){
        oscoreboardFile << "I ALREADY EXIST BUT THATS COOL";
        cout << "aaaaaaaaaaa" << endl;
        oscoreboardFile.close();
    } else{
        oscoreboardFile << "I DIDN'T EXIST BUT NOW I DO :)";
        cout << "bbbbbbbbb" << endl;
        oscoreboardFile.close();
    }
}


void getPlayerName(string &playerName){
    do{

        bool validInput = getInput<string>(playerName);

        if (validInput && 0 < playerName.length() && playerName.length()<= 15){
            clearBuffer();
            break;
        } else if (!cin.eof()){
            warnUser("name");
        }
    } while (!cin.eof());
}


void printScoreboard(string fullPath){
    ifstream iscoreboardFile;
    string str;

    iscoreboardFile.open(fullPath.c_str());
    while (getline (iscoreboardFile, str)){
        cout << str;
    }
    iscoreboardFile.close();
}

void displayScoreboard(Player player, const Maze maze){
    const string PREFIX = "../output/";                      // prefix containing the file where the maze files are at

    string str;
    vector<Player> playerVec;
    vector<char> rowsVec;
    vector<vector<char>> scoreVec;

    string filename = "MAZE_" + maze.number + "_WINNERS.TXT";
    string fullPath = PREFIX + filename;

    // clearScreen();
    // Getting player's name
    cout << "What's your name?" << endl;
    getPlayerName(player.name);

    updateScoreboard(player, maze, fullPath);

    printScoreboard(fullPath);

/*
    ifstream iscoreboardFile;
    iscoreboardFile.open("../output/"+filename);
    if (iscoreboardFile.is_open()) {
        string line;
        while (getline(iscoreboardFile, line)) {
            // using printf() in all tests for consistency
            printf("%s", line.c_str());
        }
        iscoreboardFile.close();
    }
*/
}
/*
 vector<Player> vec;

//insert code to fill vector up

sort(vec.begin(), vec.end(), [](Player a, Player b){
  return a.time < b.time;
});
 */

/*
void parseTable(const Player &player, vector<Player> playerVec) {

}


vector<Player>*

bool validTable(ofstream &scoreFile) {
    string firstLine = getline(scoreFile);
    string secondLine = getline(scoreFile);
    if
    getl
    Player          - Time
    ----------------------
    Joseph Joestar  - 512
    Dio             - 413
}
*/