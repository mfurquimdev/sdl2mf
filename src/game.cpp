#include "game.h"
#include "event.h"

#include <stdio.h>
#include <filesystem>

namespace fs = std::filesystem;

Game::Game( int argc, char* args[] )
{
	fprintf( stderr, "Game::Game()\n" );
	m_window = NULL;
	m_screenSurface = NULL;
	m_images = vector<Image*>();

	initialize();
	loadAssets();
}

Game::~Game()
{
	fprintf( stderr, "Game::~Game()\n" );
	shutdown();
}

void
Game::Loop()
{
	do
	{
		handlingEvents();
		draw();
	} while ( !isGameOver() );
}

void
Game::handlingEvents()
{
	m_event.HandlingEvent( *this );
}

bool
Game::initialize()
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
Game::loadAssets()
{
	bool assetsLoaded = true;

	const std::string lazyFooPath ("assets/lazyfoo");
	for (const auto & entry : fs::directory_iterator(lazyFooPath)) {
		fprintf(stderr, "parent_path: %s\tfilename: %s\n", entry.path().parent_path().string().c_str(), entry.path().filename().string().c_str());
		m_images.push_back(new Image(entry.path().parent_path().string().c_str(), entry.path().filename().string().c_str()));
	}

	// Load images
	for (auto image: m_images) {
		assetsLoaded = image->Load();
		if (!assetsLoaded) {
			break;
		}
		image->Centralize(m_screenSurface);
	}

	return assetsLoaded;
}

void
Game::draw()
{
	// Get window surface
	m_screenSurface = SDL_GetWindowSurface( m_window );

	// Fill the surface white
	SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xEC, 0xEF, 0xF4 ) );

	for (uint8_t i = 0; i < m_images.size(); i++) {
		m_images.at(i)->Drawable(false);
	}
	m_images.at(m_cycleAssets)->Drawable(true);

	// Apply image
	for (auto image: m_images) {
		image->Draw(m_screenSurface);
	}

	// Update the surface
	SDL_UpdateWindowSurface( m_window );
}

void
Game::shutdown()
{
	fprintf( stderr, "Shutdown()\n" );

	// Deallocate surface
	for (auto image: m_images) {
		delete(image);
	}
	m_images.clear();
	
	// Destroy window
	SDL_DestroyWindow( m_window );
	m_window  = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

bool
Game::isGameOver()
{
	return m_quit;
}

void
Game::gameOver()
{
	m_quit = true;
}

void
Game::CycleAsset()
{
	m_cycleAssets++;
	if (m_cycleAssets >= m_images.size()) {
		m_cycleAssets = 0;
	}
}

