#include "Game.h"
#include "globaldefs.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <iomanip>

Game::Game(const std::string &filename) {

    std::ifstream mazeFile;
    mazeFile.open(filename);

    //Maze maze;

    unsigned int rows = 0, cols = 0, id = 1, counter = 0;
    xval x = 0;
    yval y = 0;
    char sep;

    mazeFile >> rows;
    mazeFile >> sep;
    mazeFile >> cols;

    mazeFile.ignore(1);

    std::string name = filename.substr(14, 2);

    _maze.setCols(cols);
    _maze.setRows(rows);
    _maze.setName(name);

    unsigned int area = _maze.getMazeArea();

    while (!mazeFile.eof()) {
        char chr = mazeFile.get();
        if (x != cols) {                                            // Checks if the x coordinate is within the bounds of the maze
            counter++;                                              // Keeps track of the amount of characters of the maze
            if (tolower(chr) == 'h') {                              // Player
                Player player(chr, {x, y});
                _player = player;
            } else if (chr == 'R') {                                // Alive robot
                Robot robot(chr, {x, y}, id, Robot::ALIVE);
                _robot.push_back(robot);
                id++;
            } else if (chr == 'r') {                                // Dead robot
                Robot robot(chr, {x, y}, id, Robot::DEAD);
                _robot.push_back(robot);
                id++;
            } else if ( chr == '*' || chr == '+' || chr == 'O') {   // Fence / Exit
                Post post({x, y}, chr);
                _maze.addPost(post);
            }
            x++;
        } else {
            x = 0;
            y++;
        }
    }

    /* Error throwing if the maze has invalid dimensions
     * @note Player doesn't need to be cleared since it won't be used unless it is set
     * again.
     */
    if (counter != area) {
        _robot.clear();
        _maze.clear();
        throw std::runtime_error("Invalid mazefile: The file format is not correct!");
    }

}

void Game::play() {
    // Vector of phrases to be displayed when player wins
    std::vector<std::string> win = {"Well done, champ!!", "You have beat those evil robots. Good job!!",
                          "Perfect!!", "You've aced the game!", "Well done! Those robots were a bit RUSTy, am I right?"};
    // Vector of phrases to be displayed when player looses
    std::vector<std::string> loss = {"Better luck next time.", "Try again...", "You can only win if you keep on trying!",
                           "Don't let those robots survive!", "You lost..."};

    const int RAND_IDX = rand() % 5;

    auto start = std::chrono::high_resolution_clock::now();                      // Game timer starts
    do {
        char key;                                                   // Initialize the player's input variable

        drawMaze();
        std::cout << "Where do you wish to move to?" << std::endl;

        bool validInput = getInput<char>(key);                   // Checks if the input is valid for the type "char"
        clearScreen();

        if (validInput){                            // Valid input
            if (validMove(key)) {                   // Valid move
                // GAME ROUND

                clearBuffer();
                bool validPlayerUpdate = updatePlayer(key);

                if (validPlayerUpdate) {            // Move doesn't violate the games' rules
                    if (_player.win()) {            // Player found an exit
                        updateAllRobots();
                        break;
                    } else {
                        updateAllRobots();
                    }
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
    } while (!std::cin.eof() && _player.isAlive() && !_player.win());

    auto end = std::chrono::high_resolution_clock::now();                                  // Game timer ends
    drawMaze();

    std::chrono::duration<int> gameTime = std::chrono::duration_cast<std::chrono::duration<int>>(end - start);       // Calculates Game time

    if (_player.win()) {
        std::cout << win.at(RAND_IDX) << std::endl                                      // Prints a winning message
             << "Your time: " << gameTime.count() << "s" << std::endl;
        _player.setScore(gameTime.count());
        updateScoreboard();                                    // Updates the scoreboard for the current maze
    } else {
        std::cout << loss.at(RAND_IDX) << std::endl
             << "Your time: " << gameTime.count() << "s" << std::endl;             // Displays the player game time
        waitForConfirmation();
    }
}

bool Game::validMove(char key) {
    std::vector<char> movements = {'q', 'w', 'e', 'a', 's', 'd', 'z', 'x', 'c'};
    // Checks if `key` is in `movements`
    return std::find(movements.begin(), movements.end(), static_cast<char>(tolower(key))) != movements.end();
}


void Game::drawMaze() {
    Point pos{0, 0};
    PostVec allPostList = _maze.getAllList();
    unsigned int mazeArea = _maze.getMazeArea();

    while (((pos.x + 1) * (pos.y + 1)) <= mazeArea) {                       // Looping from (0,0) to (cols, rows), while the area of the shape formed by pos and (0,0) isn't the area of the maze
        bool fillWithSpace = true;                                          // Flag keeping track if there aren't any robots/player/posts in coordinates pos

        auto robotIt = std::find_if(_robot.begin(), _robot.end(), [&](const Robot &x) {
            return x.getCoordinates() == pos;
        });

        if ( robotIt != _robot.end()) {
            char symbol = robotIt->getStatus();
            // *it is the Robot found
            if ((pos.x + 1) == _maze.getColumns()) {
                std::cout << symbol << '\n';
                pos.y++; pos.x = 0;
            } else {
                std::cout << symbol << std::flush;             // Drawing player
                pos.x++;
            }
            fillWithSpace = false;
        }

        auto postIt = std::find_if(allPostList.begin(), allPostList.end(), [&](const Post &x) {
            return x.getCoordinates() == pos;
        });

        if ( postIt != allPostList.end()) {
            char symbol = postIt->getSymbol();
            // *it is the Robot found
            if ((pos.x + 1) == _maze.getColumns()) {
                std::cout << symbol << '\n';
                pos.y++; pos.x = 0;
            } else {
                std::cout << symbol << std::flush;             // Drawing player
                pos.x++;
            }
            fillWithSpace = false;
        }

        if (_player.getCoordinates() == pos) {                              // The player is in pos
            if ((pos.x + 1) == _maze.getColumns()) {                        // Checking it isn't the last character of the row
                std::cout << _player.getStatus() << '\n';                   // Drawing player
                pos.y++; pos.x = 0;                                         // Moving to next row
            } else {
                std::cout << _player.getStatus() << std::flush;             // Drawing player
                pos.x++;                                                    // Moving to next column
            }
            fillWithSpace = false;
        }

        if (fillWithSpace) {                                                // Checking if there weren't any robots/posts/player in pos
            std::cout << " " << std::flush;                                 // Drawing a space
            pos.x++;                                                        // Moving to next column
        }
    }
    std::cout << std::endl;

}


bool Game::updatePlayer(const char key) {
    // Player position before the movement
    Point lastPos = _player.getCoordinates();
    xval x = _player.getCoordinates().x;
    xval y = _player.getCoordinates().y;

    switch (static_cast<char>(tolower(key))) {
        case('q'):  _player.moveTo({--x,--y}); break;              // Up left
        case('w'):  _player.moveTo({x,--y});   break;              // Up
        case('e'):  _player.moveTo({++x,--y}); break;              // Up right
        case('a'):  _player.moveTo({--x,y});   break;              // Left
        case('s'):  break;                                                  // Stay
        case('d'):  _player.moveTo({++x,y});   break;              // Right
        case('z'):  _player.moveTo({--x,++y}); break;              // Down left
        case('x'):  _player.moveTo({x,++y});   break;              // Down
        case('c'):  _player.moveTo({++x,++y}); break;              // Down right
    }

    // New position

    char newPosChar = getNewPosChar(_player.getCoordinates());

    if (!outOfBounds(_player.getCoordinates())) {                         // Checks if the player is inside the maze bounds
        if (newPosChar == ' ' || newPosChar == 'H') {                                             // Danger free player movement
            return true;
        } else if (newPosChar == 'R' || newPosChar == '*') {                 // Kills the player if they move into a live robot or electric fence
            _player.kill();
            _player.setStatus('h');
            _player.moveTo(lastPos);
            return true;
        } else if ( newPosChar == 'O' ) {                                    // Player found the exit, therefore they win
            _player.setWin();
            return true;
        } else {                                                             // Invalid player move
            _player.moveTo(lastPos);
            return false;
        }
    } else {                                                                 // Invalid move (out of maze bounds)
        _player.moveTo(lastPos);
        return false;
    }
}


bool Game::outOfBounds(Point pos) {
    const unsigned int HEIGHT = _maze.getRows(), WIDTH = _maze.getColumns(); // Creating height and width variables by looking at the maze instance
    return !(0 <= pos.y && pos.y < HEIGHT && 0 <= pos.x && pos.x < WIDTH);   // Returning true (if inbounds) and false (if out of bounds)
}


char Game::getNewPosChar(const Point pos) {

    for (Post currPost : _maze.getAllList()) {                                // Iterating through all posts
        if ( currPost.getCoordinates() ==  pos) {        // Checking if the post has the same coordinates of the player (collision)
            return currPost.getSymbol();
        }
    }

    for (Robot currRobot : _robot) {                                           // Iterating through all robots
        if ( currRobot.getCoordinates() == pos) {        // Checking if the robot has the same coordinates of the player (collision)
            return currRobot.getStatus();
        }
    }

    if (_player.getCoordinates() == pos){
        return _player.getStatus();
    }

    return ' ';                                                               // The player didn't move into danger so they either stayed in place or moved to a free space
}

void Game::updateAllRobots() {

    for (int i = 0; i < _robot.size(); i++) {

        if (!_robot.at(i).isAlive()) {continue;};

        Point newPos = findBestMove(_robot.at(i));

        char charInPos = getNewPosChar(newPos);

        // std::cout << "newPos x: " << newPos.x << " newPos y: " << newPos.y << " currPos x: " << _robot.at(i).getCoordinates().x << " currPos y: " << _robot.at(i).getCoordinates().y << " charInPos: " << charInPos << std::endl;

        if (charInPos == 'R' || charInPos == 'r') {                 // Robot gets stuck
            _robot.at(i).kill();                                       // First robot dies
            _robot.at(i).setStatus('r');
            _robot.at(i).setState(Robot::STUCK);
            _robot.at(i).moveTo(newPos);                               // Coordinates update
            for (int j = 0; j < _robot.size(); j++) {
                if (_robot.at(i) == _robot.at(j)) { continue; };

                if (_robot.at(j).getCoordinates() == newPos) {           // If there's a robot collision, kills the other robot
                    _robot.at(j).kill();                                 // Second robot dies
                    _robot.at(i).setState(Robot::STUCK);
                    _robot.at(j).setStatus('r');
                }
            }

        } else if (charInPos == '*') {                               // Robot moves to electric fence
            _robot.at(i).kill();                                        // Robot dies
            _robot.at(i).setStatus('r');
            _robot.at(i).setState(Robot::DEAD);
        }else if (charInPos == '+') {
            _robot.at(i).kill();                                        // Robot dies
            _robot.at(i).setStatus('r');
            _robot.at(i).setState(Robot::STUCK);
        } else if (charInPos == 'H') {                              // Player gets caught by robot
            _player.kill();                                         // Player dies
            _player.setStatus('h');
            break;
        } else {                                                    // Regular robot move
            _robot.at(i).moveTo(newPos);                               // Updates robot position
        }
    }
}


Point Game::findBestMove(Robot& currRobot) {
    xval x = currRobot.getCoordinates().x;
    yval y = currRobot.getCoordinates().y;

    // Possible move positions for the Robot
    std::vector<Point> moveVec = {{x-1, y-1}, {x, y-1}, {x+1, y-1},
                                  {x-1, y},                  {x+1, y    },
                                  {x-1, y+1}, {x, y+1}, {x+1, y+1}};

    double minDist = std::numeric_limits<double>::max();
    Point bestMove;                                                                   // Variable to store the optimal position to move
    for (int i = 0; i < moveVec.size(); i++) {
        if (!outOfBounds(moveVec.at(i))) {                                            // The position is inside the maze bounds
            double dist = pointDist(moveVec.at(i), _player.getCoordinates());      // Distance between that move option and the player
            if (dist < minDist) {                                                     // If that move is the best until the moment
                minDist = dist;
                bestMove = moveVec.at(i);
            }
        }
    }
    return bestMove;
}

void Game::getPlayerName(Player &player){
    // Variable to leave the do-while loop (should be at 0 to leave)
    short leave = 1;
    do{
        std::string playerName;                                  // Initializes string to store the player username
        int nameLen = 0;                                    // The size of the name

        std::cout << "What's your name?" << std::endl;
        bool validInput = getInput(playerName);

        if (validInput) {                                   // Valid type
            clearBuffer();
            nameLen = playerName.length();

            if (0 < nameLen && nameLen <= 15) {             // Invalid name size
                player.setName(playerName);
                leave = 0;                                  // Leave the loop
            } else {
                warnUser("name");
            }
        } else if (!std::cin.eof()) {                            // Invalid type
            /**
             * Note: we need this condition for inputs like:
             * "ABCDEFGHJKLMNOPQRSTUV" where the name would exceed the 15
             * chars limit, but since only the string "ABCDEFGHJKLMNOP" would go to
             * the buffer, the scoreboard would be incorrectly updated
             */
            warnUser("name");
        }
    } while (!std::cin.eof() && leave != 0);
}

void Game::updateScoreboard() {
    // Initializing a ScoreBoard (vector<Player>) to track the players in the leaderboard
    ScoreBoard scoreboard;
    const std::string PREFIX = "../input/";                                          // Prefix for relative path file location
    const std::string fullPath = PREFIX + "MAZE_" + _maze.getName() + "_WINNERS.txt";    // Full path and filename

    getPlayerName(_player);
    if (!std::cin.eof()) {
        scoreboard.push_back(_player);  // Inserts the current game player in the scoreboard

        // Updates the scoreboard
        getScoreboard(fullPath, scoreboard, _player);

        clearScreen();
        std::cout << std::endl << "The scoreboard has been updated, " << _player.getName() << "! :)" << std::endl
             << "Press enter to continue to the menu ...";
        waitForConfirmation();
    }
}

void Game::getScoreboard(const std::string &fullPath, ScoreBoard scoreboard, const Player &player) {
    std::ifstream if_leaderBoard;                            // Initializing a stream for file input

    if_leaderBoard.open(fullPath.c_str());              // Opening the file

    if (if_leaderBoard.good()) {                        // File exists
        std::string str;

        // Skipping the lines for the header
        std::string line1, line2;
        getline(if_leaderBoard, line1);
        getline(if_leaderBoard, line2);

        parseLines(if_leaderBoard, scoreboard, player); // Parsing the previous scoreboard to `scoreboard`
        if_leaderBoard.close();                                // Closing the stream for file input

        std::ofstream of_leaderBoard;                               // Opening a stream for file output
        of_leaderBoard.open(fullPath.c_str());                 // Opening the file to write into

        // Writing the table header
        of_leaderBoard << "Player              - Time" << std::endl
                       << "--------------------------" << std::endl;

        int scoreboardSize = scoreboard.size();
        int counter = 1;
        // Sorting the scores in the scoreboard
        std::sort(scoreboard.begin(), scoreboard.end(), [](const Player p1, const Player p2) { return p1.getScore() < p2.getScore(); });


        for (auto player2 : scoreboard) {
            if (counter != scoreboardSize) {                // Not the end of the table
                of_leaderBoard << std::left << std::setw(20)  << player2.getName() << "- " << std::right << std::setw(4) << player2.getScore() << std::endl;
                counter++;
            } else {                                        // The end of the table
                of_leaderBoard << std::left << std::setw(20)  << player2.getName() << "- " << std::right << std::setw(4) << player2.getScore();
            }
        }

        of_leaderBoard.close();                             // Closing the file output stream
    } else {                    // File does not exist (creates one with the current player score)
        if_leaderBoard.close();
        std::ofstream of_leaderBoard;                        // Opening a stream for file output
        of_leaderBoard.open(fullPath);                       // Opening the file to write into

        Player player = scoreboard.at(0);

        // Writes the header of the leaderboard to the file
        of_leaderBoard << "Player              - Time" << std::endl
                       << "--------------------------" << std::endl
                       << std::left << std::setw(20)  << player.getName() << "- " << std::right << std::setw(4) << player.getScore();

        of_leaderBoard.close();
    }
}


void Game::parseLines(std::ifstream &leaderBoard, ScoreBoard &scoreBoard, const Player &player) {
    // This loop will happen  until the end of the file
    while (!leaderBoard.eof()) {
        std::string line;
        getline(leaderBoard, line);                             // Stores the current line of the iteration on `line`

        size_t lastDashPos = line.rfind('-');                       // Gets the index of the last '-' occurrence
        std::string strScore = line.substr(lastDashPos + 2);           // Parses the `score` from the line
        int score = stoi(strScore);                                    // Converts score into an integer

        std::string firstPart = line.substr(0, lastDashPos);           // Parses the string of the line until '-'
        size_t lastAlphaPos = getLastAlphaIdx(firstPart);          // Gets the index of the first char that is not ' '

        std::string name = firstPart.substr(0, lastAlphaPos + 1);   // Parses the `name` from the string

        // Creates a player instance being the`Player` instance only fields that are relevant to initialize `name` and `score`
        Player player2;
        player2.setName(name);
        player2.setScore(score);

        // Updating the scoreboard taking into account the best score registered for the current player
        if (name == player.getName() && score > player.getScore()) {                    // The player already exists and was faster
            continue;                                                         // The previous value (player2) is now slower so it isn't put on the scoreboard
        } else if (name != player.getName()){                                      // It is a different player
            scoreBoard.push_back(player2);
        } else {                                                              // The player already exists and was slower
            scoreBoard.erase(scoreBoard.begin());                             // Remove the player's score of the current run from the vector
            scoreBoard.push_back(player2);                                    // Append the current `player2` instance to the `scoreBoard`
        }
    }
}