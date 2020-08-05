#include "game.h"

int main( int argc, char* args[] )
{
	Game game( argc, args );
	game.Loop();

	return 0;
}
