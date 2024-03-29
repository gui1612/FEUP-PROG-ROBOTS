#include "Post.h"
#include "constants.h"


bool Post::isElectrified() const {
    return _symbol == ELECTRIC_POST_CHAR;
}


bool Post::isExit() const {
    return _symbol == EXIT_POST_CHAR;
}


bool Post::isNotElectrified() const {
    return _symbol == NON_ELECTRIC_POST_CHAR;
}