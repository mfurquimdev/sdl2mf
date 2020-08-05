#pragma once

#include <SDL2/SDL.h>

class Game {

public:
	Game();
	~Game();

	bool Initialize();
	bool LoadAssets();
	void Display();
	void Shutdown();

private:
	const int DEFAULT_SCREEN_WIDTH = 854;
	const int DEFAULT_SCREEN_HEIGHT = 480;
	const char* DEFAULT_WINDOW_TITLE = "SDL2MF";

	// The window to be rendered to
	SDL_Window* m_window = NULL;

	// The surface contained by the window
	SDL_Surface* m_screenSurface = NULL;

	// The image loaded and shown on the screen
	SDL_Surface* m_helloWorld = NULL;
	SDL_Surface* m_x = NULL;
};
