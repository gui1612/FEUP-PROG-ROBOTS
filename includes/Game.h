//#ifndef FEUP_PROG_PROJ1_GAME_H
//#define FEUP_PROG_PROJ1_GAME_H
#pragma once

#include "globaldefs.h"
#include "Robot.h"
#include "Player.h"
#include "Maze.h"

#include <vector>
#include <string>
#include <optional>

using gameBoard = std::vector<std::vector<char>>;

class Game {
    Player               _player;
    std::vector<Robot>   _robot;
    Maze                 _maze;
public:

    /** @brief Game constructor */
    Game(const std::string &filename);

    /** @brief Function that starts the game loop */
    void play();

private:

    /**
     * @brief Checks if the Move is a valid one
     *
     * @param key User input for the movement
     * @return Returns `true` if the move is valid, otherwise `false`
     *
     * @note This function does not check if the move is possible.
     * It only checks if the generic movement would be possible in
     * a generic situation.
     */
    bool validMove(char key);


    /**
     *
     */
    void drawMaze();

    bool updatePlayer(const char key);

    char getNewPosChar();

    bool outOfBounds();
};


//#endif //FEUP_PROG_PROJ1_GAME_H
