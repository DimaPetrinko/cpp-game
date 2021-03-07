#include <iostream>
#include "Utils/Vector.h"
#include "Utils/ReturnCodes.h"
#include "GameLoop/App.h"
#include "GameLoop/Game.h"

int main()
{
	GameLoop::App* game = new GameLoop::Game(vec2(1280, 720), "cpp-game");
	
	ReturnCode returnCode = game->Run();

	game->Shutdown();
	delete game;
	return returnCode;
}