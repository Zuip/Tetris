#include "gamemotor.hh"
#include "graphics.hh"

#include <iostream>

// Builder
Gamemotor::Gamemotor() {
	// Set game to not started
	gameStarted = false;

	// Randomize a new piece
	srand(time(NULL));
	nextPiece = rand() % 7;
	newBlock();

	// Set score to zero
	score = 0;
}

// Destructor
Gamemotor::~Gamemotor() {
	while(pieces.size() > 0) {
		pieces.pop_back();
	}
}

// This function is executed if game ends.
void Gamemotor::gameEnded(Toplist &toplist) {
	gameStarted = false;
	toplist.addScore(score);
	while(pieces.size() > 0) {
		pieces.pop_back();
	}
}

// Begins a new game
void Gamemotor::beginGame() {
	gameStarted = true;
}

// Function where new piece is chosen by random and set to it's place.
void Gamemotor::newBlock() {

	// Set new piece as movable piece and choose a new random piece.
	shapeOfMovablePieces = nextPiece;
	srand(time(NULL));
	nextPiece = (nextPiece + rand()) % 7;

	// Set rotation state of piece.
	stateOfMovablePieces = 0;

	// Piece where information of piece is located temporarily.
	Piece helpPiece;
	helpPiece.color = shapeOfMovablePieces;

	// Set pieces' location to it's place by what block was chosen.
	if(shapeOfMovablePieces == 0) { // Block 0 is triangle
		helpPiece.locationX = 4;
		helpPiece.locationY = 0;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 5;
		helpPiece.locationY = 1;
		pieces.push_back(helpPiece);
	} else if(shapeOfMovablePieces == 1) { // Block 1 is square
		helpPiece.locationY = 0;
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
		helpPiece.locationY = 1;
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
	} else if(shapeOfMovablePieces == 2) { // Block 2 is straight
		helpPiece.locationY = 0;
		for(int a = 0; a < 4; ++a) {
			helpPiece.locationX = 3 + a;
			pieces.push_back(helpPiece);
		}
	} else if(shapeOfMovablePieces == 3) { // Block 3 is L
		helpPiece.locationY = 0;
		helpPiece.locationX = 4;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
		helpPiece.locationY = 1;
		helpPiece.locationX = 4;
		pieces.push_back(helpPiece);
	} else if(shapeOfMovablePieces == 4) { // Block 4 is mirrowed L
		helpPiece.locationY = 0;
		helpPiece.locationX = 4;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
		helpPiece.locationY = 1;
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
	} else if(shapeOfMovablePieces == 5) { // Block 5 is S
		helpPiece.locationY = 0;
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
		helpPiece.locationY = 1;
		helpPiece.locationX = 4;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
	} else if(shapeOfMovablePieces == 6) { // Block 6 is mirrowed S
		helpPiece.locationY = 0;
		helpPiece.locationX = 4;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationY = 1;
		helpPiece.locationX = 5;
		pieces.push_back(helpPiece);
		helpPiece.locationX = 6;
		pieces.push_back(helpPiece);
	}

	// Activate movable pieces.
	for(int a = 0; a < 4; ++a) {
		movablePieces[a] = &pieces.at(pieces.size() - 4 + a);
	}
}

// Returns the amount of pieces in the screen.
int Gamemotor::returnAmountOfPieces() {
	return pieces.size();
}

// Returns information of the chosen piece
Piece Gamemotor::returnPiece(int number) {
	return pieces.at(number);
}

// Searches for full rows and removes them if found.
void Gamemotor::searchRows() {
	int rows = 0;
	int piecesInRow = 0;
	int a = 0;

	// Examine all 24 rows one by one.
	while(a < 24) {

		// Examine all 10 pieces in row.
		piecesInRow = 0;
		for(int b = 0; b < 10; ++b) {

			// Examine all pieces in pieces-vector.
			for(int c = 0; c < pieces.size(); ++c) {

				// If the piece that is being examined
				// is in examined row, add one to
				// piecesInRow-variable.
				if(pieces.at(c).locationY == a
						&& pieces.at(c).locationX
						== b) {

					++piecesInRow;
				}
			}
		}

		// If there is 10 pieces in a row, remove row.
		if(piecesInRow >= 10) {
			++rows;
			for(int b = 0; b < pieces.size(); ++b) {
				if(pieces.at(b).locationY == a) {
					pieces.erase(pieces.begin() + b);
					b = -1;
				}
			}
			for(int b = 0; b < pieces.size(); ++b) {
				if(pieces.at(b).locationY < a) {
					++pieces.at(b).locationY;
				}
			}
			a = 0;
		} else {
			++a;
		}
	}

	// Add points to score by how many rows was removed.
	if(rows == 1) {
		score += 1;
	} else if(rows == 2) {
		score += 3;
	} else if(rows == 3) {
		score += 6;
	} else if(rows == 4) {
		score += 10;
	}
}

// Lowers moving pieces by one
bool Gamemotor::lowerPieces(Toplist &toplist) {

	// Test pieces which are used for testing if pieces can be lowered.
	Piece testPieces[4];
	for(int a = 0; a < 4; ++a) {
		testPieces[a].color = movablePieces[a]->color;
		testPieces[a].locationX = movablePieces[a]->locationX;
		testPieces[a].locationY = movablePieces[a]->locationY;
	}

	// Lower test pieces
	for(int a = 0; a < 4; ++a) {
		++testPieces[a].locationY;
	}

	// Examine if pieces can be lowered.
	for(int a = 0; a < 4; ++a) {
		if(canPiecesBePlaced(testPieces[a].locationX,
				testPieces[a].locationY) == false) {

			// Examine if there is any full rows
			searchRows();

			// If pieces are too high, end the game.
			if(didGameEnd() == true) {
				gameEnded(toplist);
			}

			// Create new block.
			newBlock();
			return false;
		}
	}

	// If pieces can be lowered, lower them.
	for(int a = 0; a < 4; ++a) {
		movablePieces[a]->color = testPieces[a].color;
		movablePieces[a]->locationX = testPieces[a].locationX;
		movablePieces[a]->locationY = testPieces[a].locationY;
	}

	return true;
}

// Lowers the pieces which are being handled.
bool Gamemotor::dropPieces(Toplist &toplist) {
	while(lowerPieces(toplist) != false) { }
}

// Rotate the block.
bool Gamemotor::rotatePieces() {

	// Create test pieces that helps to determine if block can be rotated.
	Piece testPieces[4];
	for(int a = 0; a < 4; ++a) {
		testPieces[a].color = movablePieces[a]->color;
		testPieces[a].locationX = movablePieces[a]->locationX;
		testPieces[a].locationY = movablePieces[a]->locationY;
	}

	// Help piece, that is needed for rotating the piece.
	Piece helpPiece;

	// Rotate triangle-shaped block.
	if(shapeOfMovablePieces == 0) {
		if(stateOfMovablePieces == 0) {
			testPieces[0].locationX += 1;
			testPieces[0].locationY -= 1;
			canPiecesBePlaced(testPieces[0].locationX,
				testPieces[0].locationY);
			if(testPieces[0].locationY < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationY;
				}
			}
		} 
		if(stateOfMovablePieces == 1) {
			testPieces[3].locationX -= 1;
			testPieces[3].locationY -= 1;
			if(testPieces[3].locationX < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationX;
				}
			}
		}
		if(stateOfMovablePieces == 2) {
			testPieces[2].locationX -= 1;
			testPieces[2].locationY += 1;
		}
		if(stateOfMovablePieces == 3) {
			testPieces[0].locationX += 1;
			testPieces[0].locationY += 1;
			if(testPieces[0].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					--testPieces[a].locationX;
				}
			}
			helpPiece = testPieces[0];
			testPieces[0] = testPieces[3];
			testPieces[3] = testPieces[2];
			testPieces[2] = helpPiece;
		}
	}

	// Rotate square-shaped block.
	if(shapeOfMovablePieces == 1) {
		return true;
	}

	// Rotate straight block.
	if(shapeOfMovablePieces == 2) {
		if(stateOfMovablePieces == 0) {
			testPieces[0].locationX += 1;
			testPieces[0].locationY -= 1;
			testPieces[2].locationX -= 1;
			testPieces[2].locationY += 1;
			testPieces[3].locationX -= 2;
			testPieces[3].locationY += 2;
			if(testPieces[0].locationY < 0) {
				for(int a = 0; a < 4; ++a) {
					testPieces[a].locationY += 1;
				}
			}
		}
		if(stateOfMovablePieces == 1) {
			testPieces[0].locationX -= 1;
			testPieces[0].locationY += 1;
			testPieces[2].locationX += 1;
			testPieces[2].locationY -= 1;
			testPieces[3].locationX += 2;
			testPieces[3].locationY -= 2;
			if(testPieces[0].locationX < 0) {
				for(int a = 0; a < 4; ++a) {
					testPieces[a].locationX += 1;
				}
			}
			if(testPieces[2].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					testPieces[a].locationX -= 2;
				}
			}
			if(testPieces[3].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					testPieces[a].locationX -= 1;
				}
			}
		}
	}

	// Rotate L-shaped block
	if(shapeOfMovablePieces == 3) {
		if(stateOfMovablePieces == 0) {
			testPieces[0].locationX += 1;
			testPieces[0].locationY += 1;
			testPieces[2].locationX -= 1;
			testPieces[2].locationY -= 1;
			testPieces[3].locationX += 2;
			if(testPieces[2].locationY < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationY;
				}
			}
		}
		if(stateOfMovablePieces == 1) {
			testPieces[0].locationX += 1;
			testPieces[0].locationY -= 1;
			testPieces[2].locationX -= 1;
			testPieces[2].locationY += 1;
			testPieces[3].locationY -= 2;
			if(testPieces[0].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					--testPieces[a].locationX;
				}
			}
			if(testPieces[2].locationX < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationX;
				}
			}
		}
		if(stateOfMovablePieces == 2) {
			testPieces[0].locationX -= 1;
			testPieces[0].locationY -= 1;
			testPieces[2].locationX += 1;
			testPieces[2].locationY += 1;
			testPieces[3].locationX -= 2;
		}
		if(stateOfMovablePieces == 3) {
			testPieces[0].locationX -= 1;
			testPieces[0].locationY += 1;
			testPieces[2].locationX += 1;
			testPieces[2].locationY -= 1;
			testPieces[3].locationY += 2;
			if(testPieces[0].locationX < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationX;
				}
			}
			if(testPieces[2].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					--testPieces[a].locationX;
				}
			}
		}
	}

	// Rotate mirrowed L-shaped block
	if(shapeOfMovablePieces == 4) {
		if(stateOfMovablePieces == 0) {
			testPieces[0].locationX += 1;
			testPieces[0].locationY += 1;
			testPieces[2].locationX -= 1;
			testPieces[2].locationY -= 1;
			testPieces[3].locationY -= 2;
			if(testPieces[2].locationY < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationY;
				}
			}
		}
		if(stateOfMovablePieces == 1) {
			testPieces[0].locationX += 1;
			testPieces[0].locationY -= 1;
			testPieces[2].locationX -= 1;
			testPieces[2].locationY += 1;
			testPieces[3].locationX -= 2;
			if(testPieces[0].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					--testPieces[a].locationX;
				}
			}
			if(testPieces[2].locationX < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationX;
				}
			}
		}
		if(stateOfMovablePieces == 2) {
			testPieces[0].locationX -= 1;
			testPieces[0].locationY -= 1;
			testPieces[2].locationX += 1;
			testPieces[2].locationY += 1;
			testPieces[3].locationY += 2;
		}
		if(stateOfMovablePieces == 3) {
			testPieces[0].locationX -= 1;
			testPieces[0].locationY += 1;
			testPieces[2].locationX += 1;
			testPieces[2].locationY -= 1;
			testPieces[3].locationX += 2;
			if(testPieces[0].locationX < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationX;
				}
			}
			if(testPieces[2].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					--testPieces[a].locationX;
				}
			}
		}
	}

	// Rotate S-shaped block.
	if(shapeOfMovablePieces == 5) {
		if(stateOfMovablePieces == 0) {
			testPieces[2].locationY -= 2;
			testPieces[1].locationX -= 2;
			if(testPieces[2].locationY < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationY;
				}
			}
			if(testPieces[1].locationX < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationX;
				}
			}
		}
		if(stateOfMovablePieces == 1) {
			testPieces[2].locationY += 2;
			testPieces[1].locationX += 2;
			if(testPieces[1].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					--testPieces[a].locationX;
				}
			}
		}
	}

	// Rotate mirrowed S-shaped block.
	if(shapeOfMovablePieces == 6) {
		if(stateOfMovablePieces == 0) {
			testPieces[2].locationY -= 2;
			testPieces[3].locationX -= 2;
			if(testPieces[2].locationY < 0) {
				for(int a = 0; a < 4; ++a) {
					++testPieces[a].locationY;
				}
			}
		}
		if(stateOfMovablePieces == 1) {
			testPieces[2].locationY += 2;
			testPieces[3].locationX += 2;
			if(testPieces[3].locationX > 9) {
				for(int a = 0; a < 4; ++a) {
					--testPieces[a].locationX;
				}
			}
		}
	}

	// Examine if block can be placed.
	if(canPiecesBePlaced(testPieces[0].locationX,
			testPieces[0].locationY) == false ||
			canPiecesBePlaced(testPieces[1].locationX,
			testPieces[1].locationY) == false ||
			canPiecesBePlaced(testPieces[2].locationX,
			testPieces[2].locationY) == false ||
			canPiecesBePlaced(testPieces[3].locationX,
			testPieces[2].locationY) == false) {
		return false;
	}

	// Place testpieces to vector.
	for(int a = 0; a < 4; ++a) {
		movablePieces[a]->locationX
			= testPieces[a].locationX;
		movablePieces[a]->locationY
			= testPieces[a].locationY;
	}

	// Change state of movable piece to next.
	stateOfMovablePieces += 1;
	if(stateOfMovablePieces == 4) {
		stateOfMovablePieces = 0;
	}
	if(stateOfMovablePieces == 2 && (shapeOfMovablePieces == 2
			|| shapeOfMovablePieces == 5
			|| shapeOfMovablePieces == 6)) {
		stateOfMovablePieces = 0;
	}
}

// Move pieces horizontally.
bool Gamemotor::moveHorizontally(bool direction) {

	// Create test pieces that are used to determine if pieces can be moved.
	Piece testPieces[4];
	for(int a = 0; a < 4; ++a) {
		testPieces[a].color = movablePieces[a]->color;
		testPieces[a].locationX = movablePieces[a]->locationX;
		testPieces[a].locationY = movablePieces[a]->locationY;
	}

	// Move test pieces horizontally to wanted direction and examine if
	// pieces go out of the game area.
	for(int a = 0; a < 4; ++a) {
		if(direction == false) {
			--testPieces[a].locationX;
		}
		if(direction == true) {
			++testPieces[a].locationX;
		}
		if(testPieces[a].locationX < 0
				|| testPieces[a].locationX > 9) {

			return false;
		}
	}

	// Check if there is any other pieces on the way.
	for(int a = 0; a < 4; ++a) {
		if(canPiecesBePlaced(testPieces[a].locationX,
				testPieces[a].locationY) == false) {
			return false;
		}
	}

	// If pieces can be placed, place them.
	for(int a = 0; a < 4; ++a) {
		movablePieces[a]->color = testPieces[a].color;
		movablePieces[a]->locationX = testPieces[a].locationX;
		movablePieces[a]->locationY = testPieces[a].locationY;
	}

	return true;
}

// Function that examines if movable pieces can be placed.
bool Gamemotor::canPiecesBePlaced(int locationX, int locationY) {

	// If piece goes under the game area, piece cant be placed.
	if(locationY > 23) {
		return false;
	}

	// If piece is on top of other movable piece, it doesn't matter.
	for(int a = 0; a < 4; ++a) {
		if(locationX == movablePieces[a]->locationX && locationY
				== movablePieces[a]->locationY) {

			return true;
		}
	}

	// Examine if there already is some other piece on the way.
	bool isTherePiece = false;
	for(int a = 0; a < pieces.size(); ++a) {
		if(locationX == pieces.at(a).locationX
				&& locationY == pieces.at(a).locationY) {
			return false;
		}
	}

	return true;
}

// Examine if game is started.
bool Gamemotor::isGameStarted() {
	return gameStarted;
}

// Examine if the game ended.
bool Gamemotor::didGameEnd() {
	for(int a = 0; a < pieces.size(); ++a) {
		if(pieces.at(a).locationY < 4) {
			return true;
		}
	}
	return false;
}

// Return score.
int Gamemotor::returnScore() {
	return score;
}

// Reset score.
void Gamemotor::resetScore() {
	score = 0;
}

// Return next piece.
int Gamemotor::returnNextPiece() {
	return nextPiece;
}
