#include "Game.h"

#include "Utils/RendererFarm.h"

namespace GameLoop
{
	Game::Game(vec2 size, const std::string&& title) : App(size, std::move(title)) {}

	Game::~Game() {}

	void Game::Initialize()
	{
		mPlayer = new Player({-180,0}, RendererFarm::CreateBoxRenderer({10.0f, 10.0f},
				{0.1f, 0.2f, 0.75f, 1.0f}), 400.0f);
		Object* other = new Object({0, -130}, RendererFarm::CreateBoxRenderer({6000.0f, 100.0f},
				{0.75f, 0.2f, 0.1f, 1.0f}));

		mGameObjects.push_back(mPlayer);
		mGameObjects.push_back(other);
	}

	void Game::UpdateInput()
	{
		mContext->UpdateInput();

		if (mContext->GetKey(GLFW_KEY_ESCAPE)) mContext->CloseWindow();
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
			// mRenderer->DrawQuad(go->Size, go->Position, go->SpriteColor);
			go->GetRenderer()->Draw();
		}

		mRenderer->FinishFrame();
	}

	void Game::Deinitialize()
	{
		for (auto &&go : mGameObjects)
		{
			delete go;
		}

		mGameObjects.clear();
	}
}