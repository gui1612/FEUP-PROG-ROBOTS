#include "../includes/maze.h"
#include "../includes/global.h"
#include "../includes/menu.h"

using namespace std;


bool mazePick(Maze &maze) {
    bool playGame = false;
    short leaveConfirm = 1;                            // Leaving confirmation (initialized at a value different of 0 not to leave the loop)
    // File Input loop that ends when user sends "EOF" or when a valid maze is picked
    do {
        const unsigned int SLEEP_TIME = 2;             // sleep time if the user decides to leave the maze picker stage
        short levelPick;                               // string type var to store the number of the selected maze


        cout << "Choose a level to play (0 to return to main menu)! " << endl;

        bool validInput = getInput<short>(levelPick);
        ifstream mazeFile;                              // File stream

        if (validInput) {                               // Input of valid type
            clearBuffer();
            if (levelPick == 0) {                       // Menu
                clearScreen();
                cout << "Returning to the main menu ..." << flush;
                sleepFor(SLEEP_TIME);                    // Animation to improve UX: waits 2 seconds
                clearScreen();
                leaveConfirm = 0;                        // Returns to the main menu
            } else {
                string fullFilePath;
                if (validMaze(levelPick, fullFilePath, mazeFile)) {
                    playGame = true;
                    leaveConfirm = 0;
                    maze = mazeOpen(fullFilePath, mazeFile);
                } else {
                    warnUser("fileIO");
                }
            }
        } else if (!cin.eof())                             // Input of invalid type (not EOF)
            warnUser("fileIO");
        } while (leaveConfirm != 0 && !cin.eof());
    return playGame;
}


bool validMaze(const short &filename, string &fullPath, ifstream &mazeFile) {
    const string PREFIX = "../input/";                      // prefix containing the file where the maze files are at

    /*
    * `fileNameOrNullopt` will have a string if it is valid or `std::nullopt` if invalid
    * `fileNameOrNull` will contain a string with a maze filename if `fileNameOrNullopt` has a valid string or else "Null"
    */
    optional<string> fileNameOrNullopt = getMazeName(filename);
    string fileNameOrNull = fileNameOrNullopt.value_or("Null");

    if (fileNameOrNullopt != "Null") {       // Valid filename (0 < fileName < 100)
        string filepath = PREFIX + fileNameOrNull;                   // full filepath string
        fullPath = filepath;

        mazeFile.open(filepath.c_str());                        // Trying to open the file with the name `filepath` contained in ../mazes directory
        return mazeFile.good();

    } else {                                    // Invalid filename ( 0 >= filename or 100 <= filename)
        return false;
    }
}


Maze mazeOpen(const string &levelPick, ifstream &mazeFile) {
    unsigned int rows = 0, cols = 0;                        // initializing `rows` (horizontal) and  `columns` (vertical)

        // First line parse ('rows' x 'columns')
        mazeFile >> rows;                                   // Rows
        mazeFile.ignore(3);                              // Fill chars in between rows and columns
        mazeFile >> cols;                                   // Columns

        vector<char> rowsVec;                               // Vector which will contain a single row
        vector<vector<char>> mazeVec;                       // 2D vector which will contain the chars in the maze at proper position

        mazeFile.ignore(1);

        // Loop until the file is totally read (reach the end of file `EOF`)
        while (!mazeFile.eof()) {
            char mazeCurrChar = mazeFile.get();             // Gets the next char in the file
            if (mazeCurrChar == '\n') {                     // If the char is `\n` (reached the end of a row)
                mazeVec.push_back(rowsVec);
                rowsVec.clear();
            } else {
                rowsVec.push_back(mazeCurrChar);            // Appends the current char in the file to the rows vector (`rowsVec`)
            }
        }
        mazeVec.push_back(rowsVec);                         // Appends the last row to `rowsVec`
        mazeVec.back().pop_back();                          // Removes the newline char from the last position of the last line, since we don't need it

        // Initializing maze object
        Maze mazeInp{rows, cols, mazeVec};
        return mazeInp;
}


optional<string> getMazeName(short levelChoice) {
    if (levelChoice < 1 || levelChoice > 99) {           // Invalid number for a maze file (there are only 99 mazes max)
        return nullopt;
    } else {                                             // Valid name for a maze
        // Checks if the user input number has one or two digits, turns it into a string, and, if it has one digit fills with a "0" at the left
        string firstPart = (levelChoice < 10) ? "0" + to_string(levelChoice) : to_string(levelChoice);
        string fileName = "MAZE_" + firstPart + ".txt";  // Passes the end format of the maze file to `fileName`
        return fileName;
    }
}


void drawMaze(const Maze &maze) {
    clearScreen();
    for (yval y = 0; y < maze.rows; y++) {          // Row vectors
        for (xval x = 0; x < maze.columns; x++) {   // [Row][Column] (single position)
            cout << maze.coordinates.at(y).at(x);   // Printing a single char of the maze
        }
        cout << endl;                               // New line for the new row
    }
}