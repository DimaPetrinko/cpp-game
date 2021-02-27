#include <iostream>
#include "Game.h"

int main()
{
	Game* game = new Game();
	int returnCode = game->Run();
	delete game;
	return returnCode;
}