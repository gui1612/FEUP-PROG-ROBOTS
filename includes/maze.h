//
// Created by ANTONIO on 5/9/2021.
//

#ifndef FEUP_PROG_PROJ1_MAZE_H
#define FEUP_PROG_PROJ1_MAZE_H


class Maze {
    public:

        /**
         * @brief Displays a maze
         *
         * @param maze `Maze` type object
         */
        void drawMaze(const Maze &maze);


        /**
         * @brief Reads the user input for the selected maze and, if `true` is returned a Maze struct is passed by reference
         *
         * @param maze parameter to which the maze will be passed if the filename the user maze input is valid
         *
         * @return returns a boolean to track if the operation succeeded (`maze` is valid) or not (`maze` is invalid)
         *
         * @note If `false` is returned, the maze should not be considered, since it's a randomly started maze
         */
        bool mazePick(Maze &maze);


        /**
         * @brief Checks if a maze is valid
         *
         * @param filename file name without the relative path
         * @param fullPath string passed to store the name (with relative path) of the mazefile if it is valid
         * @param mazeFile `ifstream` to check if the file can be opened (exists or not)
         *
         * @return boolean to track if the maze is valid (true) or not (false)
         *
         * @note The maze must be in a parent directory called "mazes" (if it isn't PREFIX must
         * be changed in the 2nd line of the function)
         */
        bool validMaze(const short &filename, string &fullPath, ifstream &mazeFile);


        /**
         * @brief Replaces a char at a position in the maze
         *
         * @param maze the current maze of the game
         * @param point the point were the change will occur
         * @param replacingChar th char to replace in the map
         */
        void mazeReplace(Maze &maze, Point point, char replacingChar);


        /**
         * @brief Parses a txt file containing a maze file in the right format to a `Maze` struct
         *
         * @param levelPick maze filename (with its relative path)
         * @param mazeFile file input stream
         * @param valid tracks if the maze is valid
         *
         * @return returns a Maze struct
         */
        Maze mazeOpen(const string &levelPick, ifstream &mazeFile, bool &valid);

    private:

        /** @brief String containing the number of the current maze (ex.: '01', '02', ..., '99') */
        string number;

        /** @brief The dimensions of the maze (`rows`x`columns`) */
        unsigned int rows, columns;

        /**
         * @brief A 2D vector of dimensions `rows`x`columns` which contains the chars in the maze
         *
         * | Symbol | Description        |
         * |--------|--------------------|
         * | *      | Electric Fence     |
         * | D      | Non-electric fence |
         * | H      | Alive Human        |
         * | h      | Dead Human         |
         * | R      | Alive Robot        |
         * | r      | Dead Robot         |
         *
         * @note 'D' is internal notation. The user sees it as a normal fence ('*')
        */
        vector<vector<char>> gameBoard;

        /** @brief Vector which contains all the Robots in the maze sorted by their ID's */
        vector<Robot> robotVec;

        /** @brief Variable that tracks the number of alive Robots in the current game */
        int aliveRobots = 0;
};


/**
 * @brief Gets the maze format filename if the number is valid
 *
 * @param levelChoice int representing a level number
 * @return if the level number is valid  (0 < levelChoice < 100) returns the filename. If not, returns `std::nullopt`
 */
optional<string> getMazeName(short levelChoice);

#endif //FEUP_PROG_PROJ1_MAZE_H
