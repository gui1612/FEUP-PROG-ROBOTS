#pragma once


// File Includes
#include "Utils.h"

// Lib Includes
#include <iostream>
#include <string>
#include <optional>


/** @brief Base menu caller function */
void menu();


/**
 * @brief Takes the necessary course of action depending on the user input `choice`
 *
 * @param choice value that represents the user menu choice
 * @param confirm tracks if the user really wants to leave the game
 */
void menuChoice(short choice, short &confirm);


/**
 * @brief Reads the user input for the selected maze and, if the input is valid, returns the correspondent filepath
 *
 * @return returns a string with the filepath to open/process the selected maze
 */
std::optional<std::string> mazePick();


/**
 * @brief Checks if a maze is valid
 *
 * @param filename file name without the relative path
 * @param fullPath string passed to store the name (with relative path) of the mazefile if it is valid
 * @param mazeFile `ifstream` to check if the file can be opened (exists or not)
 *
 * @return boolean to track if the maze is valid (true)
 *
 * @note The maze must be in a parent directory called "mazes" (if it isn't PREFIX must
 * be changed in the 2nd line of the function)
 */
bool validMaze(const short &filename, std::string &fullPath, std::ifstream &mazeFile);


/** 
 * @brief Asks the user for input and displays a leaderboard if it exists 
 */
void displayLeaderboard();


/**
 * @brief Converts the input given prior to a std::string checking if it is valid (]0, 100[)
 *
 * @param levelChoice int representing a level number
 * @return if the level number is valid  (0 < levelChoice < 100) returns the filename. If not, returns `std::nullopt`
 */
std::optional<std::string> getMazeName(short levelChoice);


/**
 * @brief Creates a decorative display showing all available mazes, regardless of validity
 * 
 * @param availableMazes Vector of the available maze names
 */
void displayAvailableMazes();


/**
 * @brief Reads a file
 *
 * @param filename The name of the file to be read
 * @return Returns true if the file opening was successful, false otherwise
 *
 * @notes Relative pathing is not supported
 */
void readFile(const std::string &filename);


/**
 * @brief Calculates the existing mazes and passes them in `mazeVec`

 * @param mazeVec Vector containing the names of the existing mazes
 * @return Passes a vector containing the existing mazenames

 * @note This function doesn't check the integrity of the mazes themselves
 * For more on that check `Game`
 */
void getExistingMazes(std::vector<std::string> &mazeVec);