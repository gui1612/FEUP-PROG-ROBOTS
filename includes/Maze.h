#pragma once

// File includes
#include "Post.h"

// Lib includes
#include <vector>
#include <string>

// Type aliases
using PostVec = std::vector<Post>;

class Maze {
    /** @brief The dimensions of the maze (`rows`x`columns`) */
    int _rows, _columns;

    /** @brief The name of the maze currently being played (in format 'XX') */
    std::string _name;

    /** @brief A vector of the Points containing the x and y coordinates of the game exits */
    PostVec _allList;

public:

    /* @brief Default constructor for a Maze */
    Maze() : _allList(), _rows(0), _columns(0) {};

    /* 'Getter functions' */
    PostVec getAllList() const              { return _allList;          }
    int getRows() const                     { return _rows;             }
    int getColumns() const                  { return _columns;          }
    int getMazeArea() const                 { return _rows * _columns;  }
    std::string getName() const             { return _name;             }


    /* 'Setter functions' */
    void setRows(unsigned int rows)         { _rows = rows;             }
    void setCols(unsigned int cols)         { _columns = cols;          }
    void setName(std::string &name)         { _name = name;             }


    /* Member functions */

    /**
     * @brief Adds a Post instance to the Maze
     * @param post Instance of Post
     * @note When the post is added, it is automatically
     * checked if it is electrified ('*'), an exit ('O')
     * or a regular post ('+')
     */
    void addPost(Post& post);


    /**
     * @brief Removes a Post at a given position if it exists
     * @param pos Point where the post is
     */
    void removePost(const Point &pos);


    /**
     * @brief Replaces a Post at a given position if it exists by another given Post
     * @param post Instance of Post
     * @param pos Point where the post is
     */
    void replacePost(Post &post, const Point &pos);

    /** @brief Clears a Maze instance */
    void clear();
};