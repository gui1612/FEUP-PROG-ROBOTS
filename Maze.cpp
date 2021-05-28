#include "Maze.h"
#include "Post.h"

void Maze::addPost(Post &post) {
    AllList.push_back(post);               // Adding the post to a list which contains all posts
}


void Maze::clear() {
    /* Resetting some attributes of Maze */
    _name = "";
    _rows = 0, _columns = 0;
}