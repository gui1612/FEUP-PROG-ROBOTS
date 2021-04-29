/**
 * @file entities.h
 * @author Guilherme Almeida and António Santos
 */

// Includes
#include "menu.h"
#include "entities.h"

// Namespace
using namespace std;

int main() {
    try {
        srand(time(NULL));
        // Menu call, which will trigger the entire game
        menu();
    } catch(...) {  // If there is an eventual bug we haven't noticed, the user will be notified
        cerr << "An unexpected error has occurred!\n";
        EXIT_FAILURE;
    }
    return 0;
}