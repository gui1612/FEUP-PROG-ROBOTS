#include "../includes/global.h"

using namespace std;

bool trackClearBuffer() {
    bool result = cin.good();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return result;
}


void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}