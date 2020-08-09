#include "event.h"
#include "game.h"

Event::Event()
{
}

Event::~Event()
{
}

void
Event::HandlingEvent( Game &game )
{
	SDL_Event event = m_SDLEvent;
	while( SDL_PollEvent( &event ) ) {
		handle_event_type( event, game );
	}
}

void
Event::handle_event_type( SDL_Event &event, Game &game )
{
	switch (event.type)
	{
	case SDL_QUIT:
		game.gameOver();
		break;

	case SDL_KEYDOWN:
		handle_event_keydown( event, game );
		break;

	case SDL_KEYUP:
		handle_event_keyup( event, game );
		break;

	case SDL_MOUSEBUTTONDOWN:
		handle_event_mouse_button_down( event, game );
		break;

	case SDL_MOUSEBUTTONUP:
		handle_event_mouse_button_up( event, game );
		break;

	default:
		break;
	}
}

void
Event::handle_event_keydown( SDL_Event& event, Game &game )
{
	switch( event.key.keysym.sym )
	{
	case( SDLK_ESCAPE ):
	case( SDLK_q ):
		game.gameOver();
		break;

	case( SDLK_k ):
		game.PointUp();
		break;

	case( SDLK_j ):
		game.PointDown();
		break;

	case( SDLK_h ):
		game.PointLeft();
		break;

	case( SDLK_l ):
		game.PointRight();
		break;

	case( SDLK_a ):
		game.PrevPoint();
		break;

	case( SDLK_d ):
		game.NextPoint();
		break;

	case( SDLK_w ):
		game.NextNode();
		break;

	case( SDLK_s ):
		game.ToggleTrack();
		break;

	case( SDLK_x ):
		game.ToggleAgent();
		break;

	default:
		break;
	}
}

void
Event::handle_event_keyup( SDL_Event& event, Game &game )
{
}

void
Event::handle_event_mouse_button_up( SDL_Event& event, Game &game )
{
}

void
Event::handle_event_mouse_button_down( SDL_Event& event, Game &game )
{
	switch( event.button.button )
	{
	case( SDL_BUTTON_LEFT ):
		int x, y;
		SDL_GetMouseState( &x, &y );
		game.addPoint( x, y );
		break;

	case( SDL_BUTTON_RIGHT ):
		game.removePoint();
		break;

	default:
		break;
	}
}
