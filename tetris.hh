// This file includes Levels and Piece -structs, which are important in many
// parts of the program.
// initializeLevels function is also introduced in this file. 

#ifndef TETRIS_HH
#define TETRIS_HH

#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// This struct has the information of how fast the pieces drops in which
// level and in what level player is currently.
struct Levels {
	float level[20];
	int levelNow;
};

// In this struct is information about where one piece is and what is it's
// color.
struct Piece{
	int color;
	int locationX;
	int locationY;
};

// Function that sets the speed of levels.
void setLevels(Levels &levels);

#endif
