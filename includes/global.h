#pragma once
#ifndef MAIN_CPP_GLOBAL_H
#define MAIN_CPP_GLOBAL_H

#include <iostream>
#include <limits>

using namespace std;


/**
 * @brief Returns `true` if the input is valid and `false` if it isn't
 *
 * @return clears the input buffer and tracks if the input type is valid
 */
bool trackClearBuffer();


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
 * @brief Checks if the input is an is valid
 *
 * @return boolean value (`true` if the user has input the right type only to the buffer `false` in not)
 *
 * @code
 * int x;
 * cin >> x;    // User input: 1.23
 * bool validInput = validInputType();
 * @endcode
 * validInput would be `false`, since 1.23 is not an integer
 */
bool validInputType();

#endif //MAIN_CPP_GLOBAL_H
