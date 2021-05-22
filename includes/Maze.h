//#ifndef FEUP_PROG_PROJ1_MAZE_H
//#define FEUP_PROG_PROJ1_MAZE_H
#pragma once

// Header includes
#include "Post.h"

// Includes
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

    unsigned int _rows, _columns;    /** @brief The dimensions of the maze (`rows`x`columns`) */

    std::string _name;

public:
    /* @brief Default constructor for a Maze */
    Maze() :  _PostLists(), _ExitList(), _AllList() {};

    /* 'Getter functions' */
    PostVec getPostsList() const            { return _PostLists;        };
    PostVec getExitsList() const            { return _ExitList;         };
    PostVec getAllList() const              { return _AllList;          };
    unsigned int getRows() const            { return _rows;             };
    unsigned int getColumns() const         { return _columns;          };
    unsigned int getMazeArea() const        { return _rows * _columns;  };
    std::string getName() const             { return _name;             };


    /* 'Setter functions' */
    void setRows(unsigned int rows)         { _rows = rows;             };
    void setCols(unsigned int cols)         { _columns = cols;          };
    void setName(std::string name)          { _name = name;             };

    /* Member functions */
    void addPost(Post& post);                       /// Changes the attribute `Posts` if the vector passes some sanity checks
    void clear();                                   /// Clears a Maze object

};


//#endif //FEUP_PROG_PROJ1_MAZE_H
