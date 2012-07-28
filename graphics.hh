// Class Graphics where the stuff related to graphics is executed.

#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

#include "tetris.hh"
#include "gamemotor.hh"
#include "toplist.hh"

using namespace std;

class Graphics {
public:
	// Builder.
	Graphics();

	// Destructor.
	~Graphics();

	// Function, where Allegro is initialized.
	bool init();

	// Funktio, joka piirtää pelin taustan.
	void drawBackground(Gamemotor &gamemotor, Levels &levels,
		Toplist &toplist);

	// Function where the next piece is drawn to left bar.
	void drawNextPiece(Gamemotor &gamemotor);

	// Function that draws one piece.
	void drawPiece(int color, int locationX, int locationY);

	// Function where events are dealed with.
	bool events(Gamemotor &gamemotor, Levels &levels,
		Toplist &toplist);

private:
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_DISPLAY *screen;
	ALLEGRO_TIMER *speedTimer;
	ALLEGRO_TIMER *levelTimer;
	ALLEGRO_TIMER *screenUpdateTimer;
	ALLEGRO_FONT *title;
	ALLEGRO_FONT *text;
	ALLEGRO_FONT *smallText;
};

#endif
