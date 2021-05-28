// File includes
#include "Game.h"
#include "Utils.h"
#include "constants.h"

// Lib includes
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <iomanip>



Game::Game(const std::string &filename) {

    std::ifstream mazeFile;
    mazeFile.open(filename);


    unsigned int rows = 0, id = 1, cols = 0, counter = 0;
    xval x = 0;
    yval y = 0;
    char sep;

    mazeFile >> rows;
    mazeFile >> sep;
    mazeFile >> cols;

    mazeFile.ignore(1000, '\n');

    std::string mazeName = filename.substr(5, 2);           // Parsing the maze number only

    _maze.setCols(cols);
    _maze.setRows(rows);
    _maze.setName(mazeName);

    unsigned int area = _maze.getMazeArea();

    while (!mazeFile.eof()) {
        char chr = mazeFile.get();
        if (x != cols) {                                            // Checks if the x coordinate is within the bounds of the maze
            counter++;                                              // Keeps track of the amount of characters of the maze
            switch(chr) {
                case PLAYER_DEAD_CHAR: case PLAYER_ALIVE_CHAR: {                                     // Player found
                    Player player(chr, {x, y});
                    _player = player;
                    x++; break; }
                case ROBOT_ALIVE_CHAR: {                                                              // Alive Robot found
                    Robot robot(chr, { x, y }, id, Robot::ALIVE);
                    _robot.push_back(robot);
                    id++; x++; break; }
                case ROBOT_DEAD_CHAR: {                                                               // Dead Robot found
                    Robot robot(chr, { x, y }, id, Robot::DEAD);
                    _robot.push_back(robot);
                    id++; break; }
                case ELECTRIC_POST_CHAR: case NON_ELECTRIC_POST_CHAR: case EXIT_POST_CHAR: {           // Post found
                    Post post({x, y}, chr);
                    _maze.addPost(post);
                    x++; break; }
                case ' ': x++; break;                                                                   // Space found
                default: throw std::runtime_error("Invalid mazefile: The file format is not correct!"); // Unknown char found
            }
        } else {                                                                            // New line
            x = 0;                                                                          // x coordinate is 0
            y++;                                                                            // Incrementing line number
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


    auto start = std::chrono::high_resolution_clock::now();         // Game timer starts
    do {
        char key;                                                   // Initialize the player's input variable

        drawMaze();
        std::cout << "Where do you wish to move to?" << std::endl;

        bool validInput = getInput<char>(key);                      // Checks if the input is valid for the type "char"
        clearScreen();

        if (validInput){                                            // Valid input
            if (validMove(key)) {                                   // Valid move
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

    auto end = std::chrono::high_resolution_clock::now();                          // Game timer ends
    drawMaze();

    std::chrono::duration<int> gameTime = std::chrono::duration_cast<std::chrono::duration<int>>(end - start);       // Calculates Game time

    if (_player.win()) {
        std::cout << win.at(RAND_IDX) << std::endl                                 // Prints a winning message
                  << "Your time: " << gameTime.count() << "s" << std::endl;
        _player.setScore(gameTime.count());
        updateScoreboard();                                                        // Updates the scoreboard for the current maze
    } else if (!std::cin.eof()) {
        std::cout << loss.at(RAND_IDX) << std::endl
                  << "Your time: " << gameTime.count() << "s" << std::endl;        // Displays the player game time
        waitForConfirmation();
    }
}


bool Game::validMove(const char key) const {
    std::vector<char> movements = {'q', 'w', 'e', 'a', 's', 'd', 'z', 'x', 'c'};
    // Checks if `key` is in `movements`
    return std::find(movements.begin(), movements.end(), static_cast<char>(tolower(key))) != movements.end();
}


void Game::drawMaze() const {
    Point pos{0, 0};
    PostVec allPostList = _maze.getAllList();
    const int MAZE_AREA = _maze.getMazeArea();

    while (((pos.x + 1) * (pos.y + 1)) <= MAZE_AREA) {                      // Looping from (0,0) to (cols, rows), while the area of the shape formed by pos and (0,0) isn't the area of the maze
        bool fillWithSpace = true;                                          // Flag keeping track if there aren't any robots/player/posts in coordinates pos


        auto robotIt = std::find_if(_robot.begin(), _robot.end(), [&](const Robot &x) {
            return x.getCoordinates() == pos;
        });

        if (robotIt != _robot.end()) {                                      // The Robot is in pos
            char symbol = robotIt->getStatus();                             // Character of the Robot
            if ((pos.x + 1) == _maze.getColumns()) {                        // Checking it isn't the last character of the row
                std::cout << symbol << std::endl;                           // Drawing Robot
                pos.y++; pos.x = 0;                                         // Moving to next row
            } else {
                std::cout << symbol << BLANK_CHAR << std::flush;            // Drawing Robot
                pos.x++;                                                    // Moving to next column
            }
            fillWithSpace = false;
        }

        auto postIt = std::find_if(allPostList.begin(), allPostList.end(), [&](const Post &x) {
            return x.getCoordinates() == pos;
        });

        if (postIt != allPostList.end()) {                                  // The Post is in pos
            char symbol = postIt->getSymbol();                              // Character of the Post
            if ((pos.x + 1) == _maze.getColumns()) {                        // Checking it isn't the last character of the row
                std::cout << symbol << std::endl;                                // Drawing Post
                pos.y++; pos.x = 0;                                         // Moving to next row
            } else {
                std::cout << symbol << BLANK_CHAR << std::flush;            // Drawing Post
                pos.x++;                                                    // Moving to next column
            }
            fillWithSpace = false;
        }

        if (_player.getCoordinates() == pos) {                                     // The player is in pos
            if ((pos.x + 1) == _maze.getColumns()) {                               // Checking it isn't the last character of the row
                std::cout << _player.getStatus() << std::endl;                     // Drawing player
                pos.y++; pos.x = 0;                                                // Moving to next row
            } else {
                std::cout << _player.getStatus() << BLANK_CHAR << std::flush;      // Drawing Player
                pos.x++;                                                           // Moving to next column
            }
            fillWithSpace = false;
        }

        if (fillWithSpace) {
            if ((pos.x + 1) == _maze.getColumns()) {                        // Checking it isn't the last character of the row
                std::cout << BLANK_CHAR << std::endl;                       // Drawing a space
                pos.y++; pos.x = 0;                                         // Moving to next row
            } else {
                std::cout << BLANK_CHAR << BLANK_CHAR << std::flush;        // Drawing two spaces (Note: We're using 2 spaces instead of one for playability)
                pos.x++;                                                    // Moving to next column
            }
        }
    }
    std::cout << std::endl;
}


bool Game::updatePlayer(const char key) {
    // Player position before the movement
    Point lastPos = _player.getCoordinates();
    xval x = lastPos.x;
    yval y = lastPos.y;
    PostVec allPostList = _maze.getAllList();

    switch (static_cast<char>(tolower(key))) {
        case('q'):  _player.moveTo({--x,--y}); break;              // Up left
        case('w'):  _player.moveTo({x,--y});   break;              // Up
        case('e'):  _player.moveTo({++x,--y}); break;              // Up right
        case('a'):  _player.moveTo({--x,y});   break;              // Left
        case('s'):                             break;              // Stay
        case('d'):  _player.moveTo({++x,y});   break;              // Right
        case('z'):  _player.moveTo({--x,++y}); break;              // Down left
        case('x'):  _player.moveTo({x,++y});   break;              // Down
        case('c'):  _player.moveTo({++x,++y}); break;              // Down right
    }

    // New position

    if (!outOfBounds(_player.getCoordinates())) {                   // Checks if the player is inside the maze bounds

        auto robotIt = std::find_if(_robot.begin(), _robot.end(), [&](const Robot& x) {
            return x.getCoordinates() == _player.getCoordinates();
            });

        if (robotIt != _robot.end()) {
            if (robotIt->isAlive()) {                               // Player moved into an alive Robot
                _player.kill();
                _player.moveTo(lastPos);
                return true;
            } else {                                                // Player moved into a dead Robot (invalid move)
                _player.moveTo(lastPos);
                return false;
            }
        }

        auto postIt = std::find_if(allPostList.begin(), allPostList.end(), [&](const Post& x) {
            return x.getCoordinates() == _player.getCoordinates();
            });

        if (postIt != allPostList.end()) {
            if (postIt->isElectrified()) {                          // Player moved into an electrified Post
                _player.kill();
                _player.moveTo(lastPos);
                return true;
            } else if (postIt->isExit()) {                          // Player found the Exit
                _player.setWin();
                return true;
            } else {                                                // Player moved a non-electrified Post (invalid move)
                _player.moveTo(lastPos);
                return false;
            }
        }
        return true;                                                // Danger free player movement
    } else {
        _player.moveTo(lastPos);
        return false;
    }
}


bool Game::outOfBounds(const Point &pos) const {
    const int LOWER_BOUND = 0;
    const int HEIGHT = _maze.getRows(), WIDTH = _maze.getColumns(); // Creating height and width variables by looking at the maze instance
    return !(LOWER_BOUND <= pos.y &&  pos.y < HEIGHT && LOWER_BOUND <=  pos.x &&  pos.x < WIDTH);   // Returning true (if inbounds) and false (if out of bounds)
}


char Game::getNewPosChar(const Point &pos) const {

    for (const Post &currPost : _maze.getAllList()) {    // Iterating through all posts
        if ( currPost.getCoordinates() == pos) {         // Checking if the post has the same coordinates of the player (collision)
            return currPost.getSymbol();
        }
    }

    for (const Robot &currRobot : _robot) {              // Iterating through all robots
        if (currRobot.getCoordinates() == pos) {         // Checking if the robot has the same coordinates of the player (collision)
            return currRobot.getStatus();
        }
    }

    if (_player.getCoordinates() == pos) {
        return _player.getStatus();
    }

    return ' ';                                          // The player didn't move into danger so they either stayed in place or moved to a free space
}


void Game::updateAllRobots() {
    PostVec allPostList = _maze.getAllList();

    for (size_t i = 0; i < _robot.size(); i++) {

        if (!_robot.at(i).isAlive()) continue;                          // If the Robot is not alive he won't move

        Point newPos = findBestMove(_robot.at(i));                      // Stores the ideal position to where the Robot should move

        auto robotIt = std::find_if(_robot.begin(), _robot.end(), [&](const Robot& x) {
            return x.getCoordinates() == newPos;
            });

        if (robotIt != _robot.end()) {
            _robot.at(i).kill();
            _robot.at(i).setState(Robot::STUCK);
            _robot.at(i).moveTo(newPos);
            robotIt->kill();
            robotIt->setState(Robot::STUCK);
            continue;            
        }

        auto postIt = std::find_if(allPostList.begin(), allPostList.end(), [&](const Post& x) {
            return x.getCoordinates() == newPos;
            });

        if (postIt != allPostList.end()) {
            if (postIt->isElectrified()) {
                _robot.at(i).kill();
                _robot.at(i).setState(Robot::DEAD);
                continue;
            } else {
                _robot.at(i).kill();
                _robot.at(i).setState(Robot::STUCK);
                continue;
            }
        }

        if (_player.getCoordinates() == newPos) {
            _player.kill();
            continue;
        }

        _robot.at(i).moveTo(newPos);
    }
}

Point Game::findBestMove(const Robot &currRobot) const {
    xval x = currRobot.getCoordinates().x;
    yval y = currRobot.getCoordinates().y;

    // Possible move positions for the Robot
    std::vector<Point> moveVec = {{x-1, y-1}, {x, y-1}, {x+1, y-1},
                                  {x-1, y},                    {x+1,  y    },
                                  {x-1, y+1}, {x, y+1}, {x+1, y+1}};

    double minDist = std::numeric_limits<double>::max();
    Point bestMove = {0, 0};                                             // Variable to store the optimal position to move
    for  (Point move : moveVec) {
        if (!outOfBounds(move)) {                                        // The position is inside the maze bounds
            double dist = pointDist(move, _player.getCoordinates());     // Distance between that move option and the player
            if (dist < minDist) {                                        // If that move is the best until the moment
                minDist = dist;
                bestMove = move;
            }
        }
    }
    return bestMove;
}


void Game::updateScoreboard() {
    // Initializing a ScoreBoard (vector<Player>) to track the players in the leaderboard
    ScoreBoard scoreboard;
    const std::string PREFIX ;                                                           // Prefix for relative path file location
    const std::string fullPath = PREFIX + "MAZE_" + _maze.getName() + "_WINNERS.txt";    // Full path and filename

    _player.getPlayerName();
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


void Game::getScoreboard(const std::string &fullPath, ScoreBoard &scoreboard, const Player &player) {
    std::ifstream if_leaderBoard;                       // Initializing a stream for file input

    if_leaderBoard.open(fullPath.c_str());              // Opening the file

    if (if_leaderBoard.good()) {                        // File exists
        std::string str;

        // Skipping the lines for the header
        std::string line1, line2;
        getline(if_leaderBoard, line1);
        getline(if_leaderBoard, line2);

        parseLines(if_leaderBoard, scoreboard, player);        // Parsing the previous scoreboard to `scoreboard`
        if_leaderBoard.close();                                // Closing the stream for file input

        std::ofstream of_leaderBoard;                          // Opening a stream for file output
        of_leaderBoard.open(fullPath.c_str());                 // Opening the file to write into

        // Writing the table header
        of_leaderBoard << "Player              - Time" << std::endl
                       << "--------------------------" << std::endl;
        
        int scoreboardSize = scoreboard.size();
        int counter = 1;
        // Sorting the scores in the scoreboard
        std::sort(scoreboard.begin(), scoreboard.end(), [](const Player &p1, const Player &p2) { return p1.getScore() < p2.getScore(); });


        for (const Player &player2 : scoreboard) {
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
        getline(leaderBoard, line);                                 // Stores the current line of the iteration on `line`

        size_t lastDashPos = line.rfind('-');                       // Gets the index of the last '-' occurrence
        std::string strScore = line.substr(lastDashPos + 2);        // Parses the `score` from the line
        unsigned int score = stoi(strScore);                        // Converts score into an integer

        std::string firstPart = line.substr(0, lastDashPos);        // Parses the string of the line until '-'
        size_t lastAlphaPos = getLastAlphaIdx(firstPart);           // Gets the index of the first char that is not ' '

        std::string name = firstPart.substr(0, lastAlphaPos + 1);   // Parses the `name` from the string

        // Creates a player instance being the`Player` instance only fields that are relevant to initialize `name` and `score`
        Player player2;
        player2.setName(name);
        player2.setScore(score);

        // Updating the scoreboard taking into account the best score registered for the current player
        if (name == player.getName() && score > player.getScore()) {          // The player already exists and was faster
            continue;                                                         // The previous value (player2) is now slower so it isn't put on the scoreboard
        } else if (name != player.getName()){                                 // It is a different player
            scoreBoard.push_back(player2);
        } else {                                                              // The player already exists and was slower
            scoreBoard.erase(scoreBoard.begin());                             // Remove the player's score of the current run from the vector
            scoreBoard.push_back(player2);                                    // Append the current `player2` instance to the `scoreBoard`
        }
    }
}