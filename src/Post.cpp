#include "Post.h"


bool Post::isElectrified() const {
    return _symbol == '*';
};


bool Post::isExit() const {
    return _symbol == 'O';
};


void Post::deactivatePost() {
    setSymbol('+');
}
