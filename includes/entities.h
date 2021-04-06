#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <vector>

using namespace std;

// Type aliases
using xval = int;
using yval = int;
using ID = int;


///////// STRUCTS ///////////

/**
 * @brief Data structure to store a Point (pair of coordinates x, y)
 *
 */
struct Point {int x; int y;};


/**
 * @brief Data structure to store a maze file (stores the number of rows, columns and the char for each position of the maze)
 *
 */
struct Maze {
    unsigned int rows;                  ///< The number of rows of the maze
    unsigned int columns;               ///< The number of columns of the maze
    vector<vector<char>> coordinates;   ///< A 2D vector  of dimensions `rows`x`columns` which contains the char in the maze for each individual position
};


/**
 * @brief Data structure to store a Person (stores his position, score and his position)
 *
 */
struct Robot {
    bool alive;
    ID id;
    vector<int> coordinates;
};


/**
 * @brief Data structure to store a Person (stores his position, score and his position)
 *
 */
struct Player {
   bool alive;
   int score;
   vector<int> coordinates;
};


/**
* @brief Starts a game based on the maze passed
*
* @param maze Maze instance
*/
struct Game {
    Maze maze;
    Player player;
    Robot robot;
};

///////// MAZE ///////////


/**
 * @brief Displays a maze
 *
 * @param maze `Maze` type object
 */
void drawMaze(const Maze &maze);


//void updateMaze(Maze &maze, Robot &robot, Player &player, char key, vector robotIDS);


/**
 * @brief Reads the user input for the selected maze and, if `true` is returned a Maze struct is passed by reference
 *
 * @param maze parameter to which the maze will be passed if the filename the user maze input is valid
 *
 * @return returns a boolean to track if the operation succeeded (`maze` is valid) or not (`maze` is invalid)
 *
 * @note If `false` is returned, the maze should not be considered, since it's a randomly started maze
 */
bool mazePick(Maze &maze);


/**
 * @brief Gets the maze format filename if the number is valid
 *
 * @param levelChoice int representing a level number
 * @return if the level number is valid  (0 < levelChoice < 100) returns the filename. If not, returns `std::nullopt`
 */
optional<string> getMazeName(short levelChoice);


/**
 * @brief Checks if a maze is valid
 *
 * @param filename file name without the relative path
 * @param fullPath string passed to store the name (with relative path) of the mazefile if it is valid
 * @param mazeFile `ifstream` to check if the file can be opened (exists or not)
 *
 * @return boolean to track if the maze is valid (true) or not (false)
 *
 * @note The maze must be in a parent directory called "mazes" (if it isn't PREFIX must
 * be changed in the 2nd line of the function)
 */
bool validMaze(const short &filename, string &fullPath, ifstream &mazeFile);


/**
 * @brief Parses a txt file containing a maze file in the right format to a `Maze` struct
 *
 * @param levelPick maze filename (with its relative path)
 * @param mazeFile file input stream
 *
 * @return returns a Maze struct
 */
Maze mazeOpen(const string &levelPick, ifstream &mazeFile);

///////// ROBOT ///////////


/**
 * @brief Updates the status of the robot (position and alive/dead)
 *
 * @param robot the robot that will have its status updated
 * @param player the player, needs their position, so that the robot is able to update its own position (according to the shortest path rule)
 * @param maze the maze, used to check if there is anything in the way of the robot that will alter its status
 *
 */
void updateRobot(Robot &robot, const Player &player, const Maze &maze);


///////// PLAYER ///////////

/**
 * @brief Updates the status of the player (position and alive/dead)
 *
 * @param player the player that will have its status updated
 * @param chat the input of the user, read in order to control the movement of the player entity
 * @param maze the maze, used to check if there is anything in the way of the player that will alter its status
 *
 */
void updatePlayer(Player &player, char key, Maze &maze);

/**
 * @brief stub
 *
 * @param player the player
 * @param maze the maze
 * @param lastPos the previous position of the player
 *
 */
void playerDraw(Point lastPos, Player player, Maze &maze);