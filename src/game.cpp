#include "game.h"
#include "global.h"


void playGame(Maze &maze) {
    // Vector of phrases to be displayed when player wins
    vector<string> win = {"Well done, champ!!", "You have beat those evil robots. Good job!!",
                      "Perfect!!", "You've aced the game", "Well done! Those robots were a bit RUSTy, am I right?"};
    // Vector of phrases to be displayed when player looses
    vector<string> loss = {"Better luck next time.", "Try again", "You can only win if you keep trying!",
                            "Don't let those robots survive!", "You loss"};

    const int RAND_IDX = rand() % 6;


    Player player;
    RobotMap robotMap;


    // Getting all the necessary values for the player and robots
    initializeGame(maze, player, robotMap);

    auto start = high_resolution_clock::now();                      // Game timer starts
    do {
        char key;                                                                   // Initialize the player's input variable

        drawMaze(maze);
        cout << "Where do you wish to move to?" << endl;

        bool validInput = getInput<char>(key);                                    // Checks if the input is valid for the type "char"

        if (validInput){                            // Valid input
            if (validMove(key)) {                   // Valid move
            // GAME ROUND

                clearBuffer();
                bool validPlayerUpdate = updatePlayer(player, key, maze);

                if (validPlayerUpdate) {            // Move doesn't violate the games' rules
                    updateAllRobot(robotMap, player, maze);
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
    } while (!cin.eof() && player.alive && robotMap.size() != 0);

    auto end = high_resolution_clock::now();                                        // Game timer ends
    duration<double> gameTime = duration_cast<duration<double>>(end - start);       // Calculates Game time
    cout << gameTime.count() <<  endl;
}


bool playerLoss(const Player &player) {
    return !player.alive;
}


bool playerWin(const Player &player, RobotMap robotMap) {
    return (player.alive && !robotMap.empty());
}


void initializeGame(Maze maze, Player &player, RobotMap &robotIdMap) {
    Point entPos;                   // Stub for the position vector of the entity (player/robot)
    //vector<int> robotIDS;           // Currently not used, but in the future a vector to store all IDs and keep track of living robots
    ID idSelector = 1;             // Stub variable fot the future of the robots IDs

    //  Iterating through the maze object in order to find instances of players/robots
    for (yval y = 0; y < maze.rows; y++) {
        for (xval x = 0; x < maze.columns; x++) {
           char currPos = maze.coordinates.at(y).at(x);              // Char at current maze position
           entPos = {x, y};                                          // Current maze coordinate
            switch (currPos) {
                case ('H'): case ('h'):                              // Player
                    player.coordinates = {entPos.x, entPos.y};       // Giving the player instance its "coordinates" attribute
                    player.alive = isupper(currPos);                 // Giving the player instance its "alive" attribute
                    break;
                case ('R'): case ('r'):                              // Robot
                    Robot robot;
                    robot.coordinates = {entPos.x, entPos.y};       // Giving the robot instance its "coordinates" attribute
                    robot.alive = isupper(currPos);                 // Giving the robot instance its "alive" attribute
                    if (robot.alive) {          // Robot (alive)
                        robot.id = idSelector;                      // Giving the robot its ID
                        robotIdMap[idSelector] = robot;
                        idSelector++;                               // Moving to the next ID
                    }
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