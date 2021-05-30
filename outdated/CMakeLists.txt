cmake_minimum_required(VERSION 3.17)
project(FEUP_PROG_Proj1)

set(CMAKE_CXX_STANDARD 17)

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ~/)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/gui1612/git/FEUP-PROG-Proj1)
add_executable(FEUP_PROG_Proj1 main.cpp Post.cpp Post.h Maze.cpp Maze.h Player.cpp Player.h Robot.cpp Robot.h Game.cpp Game.h Utils.cpp Utils.h Entity.cpp Entity.h Menu.cpp Menu.h constants.h)