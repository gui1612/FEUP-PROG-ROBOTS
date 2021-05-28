#pragma once

// File includes
#include "Utils.h"
#include "Robot.h"
#include "Player.h"
#include "Maze.h"

// Lib includes
#include <vector>
#include <string>
#include <optional>

using ScoreBoard = std::vector<Player>;

class Game {
    Player               _player;               /// Instance of Player representing the current Player
    std::vector<Robot>   _robot;                /// Vector that contains all the robots in the Maze
    Maze                 _maze;                 /// Maze instance that is currently being played
public:

    /** @brief Game constructor */
    explicit Game(const std::string &filename);

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
    bool validMove(char key) const;


    /**
     * @brief Displays a maze
     *
     * @param maze `Maze` type object
     */
    void drawMaze() const;


    /**
     * @brief Updates the status of the player (position and alive/dead), checking if there are any issues with the movement
     *
     * @param key the input of the user, read in order to control the movement of the player entity
     *
     * @return returns true if the player's movements align with the game's rules and false otherwise
     */
    bool updatePlayer(char key);


    /**
    * @brief Returns the character present at position `pos`
    *
    * @param pos The position to be checked
    * @return The char present at `pos`
    */
    //char getNewPosChar(const Point &pos) const;


    /**
     * @brief Checks if the player is trying to move to a position out of bounds
     *
     * @param pos Point of coordinates {x, y}
     * @return `true` if the Point is inside the maze's bounds, otherwise `false`
     */
    bool outOfBounds(const Point &pos) const;


    /**
     * @brief Updates the status of all the robots (position and alive/dead) and their side effects
     * (positions on the maze, if they collide with the player, etc.)
     */
    void updateAllRobots();


    /**
     * @brief Calculates the best move for the Robot
     *
     * @param robot Robot instance
     *
     * @return returns the Point to where the ideal move would be
     *
     * @note This algorithm calculates the best move based on distance only
     */
    Point findBestMove(const Robot &currRobot) const;


    /** @brief Function to ask for the username and update the scoreboard */
    void updateScoreboard();


    /**
     * @brief Fully updates the scoreboard with the new playerName
     *
     * @param fullPath  full relative filepath
     * @param scoreboard `ScoreBoard` instance
     * @param player the `Player` instance of the current game
     */
    void getScoreboard(const std::string &fullPath, ScoreBoard &scoreboard, const Player &player);


    /*
     * @brief Parses the current leaderboard file to a `scoreBoard` instance
     *
     * @param leaderBoard file stream for input
     * @param scoreBoard type alias to vector<Player>
     * @param player `Player` instance to check if the current player username already exists in the previous table
     *
     * @note If the current player username exists, always checks sticks to the new score (even if it's lower) for integrity purposes
     */
    void parseLines(std::ifstream &leaderBoard, ScoreBoard &scoreBoard, const Player &player);


};