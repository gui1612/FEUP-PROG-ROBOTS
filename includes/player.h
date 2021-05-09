//
// Created by ANTONIO on 5/9/2021.
//

#ifndef FEUP_PROG_PROJ1_PLAYER_H
#define FEUP_PROG_PROJ1_PLAYER_H


class Player {
    public:

        /**
         * @brief Updates the status of the player (position and alive/dead), checking if there are any issues with the movement
         *
         * @param player the player that will have its status updated
         * @param chat the input of the user, read in order to control the movement of the player entity
         * @param maze the maze, used to check if there is anything in the way of the player that will alter its status
         *
         * @return returns true if the player's movements align with the game's rules and false otherwise
         */
        bool updatePlayer(Player &player, char key, Maze &maze);


        /**
        * @brief Draws the player's new position, clearing the previous one
        *
        * @param player Player instance
        * @param maze the maze of the current game
        * @param lastPos the previous position of the player
        */
        void playerDraw(Point lastPos, const Player &player, Maze &maze);

        /**
        * @brief Checks if the player is trying to move to a position out of bounds
        *
        * @param pos Position the player is trying to move
        * @param maze Maze instance
        * @return returns `true` if out of bounds, `false` if not
        */
        bool outOfBounds(const Point &pos, const Maze &maze);

    private:

        /** The name of the player playing the game */
        string name;

        /** Score of the current player */
        int score;

        /** @brief `true` if the player is alive, otherwise `false` */
        bool alive;

        /** @brief Coordinates of the player in the `Maze` */
        Point coordinates;

};


#endif //FEUP_PROG_PROJ1_PLAYER_H
