#include "Post.h"


bool Post::isElectrified() const {
    return _symbol == '*';
}


bool Post::isExit() const {
    return _symbol == 'O';
}


bool Post::isNotEletrified() const {
    return _symbol == '+';
}


void Post::deactivatePost() {
    setSymbol('+');
}
