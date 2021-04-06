cmake_minimum_required(VERSION 3.17)
project(FEUP_PROG_Proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(FEUP_PROG_Proj1 src/main.cpp src/maze.cpp includes/maze.h src/global.cpp includes/global.h src/menu.cpp includes/menu.h src/game.cpp includes/game.h src/player.cpp includes/player.h src/robot.cpp includes/robot.h)