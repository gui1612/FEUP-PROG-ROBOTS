#include "Maze.h"
#include "Post.h"

#include <algorithm>

void Maze::addPost(Post &post) {
    _AllList.push_back(post);               // Adding the post to a list which contains all posts
}


void Maze::clear() {
    /* Resetting some attributes of Maze */
    _name = "";
    _rows = 0, _columns = 0;
}


void Maze::replacePost(Post &post, const Point &pos) {
    for (int i = 0; i < _AllList.size(); i++) {
        if (_AllList.at(i).getCoordinates() == pos) _AllList.at(i) = post;
    }
}


void Maze::removePost(const Point &pos) {
    auto startIt = _AllList.begin();
    for (int i = 0; i < _AllList.size(); i++) {
        if (_AllList.at(i).getCoordinates() == pos) _AllList.erase(startIt + i);
    }
}
