#pragma once

#include <SDL2/SDL.h>

class Game;

class Event {

public:
	Event();
	~Event();

	void HandlingEvent( Game& );

private:

	void handle_event_type( SDL_Event&, Game& );
	void handle_event_keydown( SDL_Event&, Game& );
	void handle_event_keyup( SDL_Event&, Game& );
	void handle_event_mouse_button_down( SDL_Event&, Game& );
	void handle_event_mouse_button_up( SDL_Event&, Game& );

	SDL_Event m_SDLEvent;
};
