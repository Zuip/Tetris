#include "toplist.hh"

// Builder
Toplist::Toplist() {
	bestScores[0] = 0;
	bestScores[1] = 0;
	bestScores[2] = 0;
}

// Destructor
Toplist::~Toplist() { }

// Function that initializes the toplist from file. If the file isn't
// found, this function creates it.
void Toplist::initList() {

	// Filestreams that are needed in this function
	ifstream filestreamIn;
	ofstream filestreamOut;

	// Boolean that has the information if the file exists.
	bool fileExists = true;

	// Researches if the file already exists.
	filestreamIn.open("toplist.txt", ios::in);
	if(!filestreamIn) {
		fileExists = false;
	}
	filestreamIn.close();

	// If the toplist file doesn't exist, we'll create it.
	if(fileExists == false) {
		filestreamOut.open("toplist.txt", ios::out);
		filestreamOut << "0 0 0";
		filestreamOut.close();
	}

	// Read toplist from file.
	filestreamIn.open("toplist.txt", ios::in);
	filestreamIn >> bestScores[0] >> bestScores[1] >> bestScores[2];
	filestreamIn.close();

}

// Function that adds score to list if it is good enough.
void Toplist::addScore(int score) {

	// Boolean that has the information if the toplist changed.
	bool didListChange = false;

	// Filestream output that is needed in this function.
	ofstream filestream;

	// If toplist changed, add information to didListChange -variable.
	if(score > bestScores[2]) {
		didListChange = true;
	}
	
	// If score is good enough, put it to it's place in toplist.
	if(score > bestScores[0]) {
		bestScores[2] = bestScores[1];
		bestScores[1] = bestScores[0];
		bestScores[0] = score;
	} else if(score > bestScores[1]) {
		bestScores[2] = bestScores[1];
		bestScores[1] = score;
	} else if(score > bestScores[2]) {
		bestScores[2] = score;
	}

	// Create string that is inputted in file
	string spaceString = " ";
	string inputString = intToString(bestScores[0]) + spaceString
		+ intToString(bestScores[1]) + spaceString
		+ intToString(bestScores[2]);

	// If list changed, update toplist file
	if(didListChange == true) {
		filestream.open("toplist.txt");
		filestream << inputString;
		filestream.close();
	}

}

// Function that returns the toplist.
void Toplist::returnToplist(string &first, string &second,
		string &third) {

	first = intToString(bestScores[0]);
	second = intToString(bestScores[1]);
	third = intToString(bestScores[2]);
}

// Function that transformers int to string.
string Toplist::intToString(int number) {
	stringstream intToStringStream;
	string transformedString;

	intToStringStream << number;
	intToStringStream >> transformedString;

	return transformedString;
}
