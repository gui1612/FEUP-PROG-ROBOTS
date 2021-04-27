// Includes
#include "global.h"
#include "menu.h"
#include "game.h"


void menu() {
    short confirm = 1;
    // Menu loop will ends when the user sends "EOF" or when they confirm to Exit (option 0)
    do {
        short menuPick;

        const string banner = R"(
       ______       ____      ____       ____      _______                _____                  __  __     ______
       |  __ \     / __ \    |  _ \     / __ \    |__   __|              / ____|       /\       |  \/  |   |  ____|
       | |__) |   | |  | |   | |_) |   | |  | |      | |                | |  __       /  \      | \  / |   | |__
       |  _  /    | |  | |   |  _ <    | |  | |      | |                | | |_ |     / /\ \     | |\/| |   |  __|
       | | \ \    | |__| |   | |_) |   | |__| |      | |                | |__| |    / ____ \    | |  | |   | |____
       |_|  \_\    \____/    |____/     \____/       |_|                 \_____|   /_/    \_\   |_|  |_|   |______|
        )";

        // Banner and menu options display
        cout << banner << endl;
        cout << R"(
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
        } else if (!cin.eof()) {
            warnUser("menu");
        }
    } while (confirm != 0 && !cin.eof());

    clearScreen();
    cout << R"(
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

            cout << "Are you sure you want to exit (0 to confirm)?" << endl;
            bool validInput = getInput<short>(confirm);

            if (cin.eof()) { break; }                    // EOF flag

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
            if (!cin.eof()) { clearScreen();}
            break;
        }
        case 2: {                                        // Play
            clearScreen();
            /////GAME START
            Maze maze;                                   // Initializes the `Maze` for the current game
            bool play = mazePick(maze);              // Checks if the player wants to play
            if (play) {playGame(maze);}              // If the player wants to play, starts the game
            break;
            /////GAME END
        }
        case 3:                                          // Leaderboard
            displayLeaderboard();
            break;
        default: {                                       // The input was of type `int`, but not a valid option
            warnUser("menu");
        }
    }
}


void displayRules() {
    cout << R"(
  --------------------------------------------------------------------------------------------------------------------
  |                                                 Instructions                                                     |
  |                                                                                                                  |
  |   > MOVEMENT                                                                                                     |
  |                                                                                                                  |
  |               -------------------                               -----------------------------------              |
  |               |  Q  |  W  |  E  |                               |  UP LEFT  |   UP   |  UP RIGHT  |              |
  |               |-----------------|                               |---------------------------------|              |
  |               |  A  |  S  |  D  |                   =>          |    LEFT   |  STAY  |    RIGHT   |              |
  |               |-----------------|                               |---------------------------------|              |
  |               |  Z  |  X  |  C  |                               | DOWN LEFT |  DOWN  | DOWN RIGHT |              |
  |               -------------------                               -----------------------------------              |
  |                                                                                                                  |
  |                                                                                                                  |
  |   > NOTATION                                                    |   > MAZE (*)                                   |
  |                                                                 |                                                |
  |    H/h -> Player (alive/dead)                                   |    High voltage fences/posts                   |
  |    R/r -> Robot (alive/dead)                                    |                                                |
  |    r   -> Several Robots collision                              |                                                |
  |    *   -> Fence/Post                                            |                                                |
  |                                                                                                                  |
  |   > PLAYER (H/h)                                                |   > ROBOTS (R/r)                               |
  |                                                                 |                                                |
  |    Overview                                                     |    Death                                       |
  |     Robots will try to destroy the player                       |     Robots will die in contact with            |
  |                                                                 |     walls/each other                           |
  |                                                                 |                                                |
  |    Movement                                                     |    Movement                                    |
  |     The player can move in any direction to an adjacent cell    |     For each player's cell movement the robot  |
  |     (horizontally, vertically, or diagonally)                   |     also moves one cell in the direction of    |
  |                                                                 |     the shortest path                          |
  |                                                                                                                  |
  |                                                                                                                  |
  |   > WIN CONDITION                                               |   > GAME OVER                                  |
  |                                                                 |                                                |
  |     All robots are destroyed                                    |    Player touches maze or robot(s)             |
  |                                                                                                                  |
  |                                                                                                                  |
  |                                                                                                                  |
  |   Press ENTER to return to the main menu...                                                                      |
  |                                                                                                                  |
  --------------------------------------------------------------------------------------------------------------------
    )";
}