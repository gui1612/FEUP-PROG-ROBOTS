#pragma once

// Includes
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

// Namespace
using namespace std;


/**
 * @brief Clears the buffer
 *
 */
void clearBuffer();


/**
 * @brief Clears the console screen
 *
 */
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
    if (cin >> firstInp && cin.peek() == '\n') {
        inp = firstInp;
        return true;
    } else if (!cin.eof()) {    // If the input is invalid (with the exception of EOF) returns a flag for invalid input without clearing the buffer
        clearBuffer();
        return false;
    } else {                    // If the input is EOF, returns a flag for invalid input without clearing the buffer
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
void warnUser(const string &warningType);


/**
 * @brief Sleeps for the given amount of seconds
 *
 * @param sec sleep time in seconds
 */
void sleepFor(unsigned int sec);