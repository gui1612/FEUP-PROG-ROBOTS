#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <vector>

// Type aliases
using xval = int;
using yval = int;


using namespace std;

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
 * @brief Parses a txt file containing a maze file in the right format to a `Maze` struct
 *
 * @param levelPick maze filename (with its relative path)
 * @param mazeFile file input stream
 *
 * @return returns a Maze struct
 */
Maze mazeOpen(const string &levelPick, ifstream &mazeFile);
