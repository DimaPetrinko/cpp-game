#include <iostream>
#include "Graphics/WindowData.h"
#include "GameLoop/ReturnCodes.h"
#include "GameLoop/App.h"
#include "GameLoop/Game.h"

int main()
{
	GameLoop::App* game = new GameLoop::Game(Graphics::WindowData(vec2(1280, 720), "cpp-game"));

	ReturnCode returnCode = game->Run();

	delete game;

	std::cout << "Game exited with code " << (int)returnCode << std::endl;
	return returnCode;
}