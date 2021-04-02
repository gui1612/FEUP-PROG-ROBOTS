#include "inp_out.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void mazePick(){

    string levelPick;   // string type var to store the number of the selected maze

    cout << "Choose a level to play (00 to return to main menu)! " << std::endl;
    cin >> levelPick;

    // TODO: overall needs refining
    if (levelPick == "00") {
        // TODO: connect with main menu
        std::cout << "Back to the main menu here." << std::endl;
    }else {
        mazeOpen(levelPick);
    }
}

void mazeOpen(string levelPick){

    ifstream levelFile;    // input type var to open and read from
    string level, width, height;          // string type var to store the content of levelFile
    int i=1;

    // TODO: method used to chose the user's level seems finicky and ignoring the first line is done in a weird way
    levelFile.open("../mazes/MAZE_" + levelPick + ".txt", ios::in);
    if (levelFile.is_open()) {
        while (!levelFile.eof()) {
            getline (levelFile, level);
            if (i==1) {
                for (int j = 0; j <= level.length()-1; j++){
                    if (level[j] == ' ' && i==1){
                        height = level.substr(0,j);
                        i++;
                    } else if (level[j] == ' ' && i==2){
                        width = level.substr(j+1, level.length()-1);
                    }
                }
            }else {
                cout << level << endl;
            }
        }
        cout << height << " " << width << endl;
    }else {
        // TODO: make the user able to retry the input (loop)
        cout << "That maze doesn't exist!" << endl;
    }
    levelFile.close();
}