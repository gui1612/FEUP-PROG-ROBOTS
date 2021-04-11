#include "global.h"
#include "menu.h"
#include "game.h"


void menu() {
    short confirm = 1;                       // Leaving confirmation (initialized at a value different of 0 not to leave the loop)
    // Menu loop will end either when user sends "EOF" or when he double confirms he wants to Exit (option 0 of the menu)
    do {
        short menuPick;                      // Menu choice

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

        // gets an input and if it is successfully (`validInput` -> `true`) writes it on `menuPick` (if not clears the buffer)
        bool validInput = getInput<short>(menuPick);

        if (validInput) {               // Valid input type
            clearBuffer();                    // Clears the buffer from the last `cin` call
            menuChoice(menuPick, confirm);
        } else if (!cin.eof()) {              // If the input is invalid (with the exception of `EOF`) the screen is cleared and options are displayed again
            warnUser("menu");      // Warns the user about wrong input
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
        case 0: {               // Exit
            clearScreen();
            cout << "Are you sure you want to exit (0 to confirm)?\n";

            // gets an input and if it is successfully (`validInput` -> `true`) writes it on `confirm` (if not clears the buffer)
            bool validInput = getInput<short>(confirm);

            if (cin.eof()) {break;}     // EOF flag

            if (!validInput) {    // Invalid input
                confirm = 1;            // Resets `confirm` for cases in which user inputs a problematic value
                warnUser("menu");             // Warns the user about invalid input
            } else {                    // Valid input
                clearBuffer();          // Clears the buffer
            }
            clearScreen();              // clears the screen before the next menu display or the end of the game
            break;
        }
        case 1: {              // Rules
            clearScreen();          // Clears the screen
            displayRules();         // Displays the rules
            waitForConfirmation();  // Waits for user input
            if (!cin.eof()) { clearScreen();}  // Clears the screen if the user didn't press EOF in the confirmation
            break;
        }
        case 2: {               // Play
            clearScreen();
            /////GAME START
            Maze maze;
            bool play = mazePick(maze);
            if (play)
                playGame(maze);
            break;
            /////GAME END
        }
        case 3:
            displayLeaderboard();
            break;
        default: {              // The input was of type `int`, but not a valid option
            warnUser("menu");             // Warns the user about wrong input
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