#include <iostream>
#include "Utilities/Vectors.h"
#include "Utilities/ReturnCodes.h"
#include "GameLoop/App.h"
#include "GameLoop/Game.h"

int main()
{
	GameLoop::App* game = new GameLoop::Game(vec2(1280, 720), "cpp-game");
	
	ReturnCode returnCode = game->Run();

	delete game;
	return returnCode;
}