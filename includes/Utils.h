#pragma once

// File includes
#include "Utils.h"

// Lib includes
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <vector>


// Type aliases
using xval = int;
using yval = int;
using ID = unsigned int;


/** @brief Data structure to store a Point (pair of coordinates x, y) */
struct Point {int x; int y;};


/** @overload
 * @param p1 Point instance
 * @param p2 Point instance
 *
 * @return `true` if the points are the same, otherwise `false`
 */
inline bool operator==(const Point &p1, const Point &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}


/**
 * @brief Clears the buffer
 *
 */
void clearBuffer();


/** @brief Clears the console screen */
void clearScreen();


/**
 * @brief Waits for any user input while also clearing the garbage in the buffer (if there is any)
 *
 */
void waitForConfirmation();


/**
 * @brief Reads value of any type from the keyboard and writes it to `inp` if the input is correct
 *
 * @param inp variable to where the input will be written if the input is correct
 * @return `true` if the input is correct (the type is right) else `false`
 */
template<typename T>
bool getInput(T &inp) {
    T firstInp;
    if (std::cin >> firstInp && std::cin.peek() == '\n') {
        inp = firstInp;
        return true;
    } else if (!std::cin.eof()) {       // If the input is invalid (with the exception of EOF) returns a flag for invalid input without clearing the buffer
        clearBuffer();
        return false;
    } else {                            // If the input is EOF, returns a flag for invalid input without clearing the buffer
        return false;
    }
}


/**
 * @brief Warns the user about bad input in a single frame (Note: Safe to use, since it clears the screen and buffer before and after its call)
 *
 * @param warningType string to define the warning type
 *
 * @details
 * `fileIO`     -> IO warning;
 * `menu`       -> Menu warning;
 * `game`       -> Game warning;
 * `game-move`  -> Movement warning;
 * `name`       -> Name length warning;
 * `leaderboard`-> Leaderboard warning;
 *  `mazeFile`  -> Warning layout for the mazefile.
 */
void warnUser(const std::string &warningType);


/**
 * @brief Sleeps for the given amount of seconds
 *
 * @param sec sleep time in seconds
 */
void sleepFor(unsigned int sec);


/**
 * @brief Calculates the distance between 2 points
 *
 * @param p1 first point
 * @param p2 second point
 *
 * @return distance between `p1` and `p2`
 */
double pointDist(const Point &p1, const Point &p2);


/**
 * @brief Gets the index of the last character that is not a space ()
 *
 * @param str the string to check
 *
 * @return returns the index of the last "non-space character"
 */
size_t getLastAlphaIdx(const std::string &str);


 /**
  * @brief Checks if `filename` exists under `path` directory
  * @param filename The name of the file
  * @param path The relative path of the file location
  * @return `true` if the file exists, otherwise `false`
  */
bool fileExists(const std::string &filename, const std::string &path = "");


/**
 * @brief Gets the number of lines in a file
 * @param fileName the name of the file
 * @return number of lines in `fileName`
 */
int getLinesNumber(const std::string &fileName);