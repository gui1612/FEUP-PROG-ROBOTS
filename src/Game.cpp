#include "Game.h"
#include "globaldefs.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

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
            if (tolower(chr) == 'h'){                               // Player
                Player player(chr, {x, y});
                _player = player;
            } else if (tolower(chr) == 'r'){                        // Robot
                Robot robot(chr, {x, y}, id);
                _robot.push_back(robot);
                id++;
            } else if ( chr == '*' || chr == '+' || chr == 'O') {   // Fence / Exit
                std::cout <<  "x: " << x << " y: " << y << std::endl;
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
                        //updateAllRobots();
                        break;
                    } else if (_player.isAlive() && !_player.win()) {
                        std::cout << "TODO" << std::endl;
                        //updateAllRobots(player, maze);
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
    } while (!std::cin.eof() && !_player.isAlive());

    auto end = std::chrono::high_resolution_clock::now();                                  // Game timer ends
    drawMaze();

    std::chrono::duration<int> gameTime = std::chrono::duration_cast<std::chrono::duration<int>>(end - start);       // Calculates Game time

    if (_player.win()) {
        std::cout << win.at(RAND_IDX) << std::endl                                      // Prints a winning message
             << "Your time: " << gameTime.count() << "s" << std::endl;
        _player.setScore(gameTime.count());
       // updateScoreboard(player, maze);                                    // Updates the scoreboard for the current maze
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

    while (( (pos.x + 1) * (pos.y + 1)) <= mazeArea) {
        bool fillWithSpace = true;

        if (_player.getCoordinates() == pos) {
            if ((pos.x + 1) == _maze.getColumns()) {
                std::cout << _player.getStatus() << '\n';
                pos.y++; pos.x = 0;     // new line
            } else {
                std::cout << _player.getStatus() << std::flush;
                pos.x++;
            }
        }

        for (auto currPost : allPostList) {
            if (currPost.getCoordinates() == pos) {
                if ((pos.x + 1) == _maze.getColumns()) {
                    std::cout << currPost.getSymbol() << '\n';
                    pos.y++; pos.x = 0;     // new line
                } else {
                    std::cout << currPost.getSymbol() << std::flush;
                    pos.x++;
                }
                fillWithSpace = false;
                break;
            }
        }

        for (auto currRobot : _robot) {
            if (currRobot.getCoordinates() == pos) {
                if ((pos.x + 1) == _maze.getColumns()) {
                    std::cout << currRobot.getStatus() << '\n';
                    pos.y++; pos.x = 0;     // new line
                } else {
                    std::cout << currRobot.getStatus() << std::flush;
                    pos.x++;
                }
                fillWithSpace = false;
                break;
            }
        }

        if (fillWithSpace) {
            std::cout << " " << std::flush;
            pos.x++;
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

    char newPosChar = getNewPosChar();

    if (!outOfBounds()) {                                                    // Checks if the player is inside the maze bounds
        if (newPosChar == ' ' || newPosChar == 'H' || newPosChar == 'O') {   // Valid player movement
            return true;
        } else if (newPosChar == 'R' || newPosChar == '*') {                 // Kills the player if they move into a live robot or electric fence
            _player.kill();
            _player.setStatus('h');
            _player.moveTo(lastPos);
            return true;
        } else {                                      // Invalid player move
            _player.moveTo(lastPos);
            return false;
        }
    } else {                                                                 // Invalid move (out of maze bounds)
        _player.moveTo(lastPos);
        return false;
    }
}

bool Game::outOfBounds() {
    const unsigned int HEIGHT = _maze.getRows(), WIDTH = _maze.getColumns();
    Point pos = _player.getCoordinates();
    return !(0 <= pos.y && pos.y < HEIGHT && 0 <= pos.x && pos.x < WIDTH);
}

char Game::getNewPosChar() {
    for (Post currPost : _maze.getAllList()) {
        if ( currPost.getCoordinates() == _player.getCoordinates() ) {
            return currPost.getSymbol();
        }
    }

    for (Robot currRobot : _robot){
        if ( currRobot.getCoordinates() == _player.getCoordinates() ) {
            return currRobot.getStatus();
        }
    }

    return ' ';
}