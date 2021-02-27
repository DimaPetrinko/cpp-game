#pragma once

#include "Utils/GL.h"
#include "Objects/Player.h"

class Game
{
	Player* mPlayer;
	GLFWwindow* mWindow;

public:

	Game();
	~Game();

	int InitializeGraphics();
	int Run();
};