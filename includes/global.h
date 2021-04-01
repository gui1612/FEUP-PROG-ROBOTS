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

#endif //MAIN_CPP_GLOBAL_H
