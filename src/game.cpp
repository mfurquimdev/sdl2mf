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
		else
		{
			m_screenSurface = SDL_GetWindowSurface( m_window );
		}
	}

	return initialized;
}

bool
Game::LoadAssets()
{
	bool assetsLoaded = true;

	const char* file_path = "assets/lazyfoo/hello_world.bmp";

	// Load an image
	m_helloWorld = SDL_LoadBMP( file_path );

	if( m_helloWorld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", file_path, SDL_GetError() );
		 assetsLoaded = false;
	}

	return assetsLoaded;
}

void
Game::Display()
{
	// Get window surface
	m_screenSurface = SDL_GetWindowSurface( m_window );

	// Fill the surface white
	SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xEC, 0xEF, 0xF4 ) );

	// Center the image on screen
	SDL_Rect dstrect = { (m_screenSurface->w - m_helloWorld->w)/2,
						 (m_screenSurface->h - m_helloWorld->h)/2,
						  m_helloWorld->w,
						  m_helloWorld->h, };

	// Apply image
	SDL_BlitSurface( m_helloWorld, NULL, m_screenSurface, &dstrect);
	
	// Update the surface
	SDL_UpdateWindowSurface( m_window );

	// Wait two seconds
	SDL_Delay( 2000 );
}

void
Game::Shutdown()
{
	// Deallocate surface
	SDL_FreeSurface( m_helloWorld );
	m_helloWorld = NULL;

	// Destroy window
	SDL_DestroyWindow( m_window );
	m_window  = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}
