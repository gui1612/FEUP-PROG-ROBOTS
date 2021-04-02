#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <optional>


using namespace std;

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