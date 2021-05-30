// File includes
#include "Maze.h"
#include "Post.h"

// Lib includes
#include <algorithm>

void Maze::addPost(Post &post) {
    _allList.push_back(post);               // Adding the post to a list which contains all posts
}


void Maze::clear() {
    /* Resetting some attributes of Maze */
    _name = "";
    _rows = 0, _columns = 0;
}


void Maze::replacePost(Post &post, const Point &pos) {
    for (Post &currPost : _allList) {
        // Loop to replace the Post (if it exists) at position `pos` with `post`
        if (currPost.getCoordinates() == pos) currPost = post;
    }
}


void Maze::removePost(const Point &pos) {
    auto startIt = _allList.begin();                                            // Iterator to the starting point of the vector
    // Loop to remove the Post at position `pos` (if it exists)
    for (int i = 0; i < _allList.size(); i++) {
        if (_allList.at(i).getCoordinates() == pos) _allList.erase(startIt + i);
    }
}
