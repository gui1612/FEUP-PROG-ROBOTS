#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <vector>
#include <cmath>
#include <climits>
#include <map>
#include <unordered_map>

using namespace std;

// Type aliases
using xval = int;
using yval = int;
using ID = unsigned int;


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
    string number;                      ///< The number of the maze (string format)
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
    Point coordinates;
};


using RobotMap = unordered_map<ID, Robot>;


/**
 * @brief Data structure to store a Person (stores his position, score, name and position)
 *
 */
struct Player {
   string name;
   int score;
   bool alive;
   Point coordinates;
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


/**
 * @brief Updates all the maze (The player and the robot)
 *
 * @param robotMap Unordered map with <key, value> pairs of Ids and Robots
 * @param player `Player` instance
 * @param maze the current `maze` state
 * @param chr `char` containing the user movement input
 */
void updateMaze(RobotMap &robotMap, Player &player, Maze &maze, char chr);


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
 * @brief Replaces a char at a position in the maze
 *
 * @param maze the current maze of the game
 * @param point the point were the change will occur
 * @param replacingChar th char to replace in the map
 */
void mazeReplace(Maze &maze, Point point, char replacingChar);


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
 * @brief Updates the status of all the robots (position and alive/dead) and their side effects
 * (positions on the maze, if they collide with the player, etc.)
 *
 * @param robotMap Unordered map with <key, value> pairs of Ids and Robots
 * @param robot Robot instance
 * @param player Player instance
 * @param maze
 */
void updateAllRobot(RobotMap &robotMap, Player &player, Maze &maze);


/**
 * @brief Updates the status of the robot and its position in the maze
 *
 * @param robot the robot that will have its status updated
 * @param player player instance to calculate the shortest path and be updated if
 * @param maze the maze where the `chars` representing `player` and `robot` will be updated
 *
 */
void updateRobot(Robot &robot,Player &player, Maze &maze);


/**
 * @brief Calculates the best move for the Robot
 *
 * @param robot robot instance
 * @param player player instance
 * @param maze maze instance
 *
 * @return returns the Point to where the ideal move would be
 *
 * @note This algorithm calculates the best move based on distance only
 */
Point bestMove(const Robot &robot, const Player &player, const Maze &maze);

/**
 * @brief Gets the robot adress from its `id` or `nullptr` if it is not valid
 *
 * @param id
 * @param robotMap
 *
 * @return `id` or `nullptr` if it is not valid
 */
/*
Robot* getById(ID id, RobotMap &robotMap);
*/
///////// PLAYER ///////////


/**
 * @brief Updates the status of the player (position and alive/dead), checking if there are any issues with the movement
 *
 * @param player the player that will have its status updated
 * @param chat the input of the user, read in order to control the movement of the player entity
 * @param maze the maze, used to check if there is anything in the way of the player that will alter its status
 *
 * @return returns true if the player's movements align with the game's rules and false otherwise
 */
bool updatePlayer(Player &player, char key, Maze &maze);


/**
 * @brief stub
 *
 * @param player the player
 * @param maze the maze
 * @param lastPos the previous position of the player
 *
 */
void playerDraw(Point lastPos, const Player &player, Maze &maze);


/**
 * @brief Calculates the distance between 2 points
 *
 * @param p1 first point
 * @param p2 second point
 *
 * @return distance between `p1` and `p2`
 */
double pointDist(Point p1, Point p2);


/**
 * @brief Checks if the player is trying to move to a position out of bounds
 *
 * @param pos Position the player is trying to move
 * @param maze Maze instance
 * @return returns `true` if out of bounds, `false` if not
 */
bool outOfBounds(const Point &pos, const Maze &maze);