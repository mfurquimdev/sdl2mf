#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "event.h"
#include "image.h"

using namespace std;

class Game {

public:
	Game( int argc, char* args[] );
	~Game();

	void Loop();

	// Gets and Sets
	bool isGameOver();
	void gameOver();

	void CycleAsset();

private:

	// Consts
	const int DEFAULT_SCREEN_WIDTH = 1280;
	const int DEFAULT_SCREEN_HEIGHT = 720;
	const char* DEFAULT_WINDOW_TITLE = "SDL2MF";

	// Game's main functions
	bool initialize();
	bool loadAssets();
	void draw();
	void shutdown();

	uint8_t m_cycleAssets = 0;

	//Current displayed image
	SDL_Surface* gCurrentSurface = NULL;

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
	vector<Image*> m_images;
};
