#include "game.h"

int main( int argc, char* args[] )
{
	Game game;

	if( game.Initialize() )
	{
		if( game.LoadAssets() )
		{
			game.Display();
		}
	}

	game.Shutdown();

	return 0;
}
