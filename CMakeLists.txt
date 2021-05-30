cmake_minimum_required(VERSION 3.17)
project(FEUP_PROG_ROBOTS)

set(CMAKE_CXX_STANDARD 17)

add_executable(FEUP_PROG_ROBOTS src/main.cpp src/Entity.cpp includes/Entity.h src/Game.cpp includes/Game.h src/Maze.cpp includes/Maze.h includes/constants.h src/Utils.cpp includes/Utils.h src/Robot.cpp includes/Robot.h src/Menu.cpp includes/Menu.h src/Player.cpp includes/Player.h src/Post.cpp includes/Post.h)

include_directories(FEUP_PROG_ROBOTS includes/)