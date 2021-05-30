// T06_G06
/**
 * @author Guilherme Almeida (up202006137)
 * @author António Santos (up202008004)
 *
 * @copyright Copyright (c) 2021
 */


// File Includes
#include "Utils.h"
#include "Menu.h"

int main() {
    // Random seed initialization
    srand(static_cast<unsigned int>(time(nullptr)));
    try {
        // Menu call, which will trigger the entire game
        menu();
    } catch(...) {  // If there is an eventual bug we haven't noticed, the user will be notified
        std::cout << "An unexpected error has occurred!\n";
        EXIT_FAILURE;
    }
    return 0;
}