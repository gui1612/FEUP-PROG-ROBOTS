cmake_minimum_required(VERSION 3.17)
project(FEUP_PROG_Proj1)

set(CMAKE_CXX_STANDARD 17)

#add_executable(FEUP_PROG_Proj1 src.o/main2.cpp src.o/global.cpp src.o/menu.cpp src.o/game.cpp includes/entities.h src.o/entities.cpp src.o/score.cpp includes/score.h )
add_executable(FEUP_PROG_Proj1 src/main.cpp src/Post.cpp includes/Post.h src/Maze.cpp includes/Maze.h src/Player.cpp includes/Player.h src/Robot.cpp includes/Robot.h src/Game.cpp includes/Game.h src/globaldefs.cpp includes/globaldefs.h src/Entity.cpp includes/Entity.h src/Menu.cpp includes/Menu.h)

include_directories(FEUP_PROG_Proj1 includes/)