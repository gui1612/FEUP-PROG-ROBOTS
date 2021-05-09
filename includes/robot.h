//
// Created by ANTONIO on 5/9/2021.
//

#ifndef FEUP_PROG_PROJ1_ROBOT_H
#define FEUP_PROG_PROJ1_ROBOT_H

using ID = unsigned int;

class Robot {
    public:
        /**
         * @brief Updates the status of all the robots (position and alive/dead) and their side effects
         * (positions on the maze, if they collide with the player, etc.)
         *
         * @param player Player instance
         * @param maze
         */
        void updateAllRobots(Player &player, Maze &maze);

        /**
        * @brief Calculates the best move for the Robot
        *
        * @param robot robot instance
        * @param player player instance
        * @param maze maze instance
        *
        * @return returns the Point to where the ideal move would be
        *
        * @note This algorithm calculates the best move based on distance only
        */
        Point bestMove(const Robot &robot, const Player &player, const Maze &maze);

    private:
        /** @brief `true` if the robot is alive, otherwise `false` */
        bool alive;

        /** @brief ID of the robot (unique for each robot) */
        ID id;

        /** @brief Coordinates of the robot in the `Maze` */
        Point coordinates;
};


/** @overload
 *
 * @param r1 Robot instance
 * @param r2 Robot instance
 *
 * @return `true` if the robots are the same, otherwise `false`
 */
inline bool operator==(Robot r1, Robot r2) {
    // Since ID's are unique, we only need to compare them to know if the robot is the same
    return r1.id == r2.id;
}


/**
 * @brief Calculates the distance between 2 points
 *
 * @param p1 first point
 * @param p2 second point
 *
 * @return distance between `p1` and `p2`
 */
double pointDist(Point p1, Point p2);

#endif //FEUP_PROG_PROJ1_ROBOT_H
