#include "Game.h"

namespace GameLoop
{
	Game::Game(vec2 size, const std::string&& title) : App(size, std::move(title)) {}

	Game::~Game() {}

	void Game::Init()
	{

	}

	void Game::UpdateInput()
	{
		mContext->UpdateInput();

		mMousePosition = mContext->GetMousePosition();

		float currentMultiplier = 1.0f;

		if (mContext->GetKeyDown(GLFW_KEY_RIGHT_SHIFT) || mContext->GetKeyDown(GLFW_KEY_LEFT_SHIFT))
			currentMultiplier = mShiftMultiplier;
		else currentMultiplier = 1.0f;
		if (mContext->GetKeyDown(GLFW_KEY_W)) mPlayerPosition.y += mPlayerMovementRate * currentMultiplier;
		if (mContext->GetKeyDown(GLFW_KEY_S)) mPlayerPosition.y -= mPlayerMovementRate * currentMultiplier;
		if (mContext->GetKeyDown(GLFW_KEY_D)) mPlayerPosition.x += mPlayerMovementRate * currentMultiplier;
		if (mContext->GetKeyDown(GLFW_KEY_A)) mPlayerPosition.x -= mPlayerMovementRate * currentMultiplier;
		if (mContext->GetKey(GLFW_KEY_ESCAPE)) mContext->CloseWindow();
	}

	void Game::UpdateLogic()
	{

	}

	void Game::UpdateGraphics()
	{
		mRenderer->Clear(Color(0.3f, 0.3f, 0.4f, 1.0f));

		mRenderer->DrawQuad({100, 100}, vec2(1280.0f / 2, 720.0f / 2), Color(0.5f, 0.2f, 0.2f, 0.0f));
		mRenderer->DrawQuad({100, 100}, mPlayerPosition, Color(0.2f, 0.2f, 0.5f, 0.0f));

		mRenderer->FinishFrame();
	}

	void Game::Deinit()
	{

	}
}