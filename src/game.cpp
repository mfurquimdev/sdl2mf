#include "game.h"
#include "event.h"

#include <cstdio>
#include <cmath>

Game::Game( int argc, char* args[] )
{
	fprintf( stderr, "Game::Game()\n" );
	m_window = NULL;
	m_screenSurface = NULL;

	initialize();
	loadAssets();

//	for( int i = 0; i < 10; i++ )
//	{
//		path.points.push_back( { 200.0f * sinf( (float)i / 10.0f * 3.14159f * 2.0f ) + ScreenWidth() / 2,
//								 200.0f * cosf( (float)i / 10.0f * 3.14159f * 2.0f ) + ScreenHeight() / 2 } );
//	}
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
		SDL_Delay(100);
	} while ( !isGameOver() );
}

void
Game::handlingEvents()
{
	m_event.HandlingEvent( *this );
	int x, y;
	SDL_GetMouseState( &x, &y );
	fprintf( stderr, "Mouse: (%d,%d)\n", x, y );
	addPoint( x, y );
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

	const char* hello_world_file_path = "assets/lazyfoo/hello_world.bmp";
	const char* x_file_path = "assets/lazyfoo/x.bmp";

	// Load image
	m_helloWorld = SDL_LoadBMP( hello_world_file_path );
	if( m_helloWorld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", hello_world_file_path, SDL_GetError() );
		assetsLoaded = false;
	}

	m_x = SDL_LoadBMP( x_file_path );
	if( m_x == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", x_file_path, SDL_GetError() );
		assetsLoaded = false;
	}

	return assetsLoaded;
}

void
Game::draw()
{
	// Fill the surface Black
	SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0x2E, 0x34, 0x40 ) );

	// Draw Spline
	int sw = 3;
	int sh = 3;

	for( float t = 0.0f; t < (float) path.points.size(); t += 0.005f )
	{
		struct sPoint2D p = path.GetSplinePoint( t );

		const SDL_Rect dstrect = { p.x, p.y, sw, sh };
		SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xEC, 0xEF, 0xF4 ) );
	}

	int w = 5;
	int h = 5;

	for( auto p: path.points )
	{
		const SDL_Rect dstrect = { p.x, p.y, w, h };
		SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xBF, 0x61, 0x6A ) );
	}

	struct sPoint2D p = path.points.at(nSelectedPoint);
	const SDL_Rect dstrect = { p.x, p.y, w, h };
	SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xEB, 0xCB, 0x68 ) );

	//for( auto p: points )
	//{
	//	const SDL_Rect dstrect = { p.first, p.second, w, h };
	//	SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xEC, 0xEF, 0xF4 ) );
	//}

	// Update the surface
	SDL_UpdateWindowSurface( m_window );
	removePoint();
}

void
Game::shutdown()
{
	fprintf( stderr, "Shutdown()\n" );
	points.clear();

	// Destroy window
	SDL_DestroyWindow( m_window );
	m_window  = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

void
Game::addPoint( int x, int y )
{
	path.points.push_back( sPoint2D{ x, y } );
}

void
Game::removePoint()
{
	if( !path.points.empty() )
	{
		path.points.pop_back();
	}
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
Game::NextPoint()
{
	nSelectedPoint = (nSelectedPoint + 1) % path.points.size();
}

void
Game::PrevPoint()
{
	nSelectedPoint = (nSelectedPoint + path.points.size() - 1) % path.points.size();
}

void
Game::PointUp()
{
	path.points.at( nSelectedPoint ).y -= 10;
	if( path.points.at( nSelectedPoint ).y < 0 )
	{
		path.points.at( nSelectedPoint ).y = 0;
	}
}

void
Game::PointDown()
{
	path.points.at( nSelectedPoint ).y += 10;
	if( path.points.at( nSelectedPoint ).y > ScreenHeight() - 5 )
	{
		path.points.at( nSelectedPoint ).y = ScreenHeight() - 5;
	}
}

void
Game::PointLeft()
{
	path.points.at( nSelectedPoint ).x -= 10;
	if( path.points.at( nSelectedPoint ).x < 0 )
	{
		path.points.at( nSelectedPoint ).x = 0;
	}
}

void
Game::PointRight()
{
	path.points.at( nSelectedPoint ).x += 10;
	if( path.points.at( nSelectedPoint ).x > ScreenWidth() - 5 )
	{
		path.points.at( nSelectedPoint ).x = ScreenWidth() - 5;
	}
}

const int
Game::ScreenHeight()
{
	return DEFAULT_SCREEN_HEIGHT;
}

const int
Game::ScreenWidth()
{
	return DEFAULT_SCREEN_WIDTH;
}
