cmake_minimum_required(VERSION 3.17)
project(FEUP_PROG_Proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(FEUP_PROG_Proj1 src/main.cpp src/global.cpp src/menu.cpp src/game.cpp includes/entities.h src/entities.cpp src/score.cpp includes/score.h includes/robot.cpp includes/robot.h includes/player.cpp includes/player.h includes/maze.cpp includes/maze.h)

include_directories(FEUP_PROG_Proj1 includes/)