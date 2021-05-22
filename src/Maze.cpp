#include "Maze.h"
#include "Post.h"

void Maze::addPost(Post &post) {
    _AllList.push_back(post);           // Adding the post to the list of all posts

    if (post.getSymbol() == 'O') {
        _ExitList.push_back(post);
    } else if (post.getSymbol() == '*') {
        _PostLists.push_back(post);
    }
}


void Maze::clear() {
    _PostLists.clear();
    _ExitList.clear();
    _name = "";
    _rows = 0, _columns = 0;
}