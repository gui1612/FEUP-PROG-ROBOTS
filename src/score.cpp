#include "score.h"
#include "global.h"


void getPlayerName(Player &player){
    // Variable to leave the do-while loop (should be at 0 to leave)
    short leave = 1;
    do{
        string playerName;                                  // Initializes string to store the player username
        int nameLen = 0;                                    // The size of the name

        cout << "What's your name?" << endl;
        bool validInput = getInput(playerName);

        if (validInput) {                          // Valid type
            clearBuffer();
            //TODO: Remove this and count UTF-8 length
            //for (int i = 0; playerName[i]!='\0'; i++) {nameLen++;}
            nameLen = playerName.length();

            if (0 < nameLen && nameLen <= 15) {     // Invalid name size
                player.name = playerName;
                leave = 0;                                  // Leave the loop
            } else {
                warnUser("name");
            }
        } else if (!cin.eof()) {                    // Invalid type
            /**
             * Note: we need this condition for inputs like:
             * "ABCDE FGHJKLMNOPQRSTUV" were the name would exceed the 15
             * chars limit, but since only the string "ABCDE" would go to
             * the buffer, the scoreboard would be wrongly updated
             */
            warnUser("name");
        }
    } while (!cin.eof() && leave != 0);
}


void getScoreboard(const string &fullPath, ScoreBoard scoreboard, const Player &player) {
    ifstream if_leaderBoard;                            // Initializing a stream for file input

    if_leaderBoard.open(fullPath.c_str());              // Opening the file

    if (if_leaderBoard.good()) {        // File exists
        string str;

        // Skipping the lines for the header
        string line1, line2;
        getline(if_leaderBoard, line1);
        getline(if_leaderBoard, line2);

        parseLines(if_leaderBoard, scoreboard, player); // Parsing the previous scoreboard to `scoreboard`
        if_leaderBoard.close();                               // Closing the stream for file input

        ofstream of_leaderBoard;                              // Opening a stream for file output
        of_leaderBoard.open(fullPath.c_str());                // Opening the file to write into

        // Writing the table header
        of_leaderBoard << "Player              - Time" << endl
                       << "--------------------------" << endl;

        int scoreboardSize = scoreboard.size();
        int counter = 1;
        // Sorting the scores in the scoreboard
        sort(scoreboard.begin(), scoreboard.end(), [](const Player p1, const Player p2){return p1.score < p2.score;});


        for (auto player2 : scoreboard) {
            if (counter != scoreboardSize) {                // Not the end of the table
                of_leaderBoard << left << setw(20)  << player2.name   << "- " << right << setw(4) << player2.score << endl;
                counter++;
            } else {                                        // The end of the table
                of_leaderBoard << left << setw(20)  << player2.name   << "- " << right << setw(4) << player2.score;
            }
        }

        of_leaderBoard.close();                             // Closing the file output stream
    } else {                    // File does not exist (creates one with the current player score)
        if_leaderBoard.close();
        ofstream of_leaderBoard;                             // Opening a stream for file output
        of_leaderBoard.open(fullPath);                       // Opening the file to write into

        Player player = scoreboard.at(0);

        // writes the header of the leaderboard to the file
        of_leaderBoard << "Player              - Time" << endl
                       << "--------------------------" << endl
                       << left << setw(20)  << player.name   << "- " << right << setw(4) << player.score;;

        of_leaderBoard.close();
    }
}


void updateScoreboard(Player &player, const Maze &maze) {
    // Initializing a ScoreBoard (vector<Player>) to track the players in the leaderboard
    ScoreBoard scoreboard;
    const string PREFIX = "../input/";                                          // prefix for relative path file location
    const string fullPath = PREFIX + "MAZE_" + maze.number + "_WINNERS.txt";    // full path and filename


    getPlayerName(player);          // Gets and validates the player's name
    if (!cin.eof()) {                  // Continues to write if the player didn't signal 'EOF'
        scoreboard.push_back(player);  // Inserts the current game player in the scoreboard

        // Updates the scoreboard
        getScoreboard(fullPath, scoreboard, player);

        clearScreen();
        cout << endl << "The scoreboard has been updated, " << player.name << "! :)" << endl
             << "Press enter to continue to the menu ...";
        waitForConfirmation();
    }
}


void parseLines(ifstream &leaderBoard, ScoreBoard &scoreBoard, const Player &player) {
    // This loop will happen  until the end of the file
    while (!leaderBoard.eof()) {
        string line;
        getline(leaderBoard, line);                             // Stores the current line of the iteration on `line`

        size_t lastDashPos = line.rfind('-');                       // Gets the index of the last '-' occurrence
        cout << lastDashPos;
        string strScore = line.substr(lastDashPos + 2);           // Parses the `score` from the line
        int score = stoi(strScore);                                    // Converts store into an integer

        string firstPart = line.substr(0, lastDashPos);           // Parses the string of the line untiil '-'
        size_t lastAlphaPos = getLastAlphaIdx(firstPart);              // Gets the index of the first char that is not ' '

        cout << "I:" << firstPart << ":F" << endl;
        string name = firstPart.substr(0, lastAlphaPos + 1);    // Parses the `name` from the string
        cout << "NAME: " << name << endl;

        // Creates a player instance being the`Player` instance only fields that are relevant to initialize `name` and `score`
        Player player2;
        player2.name = name;
        player2.score = score;

        if (name == player.name && score > player.score) {                    // If the player already exists and the they were faster (lower score)
            continue;                                                         // The previous score was worse so it will not be printed (not appended to the vector)
        } else if (name != player.name){                                      // If it is a different player
            scoreBoard.push_back(player2);                                    // Appends the current `player2` instance to the `scoreBoard`
        } else {                                                              // If the player already exists and the they were slower (higher score)
            scoreBoard.erase(scoreBoard.begin());                             // Remove the player's score of the current run from the vector
            scoreBoard.push_back(player2);                                    // Appends the current `player2` instance to the `scoreBoard`
        }
    }
}


size_t getLastAlphaIdx(string str) {
    for (size_t i = str.length() - 1; i > 0; i--) {
        if (!isspace(str.at(i))) { return i; }
    }
    /*
     * if the first char of the string is ' ' the string is fully empty and -1 is returned
     * otherwise, it means that the string has one char different from 0 and, in that case returns 0 (first index)
     */
    return str.at(0) == ' ' ? -1 : 0;
}