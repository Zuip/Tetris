#include "graphics.hh"

// Builder
Graphics::Graphics() {
	eventQueue = NULL;
	speedTimer = NULL;
	levelTimer = NULL;
	screenUpdateTimer = NULL;
	screen = NULL;
	title = NULL;
	text = NULL;
	smallText = NULL;
}

// Destructor
Graphics::~Graphics() {
	al_destroy_event_queue(eventQueue);
	al_destroy_display(screen);
	al_destroy_timer(speedTimer);
	al_destroy_timer(levelTimer);
	al_destroy_timer(screenUpdateTimer);
}

// Function where Allegro events are initialized.
bool Graphics::init() {
	// Initialize Allegro
	if(!al_init()) {
		cout << "Error in initializing Allegro!" << endl;
		return false;
	}

	// Set screen size
	int sizex = 420;
	int sizey = 670;
	screen = al_create_display(sizex, sizey);
	if(!screen) {
		cout << "Error in creating display." << endl;
		return false;
	}

	// Set backgroundcolor.
	al_clear_to_color(al_map_rgb(0.4, 0.4, 0.8));

	// Initialize keyboard
	if(!al_install_keyboard()) {
		cout << "Error in initializing keyboard!" << endl;
	}

	// Initialize event queue.
	eventQueue = al_create_event_queue();
	if(!eventQueue) {
		cout << "Error in creating event queue!" << endl;
		al_destroy_display(screen);
		return false;
	}

	// Create timer that tells when to lower pieces.
	speedTimer = al_create_timer(2);
	al_start_timer(speedTimer);

	// Create timer that tells when to higher the level.
	levelTimer = al_create_timer(30);
	al_start_timer(levelTimer);

	// Create timer that tells when to update screen.
	screenUpdateTimer = al_create_timer(0.1);
	al_start_timer(screenUpdateTimer);

	// Initialize fonts
	al_init_font_addon();
	al_init_ttf_addon();
	title = al_load_ttf_font("title.ttf", 64, 0);
	text = al_load_ttf_font("text.ttf", 20, 0);
	smallText = al_load_ttf_font("text.ttf", 16, 0);

	// Register event sources
	al_register_event_source(eventQueue,
		al_get_display_event_source(screen));
	al_register_event_source(eventQueue,
		al_get_keyboard_event_source());
	al_register_event_source(eventQueue,
		al_get_timer_event_source(speedTimer));
	al_register_event_source(eventQueue,
		al_get_timer_event_source(levelTimer));
	al_register_event_source(eventQueue,
		al_get_timer_event_source(screenUpdateTimer));

	// Update display
	al_flip_display();

	return true;
}

// Function that draws the background of the game.
void Graphics::drawBackground(Gamemotor &gamemotor, Levels &levels,
		Toplist &toplist) {

	// Background color
	ALLEGRO_COLOR backgroundColor = al_map_rgb(0, 102, 153);
	al_draw_filled_rectangle(0, 0, 420, 670, backgroundColor);

	// Black rectangle where actual game is.
	ALLEGRO_COLOR blackColor = al_map_rgb(0, 0, 0);
	al_draw_filled_rectangle(149, 49.5, 399, 649.5, blackColor);

	// Dark blue lines in left bar.
	ALLEGRO_COLOR colorDarkBlue = al_map_rgb(25, 25, 112);
	al_draw_line(3, 275, 146, 275, colorDarkBlue, 1);
	al_draw_line(3, 277, 146, 277, colorDarkBlue, 1);
	al_draw_line(3, 364, 146, 364, colorDarkBlue, 1);
	al_draw_line(3, 366, 146, 366, colorDarkBlue, 1);
	al_draw_line(3, 444, 146, 444, colorDarkBlue, 1);
	al_draw_line(3, 446, 146, 446, colorDarkBlue, 1);
	al_draw_line(3, 589, 146, 589, colorDarkBlue, 1);
	al_draw_line(3, 591, 146, 591, colorDarkBlue, 1);

	// Red line which shows the height where game ends if pieces
	// stops there.
	ALLEGRO_COLOR colorRed = al_map_rgb(153, 0, 0);
	al_draw_line(150.5, 150.5, 399.5, 150.5, colorRed, 1);

	// "Tetris" -title on top of the game screen.
	al_draw_text(title, al_map_rgb(255, 255, 255), 210,
		-15 , ALLEGRO_ALIGN_CENTRE, "Tetris");

	// Text "Press A to begin a new game" which shows when game isn't on.
	if(gamemotor.isGameStarted() == false) {
		al_draw_text(text, al_map_rgb(153, 0, 0), 275,
			300 , ALLEGRO_ALIGN_CENTRE, "Press A");
		al_draw_text(text, al_map_rgb(153, 0, 0), 275,
			325 , ALLEGRO_ALIGN_CENTRE, "to begin");
		al_draw_text(text, al_map_rgb(153, 0, 0), 275,
			350 , ALLEGRO_ALIGN_CENTRE, "a new game");

	}

	// Score -text in left bar.
	al_draw_text(text, al_map_rgb(0, 0, 0), 10, 300,
		ALLEGRO_ALIGN_LEFT, "Score");
	string score = toplist.intToString(gamemotor.returnScore());
	al_draw_text(text, al_map_rgb(0, 0, 0), 15, 325,
		ALLEGRO_ALIGN_LEFT, score.c_str());

	// "Level" -text in left bar.
	al_draw_text(text, al_map_rgb(0, 0, 0), 10, 380,
		ALLEGRO_ALIGN_LEFT, "Level");
	string level = toplist.intToString(levels.levelNow);
	al_draw_text(text, al_map_rgb(0, 0, 0), 15, 405,
		ALLEGRO_ALIGN_LEFT, level.c_str());

	// Top 3 -teksti vasemmassa palkissa
	al_draw_text(text, al_map_rgb(0, 0, 0), 10, 460,
		ALLEGRO_ALIGN_LEFT, "Top3");
	al_draw_text(text, al_map_rgb(184, 134, 11), 19, 490,
		ALLEGRO_ALIGN_LEFT, "1");
	al_draw_text(text, al_map_rgb(139, 131, 134), 15, 520,
		ALLEGRO_ALIGN_LEFT, "2");
	al_draw_text(text, al_map_rgb(139, 101, 8), 15, 550,
		ALLEGRO_ALIGN_LEFT, "3");

	// Top 3 -list
	string first, second, third;
	toplist.returnToplist(first, second, third);
	al_draw_text(smallText, al_map_rgb(36, 24, 130), 55, 493,
		ALLEGRO_ALIGN_LEFT, first.c_str());
	al_draw_text(smallText, al_map_rgb(36, 24, 130), 55, 523,
		ALLEGRO_ALIGN_LEFT, second.c_str());
	al_draw_text(smallText, al_map_rgb(36, 24, 130), 55, 553,
		ALLEGRO_ALIGN_LEFT, third.c_str());

	// Zuip -text in left bar.
	al_draw_text(text, al_map_rgb(70, 130, 180), 40, 615,
		ALLEGRO_ALIGN_LEFT, "Zuip");

	// Draws next piece to left bar.
	drawNextPiece(gamemotor);
}

// Funktio, jossa piirretään seuraava palikka
void Graphics::drawNextPiece(Gamemotor &gamemotor) {

	// Black color.
	ALLEGRO_COLOR colorBlack = al_map_rgb(0, 0, 0);

	// "Next piece" -text in left bar.
	al_draw_text(smallText, al_map_rgb(0, 0, 0), 10, 80,
		ALLEGRO_ALIGN_LEFT, "Next");
        al_draw_text(smallText, al_map_rgb(0, 0, 0), 10, 100,
                ALLEGRO_ALIGN_LEFT, "piece");

	// Black rectangle where you can see next piece.
	al_draw_filled_rectangle(30, 130, 110, 250, colorBlack);

	// Set basic information about next piece
	int nextPiece = gamemotor.returnNextPiece();
	int coordx = 47;
	int coordy = 140;
	int piece3coordx = 0;
	int piece3coordy = 0;
	int piece4coordx = 0;
	int piece4coordy = 0;

	// Align the piece to center of the black rectangle.
	if(nextPiece == 0 || nextPiece == 3 || nextPiece == 4 || nextPiece == 5) {
		coordy += 12;
	} else if(nextPiece == 6) {
		coordy -= 12;
	} else if(nextPiece == 2) {
		coordx += 12;
	}

	// Draw pieces.
	drawPiece(nextPiece, coordx, coordy + 25);
	drawPiece(nextPiece, coordx, coordy + 50);
	if(nextPiece == 0) {
		piece4coordx = 1;
		piece4coordy = 1;
	} else if(nextPiece == 1) {
		piece3coordx = 1;
		piece3coordy = 1;
		piece4coordx = 1;
		piece4coordy = 2;
	} else if(nextPiece == 2) {
		piece3coordy = 3;
	} else if(nextPiece == 3) {
		piece4coordx = 1;
		piece4coordy = 2;
	} else if(nextPiece == 4) {
		piece4coordx = 1;
		piece4coordy = 0;
	} else if(nextPiece == 5) {
		piece3coordx = 1;
		piece4coordx = 1;
		piece4coordy = 1;
	} else if(nextPiece == 6) {
		piece3coordx = 1;
		piece3coordy = 2;
		piece4coordx = 1;
		piece4coordy = 3;
	}
	drawPiece(nextPiece, piece3coordx * 25 + coordx, piece3coordy * 25 + coordy);
	drawPiece(nextPiece, piece4coordx * 25 + coordx, piece4coordy * 25 + coordy);
}

// Function where one piece is drawn.
void Graphics::drawPiece(int color, int locationX, int locationY) {
	// Set colors
	int dark_r[7], dark_g[7], dark_b[7];
	int light_r[7], light_g[7], light_b[7];

	// Blue
	dark_r[0] = 0; dark_g[0] = 51, dark_b[0] = 255;
	light_r[0] = 0; light_g[0] = 102, light_b[0] = 255;

	// Red
	dark_r[1] = 255; dark_g[1] = 0, dark_b[1] = 0;
	light_r[1] = 255; light_g[1] = 51, light_b[1] = 51;

	// Green
	dark_r[2] = 51; dark_g[2] = 153, dark_b[2] = 0;
	light_r[2] = 51; light_g[2] = 204, light_b[2] = 51;

	// Violet
	dark_r[3] = 102; dark_g[3] = 0, dark_b[3] = 153;
	light_r[3] = 102; light_g[3] = 0, light_b[3] = 204;

	// Yellow
	dark_r[4] = 139; dark_g[4] = 117, dark_b[4] = 0;
	light_r[4] = 238; light_g[4] = 238, light_b[4] = 10;

	// Orange
	dark_r[5] = 153; dark_g[5] = 51, dark_b[5] = 0;
	light_r[5] = 255; light_g[5] = 102, light_b[5] = 0;

	// Pink
	dark_r[6] = 255; dark_g[6] = 0, dark_b[6] = 204;
	light_r[6] = 255; light_g[6] = 102, light_b[6] = 153;

	// Initialize colors
	ALLEGRO_COLOR dark = al_map_rgb(dark_r[color], dark_g[color],
		dark_b[color]);
	ALLEGRO_COLOR light = al_map_rgb(light_r[color], light_g[color],
		light_b[color]);

	// Draw the inner part of piece
	al_draw_filled_rectangle(locationX + 0, locationY + 0,
		locationX + 24, locationY + 24, light);

	// Draw the outer part of piece
	al_draw_rectangle(locationX + 0, locationY + 0,
		locationX + 24, locationY + 24, dark, 1);
}

// Function where Allegro-events are dealed with.
bool Graphics::events(Gamemotor &gamemotor,
		Levels &levels, Toplist &toplist) {

	// Initialize Allegro-event.
	ALLEGRO_EVENT event;
	al_wait_for_event(eventQueue, &event);

	// Examine if there was any Allegro timer events
	if(event.type == ALLEGRO_EVENT_TIMER 
			&& gamemotor.isGameStarted() == true) {

		// Lower pieces
		if(event.timer.source == speedTimer) {
			gamemotor.lowerPieces(toplist);
		}

		// Higher level
		if(event.timer.source == levelTimer
				&& levels.levelNow < 19) {
			++levels.levelNow;
			al_set_timer_speed(speedTimer, levels.level[levels.levelNow]);
		}

		// Update screen
		if(event.timer.source == screenUpdateTimer) {
			al_flip_display();
		}
	}

	// Examine if there was any keyboard events
	if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
		if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			return false;
		}
		if(event.keyboard.keycode == ALLEGRO_KEY_A) {
			gamemotor.beginGame();
			levels.levelNow = 1;
			gamemotor.resetScore();
		}
		if(gamemotor.isGameStarted() == true) {
			if(event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				gamemotor.dropPieces(toplist);
			}
			if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                        	gamemotor.moveHorizontally(true);
			}
			if(event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
				gamemotor.moveHorizontally(false);
			}
			if(event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				gamemotor.lowerPieces(toplist);
			}
			if(event.keyboard.keycode == ALLEGRO_KEY_UP) {
				gamemotor.rotatePieces();
			}
		}
	}

	if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return false;
	}

	return true;
}
