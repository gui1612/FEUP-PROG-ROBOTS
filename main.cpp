// File Includes
#include "Utils.h"
#include "Menu.h"

int main() {
    try {
        srand(time(nullptr));
        // Menu call, which will trigger the entire game
        menu();
    } catch(...) {  // If there is an eventual bug we haven't noticed, the user will be notified
        std::cerr << "An unexpected error has occurred!\n";
        EXIT_FAILURE;
    }
    return 0;
}