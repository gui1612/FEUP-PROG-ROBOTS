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
 * @brief Gets the maze format filename if the number is valid
 *
 * @param levelChoice int representing a level number
 * @return if the level number is valid  (0 < levelChoice < 100) returns the filename. If not, returns `std::nullopt`
 */
optional<string> getMazeName(short levelChoice);


/**
 * @brief reads the user input for the selected maze
 *
 */
void mazePick();


/**
 * @brief opens the MAZE_XX.txt file based on user input provided in mazePick();
 *
 */
void mazeOpen(string levelPick);