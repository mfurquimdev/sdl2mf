#pragma once

#include <SDL2/SDL.h>

class Game {

public:
	Game();
	~Game();

	bool Initialize();
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
};
