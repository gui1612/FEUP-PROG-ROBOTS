#include "entities.h"
#include "global.h"

///////// MAZE ///////////


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
                    maze.number = levelPick;              // Setting the maze level to later use in the scoreboard
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


void mazeReplace(Maze &maze, Point point, char replacingChar) {
    maze.gameBoard.at(point.y).at(point.x) = replacingChar;
}


Maze mazeOpen(const string &levelPick, ifstream &mazeFile) {
    unsigned int rows = 0, cols = 0;                    // initializing `rows` (horizontal) and  `columns` (vertical)
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
    Maze mazeInp{"0" , rows, cols, mazeVec};      // maze.number is just a initialization which will be changed
    return mazeInp;
}


optional<string> getMazeName(short levelChoice) {
    if (levelChoice < 1 || levelChoice > 99) {           // Invalid number for a maze file (there are only 99 mazes max)
        return nullopt;
    } else {                                             // Valid name for a maze
        // Checks if the user input number has one or two digits, turns it into a string, and, if it has one digit fills with a "0" at the left
        string firstPart = (levelChoice < 10) ? "0" + to_string(levelChoice) : to_string(levelChoice);
        string fileName = "MAZE_" + firstPart + ".TXT";  // Passes the end format of the maze file to `fileName`
        return fileName;
    }
}


void drawMaze(const Maze &maze) {
    clearScreen();
    for (yval y = 0; y < maze.rows; y++) {          // Row vectors
        for (xval x = 0; x < maze.columns; x++) {   // [Row][Column] (single position)
            char currChar = maze.gameBoard.at(y).at(x);
            /*
            if (currChar == 'D')
                cout << "\033[32m" << "*" << "\033[0m";
            else
                         */
                cout << currChar << ' ';

        }
        cout << endl;                               // New line for the new row
    }
}


///////// ROBOT ///////////


void updateAllRobots(Player &player, Maze &maze) {
    for (int i = 0; i < maze.robotVec.size(); i++) {

        Robot currRobot = maze.robotVec.at(i);
        Point lastPos = currRobot.coordinates;
        ID id = currRobot.id;

        //////////////DEBUG/////////////////
        cout << "{\n";
        for (auto robot : maze.robotVec) {
            Point p = robot.coordinates;
            cout << "\t{\n\talive: " << robot.alive << ",\n\tCoordinates: " <<  "(" << p.x << ", " << p.y << "), \n\t" << "ID: "<< robot.id << "\n\t}, \n";
        }
        cout << "}" << endl;
        ////////////////////////////////////

        if (!currRobot.alive) {continue;};

        Point newPos = bestMove(currRobot, player, maze);

        char charInPos = maze.gameBoard.at(newPos.y).at(newPos.x);

        if (charInPos == 'R' || charInPos == 'r') {      // Robot gets stuck
            cout << "Robot gets stuck" << endl;
            maze.robotVec.at(i).alive = false;           // First robot dies
            maze.aliveRobots--;                          // Updates aliveRobots
            maze.robotVec.at(i).coordinates = newPos;    // Coordinates update
            for (int j = 0; j < maze.robotVec.size(); j++) {
                Robot secRobot = maze.robotVec.at(j);
                if (currRobot == secRobot) {continue;};

                if (secRobot.coordinates == newPos) {            // If there's a robot collision, kills the other robot
                    maze.robotVec.at(j).alive = false;           // Second robot dies
                    if (secRobot.alive) {maze.aliveRobots--;};                        // Updates aliveRobots
                    break;
                }
                mazeReplace(maze, lastPos, ' ');
                mazeReplace(maze, newPos, 'r');
            }

        } else if (charInPos == '*') {                  // Robot moves to electric fence
            cout << "Robot collides with eletric fence";
            maze.robotVec.at(i).alive = false;           // First robot dies
            maze.aliveRobots--;                          // Updates aliveRobots
            mazeReplace(maze, lastPos, 'r');
            mazeReplace(maze, newPos, 'D');
        } else if (charInPos == 'D') {                  // Robot moves to non-electric fence
            continue;
        } else if (charInPos == 'H') {                  // Player gets caught by robot
            cout << "4" << endl;
            player.alive = false;                       // Player dies
            mazeReplace(maze, lastPos, 'R');
            mazeReplace(maze, newPos, 'h');
            break;
        } else {                                        // Regular robot move
            maze.robotVec.at(i).coordinates = newPos;   // Updates robot position
            mazeReplace(maze, lastPos, ' ');
            mazeReplace(maze, newPos, 'R');
        }
    }
}


Point bestMove(const Robot &robot, const Player &player, const Maze &maze) {
    xval x = robot.coordinates.x;
    yval y = robot.coordinates.y;
    cout << "ROBOT (" << x << ", " << y << ");" << endl;

    // Possible move positions for the Robot
    vector<Point> moveVec = {{x-1, y-1}, {x, y-1}, {x+1, y-1},
                             {x-1, y},             {x+1, y},
                             {x-1, y+1}, {x, y+1}, {x+1, y+1}};

    double minDist = numeric_limits<double>::max();                     // Max double
    Point bestMove;                                                     // Variable to store the optimal position to move
    for (int i = 0; i < moveVec.size(); i++) {
        if (!outOfBounds(moveVec.at(i), maze)) {                        // The position is inside the maze bounds
            double dist = pointDist(moveVec.at(i), player.coordinates); // Distance between that move option and the player
            if (dist < minDist) {       // If that move is the best until the moment
                minDist = dist;
                bestMove = moveVec.at(i);
            }
        }
    }

    cout << "Move vec (" << bestMove.x << ", " << bestMove.y << ");" << endl;
    return bestMove;
}


void robotDraw(Point lastPos, const Robot &robot, Maze &maze) {
    maze.gameBoard.at(lastPos.y).at(lastPos.x) = ' ';         // Replacing robot last position
    mazeReplace(maze, robot.coordinates, 'R');   // Replacing robot new position
}

///////// PLAYER ///////////


bool updatePlayer(Player &player, char key, Maze &maze){
    // Player position before the movement
    Point lastPos = {player.coordinates.x, player.coordinates.y};

    switch (static_cast<char>(tolower(key))) {
        case('q'):                             // Up left
            player.coordinates.x--;
            player.coordinates.y--;
            break;
        case ('w'):                            // Up
            player.coordinates.y--;
            break;
        case('e'):                             // Up right
            player.coordinates.x++;
            player.coordinates.y--;
            break;
        case('a'):                             // Left
            player.coordinates.x--;
            break;
        case('s'):                             // Stay
            break;
        case('d'):                             // Right
            player.coordinates.x++;
            break;
        case('z'):                             // Down left
            player.coordinates.x--;
            player.coordinates.y++;
            break;
        case('x'):                              // Down
            player.coordinates.y++;
            break;
        case('c'):                              // Down right
            player.coordinates.x++;
            player.coordinates.y++;
            break;
    }
    // New position
    xval x = player.coordinates.x;
    yval y = player.coordinates.y;

    if (!outOfBounds(player.coordinates, maze)) {                                // Checks if the player is inside the maze bounds
        char newPosChar = maze.gameBoard.at(y).at(x);
        if (newPosChar == ' ' || newPosChar == 'H') {                            // Valid player movement
            playerDraw(lastPos, player, maze);                                // Updates coordinates on the maze
            return true;
        } else {                                                                 // Invalid player move (player moves to fences/dead robot/ alive robot)
            player.coordinates = lastPos;
            return false;
        }
    } else {                                                                     // Invalid move (out of maze bounds)
        player.coordinates = lastPos;
        return false;
    }
}


void playerDraw(Point lastPos, const Player &player, Maze &maze) {
    maze.gameBoard.at(lastPos.y).at(lastPos.x) = ' ';        // Replacing player last position
    mazeReplace(maze, player.coordinates, 'H'); // Replacing player new position
}


double pointDist(Point p1, Point p2) {
    return sqrt(pow(p2.y - p1.y, 2) + pow(p2.x - p1.x, 2));
}


bool outOfBounds(const Point &pos, const Maze &maze) {
    const unsigned int HEIGHT = maze.rows, WIDTH = maze.columns;        // Creating height and width variables by looking at the maze instance
    return !(0 <= pos.y && pos.y < HEIGHT && 0 <= pos.x && pos.x < WIDTH);                  // Returning true (if inbounds) and false (if out of bounds)
}