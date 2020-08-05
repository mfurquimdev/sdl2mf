#include "game.h"

int main( int argc, char* args[] )
{
	class Game game( argc, args );
	game.Loop();

	return 0;
}
