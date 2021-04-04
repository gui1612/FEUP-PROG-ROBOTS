#include "../includes/inp_out.h"
#include "../includes/global.h"
#include "../includes/menu.h"

#include <typeinfo>

using namespace std;

//TODO: Document !!!
void mazePick() {
    // File Input loop that ends when user sends "EOF"
    short leaveConfirm = 1;                            // Leaving confirmation (initialized at a value different of 0 not to leave the loop)
    do {
        const unsigned int SLEEP_TIME = 2;             // sleep time if the user decides to leave the maze picker stage
        short levelPick;                               // string type var to store the number of the selected maze

        cout << "Choose a level to play (0 to return to main menu)! " << endl;

        // gets an input and if it is successfully (`validInput` -> `true`) writes it on `levelPick` (if not clears the buffer)
        bool validInput = getInput<short>(levelPick);

        if (validInput) {               // Input of valid type
            clearBuffer();
            if (levelPick == 0) {       // Menu
                clearScreen();                          // Clears the screen
                cout << "Returning to the main menu ..." << flush;
                sleepFor(SLEEP_TIME);                   // Animation to improve UX: waits 2 seconds
                clearScreen();                          // Clears the screen
                leaveConfirm = 0;                       // signal to leave the do while loop (return to main menu)
            } else {
                /*
                 * `fileNameOrNullopt` will have a string if it is valid or `std::nullopt` if invalid
                 * `fileNameOrNull` will contain a string with a maze filename if `fileNameOrNullopt` has a valid string or else "Null"
                 */
                optional<string> fileNameOrNullopt = getMazeName(levelPick);
                string fileNameOrNull = fileNameOrNullopt.value_or("Null");

                if (fileNameOrNullopt != "Null")        // Valid filename (0 < fileName < 100)
                    mazeOpen(fileNameOrNull);           // Opens maze
                else                                    // Invalid filename ( 0 >= filename or 100 <= filename)
                    warnUser("fileIO");      // Warns the user about invalid filename
            }
        } else if (!cin.eof()) {          // Input of invalid type (not EOF)
            warnUser("fileIO");
        }
    } while (leaveConfirm != 0 && !cin.eof());
}


void mazeOpen(string levelPick) {
    ifstream mazeFile;                                      // input type var to open and read from
    int width = 0, height = 0;                     // string type var to store the content of levelFile

    const string PREFIX = "../mazes/";                      // prefix containing the file where the maze files are at
    string filepath = PREFIX + levelPick;                   // full filepath string

    mazeFile.open(filepath.c_str());
    if (mazeFile.fail()) {                                  // File not found (doesn't exist)
        cout << "Error opening, file not found!" << endl;
    } else {
        mazeFile >> height;
        mazeFile.ignore(3);
        mazeFile >> width;

        //TODO: Write the next code part smarter and cleaner
        vector<char> lines;
        vector<vector<char>> coordinates;

        while (!mazeFile.eof()) {
            char mazeCurr = static_cast<char>(mazeFile.get());
            if (mazeCurr == '\n') {
                coordinates.push_back(lines);
                lines.clear();
            } else {
                lines.push_back(mazeCurr);
            }
        }
        coordinates.push_back(lines);
        coordinates.back().pop_back();


        Maze maze;
        maze.height = height;
        maze.width = width;
        maze.coordinates = coordinates;

        drawMaze(maze);

    }
}


// TODO: Fix this function into an actually regular readable for loop
void drawMaze(const Maze &maze) {
    for (auto i : maze.coordinates) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
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