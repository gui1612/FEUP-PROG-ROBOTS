//
// Created by ANTONIO on 5/9/2021.
//

#include "maze.h"


bool mazePick(Maze &maze) {
    bool playGame = false;
    short leaveConfirm = 1;
    // File Input loop that ends when the user sends "EOF" or when a valid maze is picked
    do {
        const unsigned int SLEEP_TIME = 2;
        short levelPick;

        cout << "Choose a level to play (0 to return to main menu)! " << endl;
        bool validInput = getInput<short>(levelPick);

        ifstream mazeFile;                              // File stream

        if (validInput) {                               // Input of valid type
            clearBuffer();
            if (levelPick == 0) {                       // Menu
                clearScreen();
                cout << "Returning to the main menu ..." << flush;
                sleepFor(SLEEP_TIME);                   // Animation to improve UX: waits 2 seconds
                clearScreen();
                leaveConfirm = 0;                       // Returns to the main menu
            } else {
                string fullFilePath;
                if (validMaze(levelPick, fullFilePath, mazeFile)) {
                    playGame = true;
                    leaveConfirm = 0;
                    bool valid;                         // Variable used to check if maze is correctly stored (dimensions)
                    maze = mazeOpen(fullFilePath, mazeFile, valid);
                    if (!valid) {                       // Checking if the maze is correctly stored (dimensions)
                        leaveConfirm = 1;
                        warnUser("mazefile");
                        playGame = false;
                    }
                    mazeFile.close();                    // Closing the maze `ifstream`
                    maze.number = (levelPick < 10) ? "0" + to_string(levelPick) : to_string(
                            levelPick);     // Setting the maze level to later use in the scoreboard
                } else {
                    warnUser("fileIO");
                }
            }
        } else if (!cin.eof())                           // Input of invalid type (not EOF)
            warnUser("fileIO");
    } while (leaveConfirm != 0 && !cin.eof());
    return playGame;
}


bool Maze::validMaze(const short &filename, string &fullPath, ifstream &mazeFile) {
    const string PREFIX = "../input/";               // Prefix containing the file where the maze files are at

    /*
    * `fileNameOrNullopt` will have a string if it is valid or `std::nullopt` if invalid
    * `fileNameOrNull` will contain a string with a maze filename if `fileNameOrNullopt` has a valid string or else "Null"
    */

    optional<string> fileNameOrNullopt = getMazeName(filename);
    string fileNameOrNull = fileNameOrNullopt.value_or("Null");

    if (fileNameOrNullopt != "Null") {                               // Valid filename (0 < fileName < 100)
        string filepath = PREFIX + fileNameOrNull;                   // Full filepath string
        fullPath = filepath;

        mazeFile.open(filepath.c_str());                             // Trying to open the file with the name `filepath` contained in ../mazes directory
        return mazeFile.good();
    } else {                                                         // Invalid filename ( 0 >= filename or 100 <= filename)
        return false;
    }
}


void Maze::mazeReplace(Maze &maze, Point point, char replacingChar) {
    maze.gameBoard.at(point.y).at(point.x) = replacingChar;
}


Maze Maze::mazeOpen(const string &levelPick, ifstream &mazeFile, bool &valid) {
    valid = true;
    unsigned int rows = 0, cols = 0;
    char sep;
    // First line parse ('rows' x 'columns')
    mazeFile >> rows;
    mazeFile >> sep;                                    // Fill char in between rows and columns
    mazeFile >> cols;

    vector<char> rowsVec;                               // Vector which will contain a single row
    vector<vector<char>> mazeVec;                       // 2D vector which will contain the chars in the maze at proper position

    mazeFile.ignore(1);

    size_t dimensions = rows * cols;
    size_t counter = 0;

    // Loop until the file is totally read (reach the end of file `EOF`)
    while (!mazeFile.eof()) {
        char mazeCurrChar = mazeFile.get();             // Gets the next char in the file
        if (mazeCurrChar == '\n') {                     // If the char is `\n` (reached the end of a row)
            mazeVec.push_back(rowsVec);
            rowsVec.clear();
        } else {
            rowsVec.push_back(mazeCurrChar);            // Appends the current char in the file to the rows vector (`rowsVec`)
            counter++;
        }
    }
    mazeVec.push_back(rowsVec);                         // Appends the last row to `rowsVec`
    mazeVec.back().pop_back();                          // Removes the newline char from the last position of the last line, since we don't need it
    counter--;                                          // Removing the additional value from counter, which shouldn't be added

    if (counter != dimensions) { valid = false; }       // Deems the maze invalid (wrong dimensions)

    // Initializing maze object
    Maze mazeInp{"0" , rows, cols, mazeVec};    // maze.number is just a initialization which will be changed
    return mazeInp;
}


optional<string> getMazeName(short levelChoice) {
    if (levelChoice < 1 || levelChoice > 99) {           // Invalid name for a maze file (there are only 99 mazes max)
        return nullopt;
    } else {                                             // Valid name for a maze
        // Checks if the user input number has one or two digits, turns it into a string, and, if it has one digit fills with a "0" at the left
        string firstPart = (levelChoice < 10) ? "0" + to_string(levelChoice) : to_string(levelChoice);
        string fileName = "MAZE_" + firstPart + ".TXT";  // Passes the end format of the maze file to `fileName`
        return fileName;
    }
}


void Maze::drawMaze(const Maze &maze) {
    clearScreen();
    for (yval y = 0; y < maze.rows; y++) {          // Row vectors
        for (xval x = 0; x < maze.columns; x++) {   // [Row][Column] (single position)
            char currChar = maze.gameBoard.at(y).at(x);
            cout << currChar << ' ';
        }
        cout << endl;                               // New line for the new row
    }
}
