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
 * @brief Overload of "==" for point equality
 *
 * @param p1 Point instance
 * @param p2 Point instance
 * @return `true` if the points are the same, otherwise `false`
 */
inline bool operator==(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}


/**
 * @brief Data structure to store a Person (stores his position, score and his position)
 *
 */
struct Robot {
    // `true` if the robot is alive, otherwise `false`
    bool alive;

    // The ID of the robot (unique for each robot)
    ID id;

    // The current coordinates of the robot in the `Maze`
    Point coordinates;
};

/**
 * @brief Overload of operator "==" for Robot equality
 *
 * @param r1 Robot instance
 * @param r2 Robot instance
 *
 * @return `true` if the robots are the same, otherwise `false`
 */
inline bool operator==(Robot r1, Robot r2) {
    // Since ID's are unique, we only need to compare them to know if the robot is the same
    return r1.id == r2.id;
}

/**
 * @brief Data structure to store a Person (stores his position, score, name and position)
 *
 */
struct Player {
   // The name of the player playing the game
   string name;

   // The score of the current player
   int score;

   // `true` if the player is alive, otherwise `false`
   bool alive;

   // The current coordinates of the player in the `Maze`
   Point coordinates;
};


///////// MAZE ///////////


/**
 * @brief Data structure that contains all the info about the maze
 *
 */
struct Maze {
    // A string containing the number of the current maze (ex.: '01', '02', ..., '99')
    string number;

    // The dimensions of the maze (`rows`x`columns`)
    unsigned int rows, columns;

    /*
     * A 2D vector of dimensions `rows`x`columns` which contains the chars in the maze
     *
     * ** MAZE NOTATION **
     * '*' -> Electric fence
     * 'D' -> Non-electric fence (Note: This is game internal notation. The player sees both 'D' and '*' as a normal '*')
     * 'H' -> Alive Human
     * 'h' -> Dead Human
     * 'R' -> Alive Robot
     * 'r' -> Dead Robot
     */
    vector<vector<char>> gameBoard;

    // Vector which contains all the Robots in the maze sorted by their ID's
    vector<Robot> robotVec;

    // Variable that tracks the number of alive Robots in the current game
    int aliveRobots = 0;
};


/**
 * @brief Displays a maze
 *
 * @param maze `Maze` type object
 */
void drawMaze(const Maze &maze);


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
 * @param player Player instance
 * @param maze
 */
void updateAllRobots(Player &player, Maze &maze);


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
 * @brief Draws the robot's new position, clearing the previous one
 *
 * @param robot Robot instance
 * @param maze the maze of the current game
 * @param lastPos the previous position of the robot
 *
 */
void robotDraw(Point lastPos, const Robot &robot, Maze &maze);


/**
 * @brief Calculates the distance between 2 points
 *
 * @param p1 first point
 * @param p2 second point
 *
 * @return distance between `p1` and `p2`
 */
double pointDist(Point p1, Point p2);


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
 * @brief Draws the player's new position, clearing the previous one
 *
 * @param player Player instance
 * @param maze the maze of the current game
 * @param lastPos the previous position of the player
 */
void playerDraw(Point lastPos, const Player &player, Maze &maze);


/**
 * @brief Checks if the player is trying to move to a position out of bounds
 *
 * @param pos Position the player is trying to move
 * @param maze Maze instance
 * @return returns `true` if out of bounds, `false` if not
 */
bool outOfBounds(const Point &pos, const Maze &maze);