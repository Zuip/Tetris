// This game is made by Zuip.

// This game is my first program that uses Allegro and this is also my first
// program that I have submitted in GitHub.

// The basic idea of this game is to be like classic Tetris. Still, there is
// some differences from the original game.

#include <allegro5/allegro.h>

#include "gamemotor.hh"
#include "graphics.hh"
#include "toplist.hh"

// A function where the speeds of levels and the starting level is
// set.
void setLevels(Levels &levels) {
	levels.level[0] = 1;
	levels.level[1] = 0.8;
	levels.level[2] = 0.6;
	levels.level[3] = 0.5;
	levels.level[4] = 0.4;
	levels.level[5] = 0.3;
	levels.level[6] = 0.25;
	levels.level[7] = 0.2;
	levels.level[8] = 0.17;
	levels.level[9] = 0.14;
	levels.level[10] = 0.12;
	levels.level[11] = 0.10;
	levels.level[12] = 0.09;
	levels.level[13] = 0.08;
	levels.level[14] = 0.07;
	levels.level[15] = 0.06;
	levels.level[16] = 0.05;
	levels.level[17] = 0.04;
	levels.level[18] = 0.03;
	levels.level[19] = 0.02;

	levels.levelNow = 0;
}

// A funktion where the situation of the game is drawn.
void drawGame(Gamemotor &gamemotor, Graphics &graphics,
		Levels &levels, Toplist &toplist) {

	// Clear the color.
	al_clear_to_color(al_map_rgb(0, 0, 0));

	// Draw the background of the game.
	graphics.drawBackground(gamemotor, levels, toplist);

	// Draw the pieces if game is started.
	if(gamemotor.isGameStarted() == true) {
		int amountOfPieces = gamemotor.returnAmountOfPieces();
		for(int a = 0; a < amountOfPieces; ++a) {
			Piece nowResearching = gamemotor.returnPiece(a);
			graphics.drawPiece(nowResearching.color,
				nowResearching.locationX * 25 + 150,
				nowResearching.locationY * 25 + 50);
		}
	}

	// Update screen.
	al_flip_display();
}


int main() {
	// Create Graphics-class where all graphics-related stuff is
	// executed.
	Graphics graphics;

	// Initiliaze Allegro.
	if(graphics.init() == false) {
		return 0;
	}

	// Gamemotor-class where most of logic-side of the game is
	// executed.
	Gamemotor gamemotor;

	// Struct Levels, where the levels of the game is tabled.
	Levels levels;
	setLevels(levels);

	// Toplist where is everything related to toplist.
	Toplist toplist;
	toplist.initList();

	// The main loop of the game.
	while(true) {

		// Execute events. If esc-button or right corner cross is
		// pressed, end game.
		if(graphics.events(gamemotor, levels, toplist)
				== false) {

			return 1;
		}

		// Draw game
		drawGame(gamemotor, graphics, levels, toplist);
	}

	return 1;
}
