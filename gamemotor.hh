// In Gamemotor-class is the logics of the game. This class controls
// things like where the pieces are and where and how they should move.

#ifndef GAMEMOTOR_HH
#define GAMEMOTOR_HH

#include <ctime>
#include <vector>
#include <cstdlib>
#include "tetris.hh"
#include "toplist.hh"

using namespace std;

class Gamemotor {
public:
	// Builder
	Gamemotor();

	// Destructor
	~Gamemotor();

	// The function that ends the game.
	void gameEnded(Toplist &toplist);

	// The function that begins the game.
	void beginGame();

	// Function, that randomizes a new block and places the pieces to
	// it's correct place.
	void newBlock();

	// Function, that returns the amount of the pieces.
	int returnAmountOfPieces();

	// Function, that returns the information of the chosen piece.
	Piece returnPiece(int number);

	// Function, that searches for full rows and removes them.
	void searchRows();

	// Function that lowers the pieces that player is moving by one.
	bool lowerPieces(Toplist &toplist);

	// Function that drops the pieces that player is moving as low as
	// possible.
	bool dropPieces(Toplist &toplist);

	// Function, that rotates the pieces that player is moving.
	bool rotatePieces();

	// Function that moves the pieces that player is moving horizontally.
	bool moveHorizontally(bool direction);

	// Function that examines if there already is pieces where the user
	// wants to move them or if the pieces would go outside the playing
	// area.
	bool canPiecesBePlaced(int locationX, int locationY);

	// Function that tells is the game started.
	bool isGameStarted();

	// Function that examines did the game end.
	bool didGameEnd();

	// Function that returns the score of the game.
	int returnScore();

	// Function that resets the score.
	void resetScore();

	// Function that returns the next piece.
	int returnNextPiece();

private:
	vector<Piece> pieces;
	Piece * movablePieces[4];
	int shapeOfMovablePieces;
	int stateOfMovablePieces;
	int score;
	bool gameStarted;
	int nextPiece;
};

#endif
