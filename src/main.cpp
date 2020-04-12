#include "game.h"

int main( int argc, char* args[] )
{
	Game game;

	bool initialized = game.Initialize();

	if( initialized )
	{
		game.Display();
	}

	game.Shutdown();

	return 0;
}
