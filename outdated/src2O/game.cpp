// Includes
#include "game.h"
#include "score.h"
#include "global.h"


void playGame(Maze &maze) {
    // Vector of phrases to be displayed when player wins
    vector<string> win = {"Well done, champ!!", "You have beat those evil robots. Good job!!",
                      "Perfect!!", "You've aced the game!", "Well done! Those robots were a bit RUSTy, am I right?"};
    // Vector of phrases to be displayed when player looses
    vector<string> loss = {"Better luck next time.", "Try again...", "You can only win if you keep on trying!",
                            "Don't let those robots survive!", "You lost..."};

    const int RAND_IDX = rand() % 5;

    Player player;
    vector<Robot> robotVec;

    // Getting all the necessary values for the player and robots
    initializeGame(maze, player);

    auto start = high_resolution_clock::now();                      // Game timer starts
    do {
        char key;                                                   // Initialize the player's input variable

        drawMaze(maze);
        cout << "Where do you wish to move to?" << endl;

        bool validInput = getInput<char>(key);                   // Checks if the input is valid for the type "char"

        if (validInput){                            // Valid input
            if (validMove(key)) {                   // Valid move
                // GAME ROUND
                clearBuffer();
                bool validPlayerUpdate = updatePlayer(player, key, maze);

                if (validPlayerUpdate) {            // Move doesn't violate the games' rules
                    if (player.alive) {updateAllRobots(player, maze);}      // Verifies that the player is alive
                } else {
                    warnUser("game-move");
                }
            } else {                                // Invalid input
                clearBuffer();
                warnUser("game");
            }
        } else {                                    // The user's input was not valid (correct type)
            warnUser("game");
        }
    } while (!cin.eof() && !playerLoss(player) && !playerWin(maze));

    auto end = high_resolution_clock::now();                                  // Game timer ends
    drawMaze(maze);

    duration<int> gameTime = duration_cast<duration<int>>(end - start);       // Calculates Game time

    if (playerWin(maze)) {
        cout << win.at(RAND_IDX) << endl                                      // Prints a winning message
             << "Your time: " << gameTime.count() << "s" << endl;
        player.score = gameTime.count();
        updateScoreboard(player, maze);                                    // Updates the scoreboard for the current maze
    } else {
        cout << loss.at(RAND_IDX) << endl
             << "Your time: " << gameTime.count() << "s" << endl;             // Displays the player game time
        waitForConfirmation();
    }

}


bool playerLoss(const Player &player) {
    return !player.alive;
}


bool playerWin(const Maze &maze) {
    return maze.aliveRobots == 0;
}


void initializeGame(Maze &maze, Player &player) {
    Point entPos;                   // Stub for the position vector of the entity (player/robot)
    ID idSelector = 1;              // Stub variable fot the future of the robots IDs

    //  Iterating through the maze object in order to find instances of players/robots
    for (yval y = 0; y < maze.rows; y++) {
        for (xval x = 0; x < maze.columns; x++) {
           char currPos = maze.gameBoard.at(y).at(x);                 // Char at current maze position
           entPos = {x, y};                                           // Current maze coordinate
            switch (currPos) {
                case ('H'): case ('h'):                               // Player
                    player.coordinates = {entPos.x, entPos.y};        // Giving the player instance its "coordinates" attribute
                    player.alive = isupper(currPos);                  // Giving the player instance its "alive" attribute
                    break;
                case ('R'): case ('r'):                               // Robot
                    bool alive = isupper(currPos);
                    Robot robot {alive, idSelector, entPos};          // Creates a `Robot` instance
                    maze.robotVec.push_back(robot);                   // Appends the robot to a vector existing robots
                    if (alive) {maze.aliveRobots++;}
                    idSelector++;                                     // Moving to the next ID
                    break;
            }
        }
    }
}


bool validMove(char key) {
    vector<char> movements = {'q', 'w', 'e', 'a', 's', 'd', 'z', 'x', 'c'};
    // Checks if `key` is in `movements`
    return find(movements.begin(), movements.end(), static_cast<char>(tolower(key))) != movements.end();
}