#include "Game.h"

#include <iostream>
#include "Utils/RendererFarm.h"


void OnFramebufferChanged(GLFWwindow* window, int width, int height)
{
	glPopMatrix(); // resets previous ortho						| we need this because appling orhto on
	glPushMatrix(); // starts recording this one				| itself leads to the image shrinking

	float worldZoom = 400.0f;
	float halfZoom = worldZoom / 2;
	float aspect = ((float)height) / ((float)width);
	float halfScaledAspect = aspect * halfZoom;

	glOrtho(-halfZoom, halfZoom, -halfScaledAspect, halfScaledAspect, 0.0f, 50);
	glViewport(0, 0, width, height);
}

Game::Game() {}

Game::~Game()
{
	delete mPlayer;
}

int Game::InitializeGraphics()
{
	if (!glfwInit()) return -1;

	mWindow = glfwCreateWindow(640, 480, "cpp-game", NULL, NULL);

	if (!mWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(mWindow);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << glewGetErrorString(error) << std::endl;
		return -1;
	}
	printf("GL version: %s\n", glGetString(GL_VERSION));

	int currentWidth, currentHeight;
	glfwGetFramebufferSize(mWindow, &currentWidth, &currentHeight);
	OnFramebufferChanged(mWindow, currentWidth, currentHeight);
	glfwSetFramebufferSizeCallback(mWindow, OnFramebufferChanged);

	return 1;
}

int Game::Run()
{
	// initialize graphics
	int initializationStatus = InitializeGraphics();
	if (initializationStatus != 1) return initializationStatus;

	// initialize game
	mPlayer = new Player(RendererFarm::CreateBoxRenderer({30.0f, 30.0f}, {0.1f, 0.2f, 0.75f, 1.0f}), 5.0f);
	Object* staticObject = new Object({0, 50},
		RendererFarm::CreateBoxRenderer({120.0f, 20.0f},
			{0.75f, 0.2f, 0.1f, 1.0f}));

	while (!glfwWindowShouldClose(mWindow))
	{
		// input
		glfwPollEvents();

		vec2 movement = {0,0};
		if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(mWindow, GLFW_TRUE);

		if (glfwGetKey(mWindow, GLFW_KEY_W) != GLFW_RELEASE) movement.y += 1.0f;
		if (glfwGetKey(mWindow, GLFW_KEY_S) != GLFW_RELEASE) movement.y -= 1.0f;
		if (glfwGetKey(mWindow, GLFW_KEY_D) != GLFW_RELEASE) movement.x += 1.0f;
		if (glfwGetKey(mWindow, GLFW_KEY_A) != GLFW_RELEASE) movement.x -= 1.0f;

		// update
		mPlayer->Move(movement);
		Bounds playerBounds = mPlayer->GetRenderer()->GetBounds();
		Bounds staticPlayerBounds = staticObject->GetRenderer()->GetBounds();

		vec2 resolution = playerBounds.Intersects(staticPlayerBounds);
		mPlayer->Position += resolution;

		// render
		glClear(GL_COLOR_BUFFER_BIT);

		mPlayer->GetRenderer()->Draw();
		staticObject->GetRenderer()->Draw();

		glfwSwapBuffers(mWindow);
	}

	//Deinitialize game
	delete staticObject;

	glfwTerminate();
	return 0;
}