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

	for( int i = 9; i >= 0; i-- )
	{
		path.points.push_back( { 200.0f * sinf( (float)i / 10.0f * 3.14159f * 2.0f ) + ScreenWidth() / 2,
								 200.0f * cosf( (float)i / 10.0f * 3.14159f * 2.0f ) + ScreenHeight() / 2 } );
	}
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
	mouse.x = (float) x;
	mouse.y = (float) y;
//	fprintf( stderr, "Mouse: (%d,%d)\n", x, y );

	if( track == 1 )
	{
		addPoint( x, y );
	}
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
			m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_SOFTWARE );
			if( m_renderer == NULL )
			{
				fprintf( stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
				initialized = false;
			}
			else
			{
				m_screenSurface = SDL_GetWindowSurface( m_window );
			}
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
	int sw = 2;
	int sh = 2;

	if( !path.points.empty() )
	{
		for( float t = 0.0f; t < (float) path.points.size(); t += 0.005f )
		{
			struct sPoint2D p = path.GetSplinePoint( t );

			const SDL_Rect dstrect = { p.x-1, p.y-1, sw, sh };
			SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xEC, 0xEF, 0xF4 ) );
		}
	}

	int w = 10;
	int h = 10;

	for( auto p: path.points )
	{
		const SDL_Rect dstrect = { p.x-5, p.y-5, w, h };
		SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xBF, 0x61, 0x6A ) );
	}

	if( !path.points.empty() )
	{
		struct sPoint2D p = path.points.at(nSelectedPoint);
		const SDL_Rect dstrect = { p.x-5, p.y-5, w, h };
		SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xEB, 0xCB, 0x68 ) );
	}

	if( !path.points.empty() )
	{
		struct sPoint2D p = path.points.at(node);
		const SDL_Rect dstrect = { p.x-5, p.y-5, w, h };
		SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xA3, 0xBE, 0x8C ) );
	}

	if( !path.points.empty() )
	{
		struct sPoint2D p = path.points.at(nextNode);
		const SDL_Rect dstrect = { p.x-5, p.y-5, w, h };
		SDL_FillRect( m_screenSurface, &dstrect, SDL_MapRGB( m_screenSurface->format, 0xA3, 0xBE, 0x8C ) );
	}

	if( agent == 1 )
	{
//		SDL_SetRenderDrawColor( m_renderer, 94, 129, 172, SDL_ALPHA_OPAQUE );
		SDL_SetRenderDrawColor( m_renderer, 136, 192, 208, SDL_ALPHA_OPAQUE );
		
		float i = path.ClosestIndex( node, nextNode, mouse );
		fprintf( stderr, "Idx: %f\n", i );
		struct sPoint2D p = path.GetSplinePoint( i );
		struct sPoint2D g = path.GetSplineGradient( i );
		fprintf( stderr, "P: (%d,%d)\tG: (%d,%d)\n", p.x, p.y, g.x, g.y );
		float r = atan2( -g.y, g.x );
		struct sPoint2D p1 = { (int)  10.0f * sin(r)  + p.x, (int)  10.0f * cos(r) + p.y };
		struct sPoint2D p2 = { (int) -10.0f * sin(r)  + p.x, (int) -10.0f * cos(r) + p.y };

		fprintf( stderr, "Line: (%d,%d) -- (%d,%d)\n", p1.x, p1.y, p2.x, p2.y );
		SDL_RenderDrawLine( m_renderer, p1.x, p1.y, p2.x, p2.y);
	}

	// Update the surface
	SDL_RenderPresent( m_renderer );
	SDL_UpdateWindowSurface( m_window );

	if( track == 1 )
	{
		removePoint();
	}
}

void
Game::shutdown()
{
	fprintf( stderr, "Shutdown()\n" );

	SDL_DestroyRenderer( m_renderer );
	m_renderer = NULL;

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

void
Game::NextNode()
{
	node++;
	if( node >= path.points.size() )
	{
		node = 0;
		lap++;
	}

	nextNode = node + 1;
	if( nextNode >= path.points.size() )
	{
		nextNode = 0;
	}
		
	fprintf( stderr, "Node: %d\tLap: %d\n", node, lap );
}

void
Game::ToggleTrack()
{
	track ^= 1;
}

void
Game::ToggleAgent()
{
	agent ^= 1;
}
