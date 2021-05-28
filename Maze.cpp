#include "Maze.h"
#include "Post.h"

void Maze::addPost(const Post &post) {
    _AllList.push_back(post);               // Adding the post to a list which contains all posts

    if (post.isExit()) {                                               // Exit
        _ExitList.push_back(post);
    } else if(post.isElectrified() || post.isNotElectrified()) {        // Eletrified or non-eletrified Post
        _PostLists.push_back(post);
    }
}


void Maze::clear() {
    /* Resetting some attributes of Maze */
    _PostLists.clear();
    _ExitList.clear();
    _name = "";
    _rows = 0, _columns = 0;
}