// Class toplist where things related to toplist are executed.

#ifndef TOPLIST_HH
#define TOPLIST_HH

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Toplist {
public:
	// Builder
	Toplist();

	// Destructor
	~Toplist();

	// Function that initializes the toplist from it's file.
	void initList();

	// Function that adds score to list if it is good enough.
	void addScore(int score);

	// Function that returns toplist.
	void returnToplist(string &first, string &second, string &third);

	// Function that transforms int to string.
	string intToString(int number);

private:
	int bestScores[3];
};

#endif
