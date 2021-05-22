#include "Menu.h"
#include "Game.h"

#include<fstream>
#include<sstream>
// Menu


void menu() {
    short confirm = 1;
    // Menu loop will ends when the user sends "EOF" or when they confirm to Exit (option 0)
    do {
        short menuPick;

        const std::string banner = R"(
       ______       ____      ____       ____      _______                _____                  __  __     ______
       |  __ \     / __ \    |  _ \     / __ \    |__   __|              / ____|       /\       |  \/  |   |  ____|
       | |__) |   | |  | |   | |_) |   | |  | |      | |                | |  __       /  \      | \  / |   | |__
       |  _  /    | |  | |   |  _ <    | |  | |      | |                | | |_ |     / /\ \     | |\/| |   |  __|
       | | \ \    | |__| |   | |_) |   | |__| |      | |                | |__| |    / ____ \    | |  | |   | |____
       |_|  \_\    \____/    |____/     \____/       |_|                 \_____|   /_/    \_\   |_|  |_|   |______|
        )";

        // Banner and menu options display
        std::cout << banner << std::endl;
        std::cout << R"(
                                        ----------------------------------------------
                                        |                                            |
                                        |                (3) Leaderboard             |
                                        |                (2) Play                    |
                                        |                (1) Rules                   |
                                        |                (0) Exit                    |
                                        |                                            |
                                        ----------------------------------------------
                    )";

        bool validInput = getInput<short>(menuPick);

        if (validInput) {
            clearBuffer();
            menuChoice(menuPick, confirm);
        } else if (!std::cin.eof()) {
            warnUser("menu");
        }
    } while (confirm != 0 && !std::cin.eof());

    clearScreen();
    std::cout << R"(
              \_/
             (* *)                            ___  __  __   ____
            __)#(__                          / _ ) \ \/ /  / __/
           ( )...( )(_)                     / _  |  \  /  / _/
           || |_| ||//                     /____/   /_/  /___/
        >==() | | ()/               Humanity appreciates your efforts!
            _(___)_
           [-]   [-]
            )";
}

void menuChoice(short choice, short &confirm) {
    switch (choice) {
        case 0: {                                        // Exit
            clearScreen();

            std::cout << "Are you sure you want to exit (0 to confirm)?" << std::endl;
            bool validInput = getInput<short>(confirm);

            if (std::cin.eof()) { break; }                    // EOF flag

            if (!validInput) {
                confirm = 1;                             // Resets `confirm` (user doesn't want to exit)
            } else {
                clearBuffer();                           // Clears the buffer
            }
            clearScreen();
            break;
        }
        case 1: {                                        // Rules
            clearScreen();
            displayRules();
            waitForConfirmation();
            if (!std::cin.eof()) { clearScreen();}
            break;
        }
        case 2: {                                        // Play
            clearScreen();
            std::optional<std::string> mazeName = mazePick();
            std::string const mazeNameOrNull = mazeName.value_or("Null");
            if (mazeNameOrNull != "Null") {
                try {
                    Game game(mazeNameOrNull);              // Tries to construct a Maze object
                    game.play();                            // If no exception occurs the Game is played
                } catch (const std::runtime_error &err) {   //
                    std::cout << err.what() << std::endl;
                }
            }
            break;
        }
        case 3: {                                          // Leaderboard
            displayLeaderboard();
            break;
        }
        default: {                                       // The input was of type `int`, but not a valid option
            warnUser("menu");
        }
    }
}

void displayRules() {
    std::ifstream fRules;
    fRules.open("../input/RULES.TXT");
    std::string str;

    if(fRules.is_open()) {
        std::cout << fRules.rdbuf() << std::endl; // reading data
    }
    fRules.close();
}


std::optional<std::string> mazePick() {
    short leaveConfirm = 1;
    // File Input loop that ends when the user sends "EOF" or when a valid maze is picked
    do {
        const unsigned int SLEEP_TIME = 2;
        short levelPick;
        std::ifstream mazeFile;

        std::cout << "Choose a level to play (0 to return to main menu)! " << std::endl;
        bool validInput = getInput<short>(levelPick);

        if (validInput) {                               // Input of valid type
            clearBuffer();
            if (levelPick == 0) {                       // Menu
                clearScreen();
                std::cout << "Returning to the main menu ..." << std::flush;
                sleepFor(SLEEP_TIME);                   // Animation to improve UX: waits 2 seconds
                clearScreen();
                leaveConfirm = 0;                       // Returns to the main menu
            } else {
                std::string fullFilePath;
                if (validMaze(levelPick, fullFilePath, mazeFile)) {
                    mazeFile.close();
                    leaveConfirm = 0;
                    return fullFilePath;
                } else {
                    mazeFile.close();
                    warnUser("fileIO");
                }
            }
        } else if (!std::cin.eof())                     // Input of invalid type (not EOF)
            warnUser("fileIO");
    } while (leaveConfirm != 0 && !std::cin.eof());

    return std::nullopt;
}


bool validMaze(const short &filename, std::string &fullPath, std::ifstream &mazeFile) {
    const std::string PREFIX = "../input/";               // Prefix containing the file where the maze files are at


    /*
    * `fileNameOrNullopt` will have a string if it is valid or `std::nullopt` if invalid
    * `fileNameOrNull` will contain a string with a maze filename if `fileNameOrNullopt` has a valid string or else "Null"
    */

    std::optional<std::string> fileNameOrNullopt = getMazeName(filename);
    std::string fileNameOrNull = fileNameOrNullopt.value_or("Null");

    if (fileNameOrNullopt != "Null") {                               // Valid filename (0 < fileName < 100)
        std::string filepath = PREFIX + fileNameOrNull;              // Full filepath string
        fullPath = filepath;

        mazeFile.open(filepath);
        return mazeFile.good();
    } else {                                                         // Invalid filename ( 0 >= filename or 100 <= filename)
        return false;
    }
}


void displayLeaderboard() {
    const unsigned int SLEEP_TIME = 2;
    const std::string PREFIX = "../input/";                   // Prefix containing the file where the maze files are at
    short leaderBoardNum;
    short leaveConfirm = 1;

    do {
        std::ifstream leaderboardFile;
        clearScreen();
        std::cout << "Insert the number of the maze (0 to leave):";
        bool validInput = getInput<short>(leaderBoardNum);

        if (validInput && leaderBoardNum > 0 && leaderBoardNum < 99) {
            clearBuffer();
            // If the number has one digit fills with a '0' on the left
            std::string num = leaderBoardNum < 10 ? "0" + std::to_string(leaderBoardNum) : std::to_string(leaderBoardNum);
            std::string fullFilepath = PREFIX + "MAZE_" + num + "_WINNERS.txt";  // Gets the relative file path and the filename
            leaderboardFile.open(fullFilepath);                             // Opening the file

            if (leaderboardFile.is_open()) {        // File exists
                std::cout << leaderboardFile.rdbuf() << std::endl;                    // Displays the scoreboard
                std::cout << "Press Enter to continue ...";
                waitForConfirmation();
                clearScreen();
                leaderboardFile.close();            // Closes the stream for file input
            } else {                                // File does not exist
                warnUser("leaderboard");
            }
        } else if (leaderBoardNum == 0) {           // User wants to leave to the main menu
            leaveConfirm = 0;
            std::cout << "Returning to the main menu ..." << std::flush;
            sleepFor(SLEEP_TIME);                   // Animation to improve UX: waits 2 seconds

        } else if (!std::cin.eof()) {
            warnUser("fileIO");
        }
        leaderboardFile.close();
    } while (!std::cin.eof() && leaveConfirm != 0);
    clearScreen();                                   // Clears the screen before going to the main menu
}

std::optional<std::string> getMazeName(short levelChoice) {
    if (levelChoice < 1 || levelChoice > 99) {           // Invalid name for a maze file (there are only 99 mazes max)
        return std::nullopt;
    } else {                                             // Valid name for a maze
        // Checks if the user input number has one or two digits, turns it into a string, and, if it has one digit fills with a "0" at the left
        std::string firstPart = (levelChoice < 10) ? "0" + std::to_string(levelChoice) : std::to_string(levelChoice);
        std::string fileName = "MAZE_" + firstPart + ".TXT";  // Passes the end format of the maze file to `fileName`
        return fileName;
    }
}
