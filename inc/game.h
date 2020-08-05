#pragma once

#include <SDL2/SDL.h>

#include "event.h"

class Game {

public:
	Game( int argc, char* args[] );
	~Game();

	void Loop();

	// Gets and Sets
	bool isGameOver();
	void gameOver();

private:

	// Consts
	const int DEFAULT_SCREEN_WIDTH = 854;
	const int DEFAULT_SCREEN_HEIGHT = 480;
	const char* DEFAULT_WINDOW_TITLE = "SDL2MF";

	// Game's main functions
	bool initialize();
	bool loadAssets();
	void draw();
	void shutdown();

	// Variables
	bool m_quit = false;

	// The event handler
	Event m_event;
	void handlingEvents();

	// The window to be rendered to
	SDL_Window* m_window = NULL;

	// The surface contained by the window
	SDL_Surface* m_screenSurface = NULL;

	// The image loaded and shown on the screen
	SDL_Surface* m_helloWorld = NULL;
	SDL_Surface* m_x = NULL;
};
