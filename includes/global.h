#pragma once

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
    } else {
        clearBuffer();
        return false;
    }
}


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