#include "Game.h"
#include "GameObjects/StaticObject.h"

namespace GameLoop
{
	Game::Game(vec2 size, const std::string&& title) : App(size, std::move(title)) {}

	Game::~Game() {}

	void Game::Init()
	{
		mPlayer = new GameObjects::Player("Player", Color(0.2f, 0.2f, 0.5f, 1.0f));
		mPlayer->Size = {100, 100};
		mPlayer->Position = vec2(1280.0f / 2, 720.0f / 2);

		GameObjects::StaticObject* other = new GameObjects::StaticObject("Other", Color(0.5f, 0.2f, 0.2f, 1.0f));
		other->Size = {50, 50};
		other->Position = vec2(1280.0f / 2, 720.0f / 2);
		
		mGameObjects.push_back(other);
		mGameObjects.push_back(mPlayer);
	}

	void Game::UpdateInput()
	{
		mContext->UpdateInput();

		if (mContext->GetKey(GLFW_KEY_ESCAPE)) mContext->CloseWindow();

		mMousePosition = mContext->GetMousePosition();

		mPlayer->Shift(mContext->GetKeyDown(GLFW_KEY_RIGHT_SHIFT) || mContext->GetKeyDown(GLFW_KEY_LEFT_SHIFT));
		
		vec2 inputVector = vec2(0,0);
		if (mContext->GetKeyDown(GLFW_KEY_W)) inputVector.y = 1;
		if (mContext->GetKeyDown(GLFW_KEY_S)) inputVector.y = -1;
		if (mContext->GetKeyDown(GLFW_KEY_D)) inputVector.x = 1;
		if (mContext->GetKeyDown(GLFW_KEY_A)) inputVector.x = -1;
		if (mContext->GetKeyDown(GLFW_KEY_DELETE)) mReturnCode = RETURN_CODE_ERROR;

		mPlayer->Move(glm::length2(inputVector) < 0.01f ? inputVector : glm::normalize(inputVector));
	}

	void Game::UpdateLogic()
	{
		for (auto &&go : mGameObjects)
		{
			go->Update();
		}	
	}

	void Game::UpdateGraphics()
	{
		mRenderer->Clear(Color(0.3f, 0.3f, 0.4f, 1.0f));

		for (auto &&go : mGameObjects)
		{
			mRenderer->DrawQuad(go->Size, go->Position, go->SpriteColor);
		}

		mRenderer->FinishFrame();
	}

	void Game::Deinit()
	{
		for (auto &&go : mGameObjects)
		{
			delete go;
		}

		mGameObjects.clear();
	}
}