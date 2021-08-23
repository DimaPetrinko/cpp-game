#include "Game.h"

#include "Utils/RendererFarm.h"

namespace GameLoop
{
	Game::Game(Graphics::WindowData&& windowData) : App(std::move(windowData)) {}

	Game::~Game() {}

	void Game::InitializeData()
	{
		mPlayer = new Objects::Player(
			{-180,0},
			RendererFarm::CreateBoxRenderer(
				{10.0f, 10.0f},
				{1.0f, 1.0f, 1.0f, 1.0f}
			),
			400.0f,
			"res/textures/image.png"
		);
		Objects::Object* other = new Objects::Object(
			{0, -130},
			RendererFarm::CreateBoxRenderer(
				{6000.0f, 100.0f},
				{0.75f, 0.2f, 0.1f, 1.0f}
			)
		);

		mGameObjects.push_back(mPlayer);
		mGameObjects.push_back(other);
	}

	void Game::DeinitializeData()
	{
		for (auto &&go : mGameObjects)
		{
			delete go;
		}

		mGameObjects.clear();
	}

	void Game::UpdateInput()
	{
		mContext->UpdateInput();

		if (mContext->GetKey(GLFW_KEY_ESCAPE)) Shutdown();
		if (mContext->GetKeyDown(GLFW_KEY_DELETE)) mReturnCode = RETURN_CODE_ERROR;
		mMousePosition = mContext->GetMousePosition();
	}

	void Game::UpdateLogic()
	{
		for (auto &&go : mGameObjects)
		{
			// mPlayer->Shift(mContext->GetKeyDown(GLFW_KEY_RIGHT_SHIFT) || mContext->GetKeyDown(GLFW_KEY_LEFT_SHIFT));
			go->UpdateLogic(mContext);
		}
	}

	void Game::UpdatePhysics()
	{
		for (auto &&go : mGameObjects)
		{
			go->UpdatePhysics();
		}

		Bounds playerBounds = mPlayer->GetRenderer()->GetBounds();
		for (auto &&go : mGameObjects)
		{
			if (go == mPlayer) continue;
			Bounds otherBounds = go->GetRenderer()->GetBounds();
			vec2 resolution = playerBounds.Intersects(otherBounds);
			mPlayer->ResolveCollision(resolution);
		}
	}

	void Game::UpdateGraphics()
	{
		mRenderer->Clear(col4(0));

		for (auto &&go : mGameObjects)
		{
			go->GetRenderer()->Draw();
		}

		mRenderer->FinishFrame();
	}
}