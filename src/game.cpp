#include "game.h"

#include <stdio.h>

Game::Game()
{
	m_window = NULL;
	m_screenSurface = NULL;
}

Game::~Game()
{
}

bool
Game::Initialize()
{
	bool initialized = true;

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		initialized = false;
	}
	else
	{
		// Create window
		m_window = SDL_CreateWindow( DEFAULT_WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( m_window == NULL )
		{
			fprintf( stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			initialized = false;
		}
	}

	return initialized;
}

void
Game::Display()
{
	// Get window surface
	m_screenSurface = SDL_GetWindowSurface( m_window );

	// Fill the surface white
	SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xEC, 0xEF, 0xF4 ) );
	
	// Update the surface
	SDL_UpdateWindowSurface( m_window );

	// Wait two seconds
	SDL_Delay( 2000 );
}

void
Game::Shutdown()
{
	// Destroy window
	SDL_DestroyWindow( m_window );

	// Quit SDL subsystems
	SDL_Quit();
}
