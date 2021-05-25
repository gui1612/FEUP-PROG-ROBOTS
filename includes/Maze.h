#pragma once

// File includes
#include "Post.h"

// Lib includes
#include <vector>
#include <string>

// Type aliases
using PostVec = std::vector<Post>;

class Maze {

    /** @brief A vector of the Posts containing the x and y coordinates of the non exit posts */
    PostVec _PostLists;

    /** @brief A vector of the Points containing the x and y coordinates of the game exits */
    PostVec _AllList;

    /** @brief A vector of the Points containing the x and y coordinates of the game exits */
    PostVec _ExitList;

    /** @brief The dimensions of the maze (`rows`x`columns`) */
    unsigned int _rows, _columns;

    /** @brief The name of the maze currently being played (in format 'XX') */
    std::string _name;

public:
    /* @brief Default constructor for a Maze */
    Maze() :  _PostLists(), _ExitList(), _AllList(), _rows(0), _columns(0) {};

    /* 'Getter functions' */
    PostVec getPostsList() const            { return _PostLists;        }
    PostVec getExitsList() const            { return _ExitList;         }
    PostVec getAllList() const              { return _AllList;          }
    unsigned int getRows() const            { return _rows;             }
    unsigned int getColumns() const         { return _columns;          }
    unsigned int getMazeArea() const        { return _rows * _columns;  }
    std::string getName() const             { return _name;             }


    /* 'Setter functions' */
    void setRows(unsigned int rows)         { _rows = rows;             }
    void setCols(unsigned int cols)         { _columns = cols;          }
    void setName(std::string name)          { _name = name;             }

    /* Member functions */

    /**
     * @brief Adds a Post instance to the Maze
     * @note When the post is added, it is automatically
     * checked if it is eletrified ('*'), an exit ('O')
     * or a regular post ('+')
     */
    void addPost(Post& post);

    /** @brief Clears a Maze instance */
    void clear();
};