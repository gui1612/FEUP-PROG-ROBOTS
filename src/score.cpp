#include "score.h"
#include "global.h"

/*
Player          - Time
----------------------
Joseph Joestar  - 512
Dio             - 413

vector<Player> = {p1, p2}
p1 = {Joseph Joestar, 512}
p2 = {Dio, 413}
 ----------------------
 Name: Giorno
 Score: 490
 Person person;
 person.name = "Giorno"
 person.score = "490"
 ----------------------

vector<Player> v= {p3, p1, p2}
sort(v.begin(), v.end(), [](Person p1, Person p2) {p1.score < p2.score});

-----------------------
 cout << " Player          - Time"
      << " ----------------------";

 for (auto person : v) {
    cout << setw(16) << person.name() << "- " << person.score;
 }
*/


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


void updateScoreboard(Player &player, const Maze &maze, ScoreBoard scoreboard) {

    const string PREFIX = "../input/";

    scoreboard.push_back(player);

    fstream leaderBoard;
    leaderBoard.open(PREFIX + "MAZE_" + maze.number + "_WINNERS.txt");

    if (leaderBoard.good()) {
        string line1, line2;
        getline(leaderBoard, line1);
        getline(leaderBoard, line2);

    } else {
        cout << "Player              - Time\n"
             << "--------------------------\n"
             << player.name << setw(25-(player.name.length())+int(ceil(log10(player.score))+1)) << "- " << player.score;

    }
    leaderBoard.close();

}



/*
void displayScoreboard(Player player, const Maze maze) {

    ifstream iscoreboardFile;
    string str;

    iscoreboardFile.open(fullPath.c_str());
    while (getline (iscoreboardFile, str)){
        cout << str;
    }
    iscoreboardFile.close();
}
*/

void getScoreboard(Player &player, const Maze &maze) {

    ScoreBoard scoreboard;

    getPlayerName(player);      // Gets and validates the player's name

    updateScoreboard(player, maze, scoreboard);
}