#include "menu.h"

#include <time.h>

using namespace std;

int main() {
   srand(time(nullptr));
    menu();
    /*
    try {
        // Menu call, which will trigger the entire game

    } catch(...) {  // If there is an eventual bug we haven't noticed, the user will be notified
        cerr << "An unexpected error has occurred!\n";
        EXIT_FAILURE;
    }
    */
    return 0;
}