#include "Game.h"

#include "Resources/AssetDatabase.h"

namespace GameLoop
{
	Game::Game(Graphics::WindowData&& windowData) : App(std::move(windowData)) {}

	Game::~Game() {}

	void Game::InitializeData()
	{
		// Rendering::Mesh* mesh;
		// Rendering::Shader* shader;
		// Rendering::Texture* texture;

		// mesh = Resources::AssetDatabase::GetAsset<Rendering::Mesh>
		// 	(WORKING_DIRECTORY "res/models/MonkeyHead.obj");
		// shader = Resources::AssetDatabase::GetAsset<Rendering::Shader>
		// 	(WORKING_DIRECTORY "res/shaders/Basic.shader");
		// texture = Resources::AssetDatabase::GetAsset<Rendering::Texture>
		// 	(WORKING_DIRECTORY "res/textures/checker3.jpg");
		// mGameObject = new Systems::GameObject(&mRenderer, mesh, texture, 1, shader);

		// // to increment reference count
		// mesh = Resources::AssetDatabase::GetAsset<Rendering::Mesh>
		// 	(WORKING_DIRECTORY "res/models/cube.obj");
		// shader = Resources::AssetDatabase::GetAsset<Rendering::Shader>
		// 	(WORKING_DIRECTORY "res/shaders/Basic.shader");
		// texture = Resources::AssetDatabase::GetAsset<Rendering::Texture>
		// 	(WORKING_DIRECTORY "res/textures/image.png");
		// mGameObject2 = new Systems::GameObject(&mRenderer,mesh, texture, 2, shader);
		// mGameObject2->Transform.Position = {0.0f, 0.0f, -100.0f};
		// mGameObject2->Transform.Rotation = {0.0f, 45.0f, 0.0f};

		// mPlayer = new Objects::Player(
		// 	{-180,0},
		// 	RendererFarm::CreateBoxRenderer(
		// 		{10.0f, 10.0f},
		// 		{1.0f, 1.0f, 1.0f, 1.0f}
		// 	),
		// 	400.0f,
		// 	"res/textures/image.png"
		// );
		// Objects::Object* other = new Objects::Object(
		// 	{0, -130},
		// 	RendererFarm::CreateBoxRenderer(
		// 		{6000.0f, 100.0f},
		// 		{0.75f, 0.2f, 0.1f, 1.0f}
		// 	)
		// );

		{
			Graphics::Texture* texture = Resources::AssetDatabase::GetAsset<Graphics::Texture>("textures/image.png");
			Graphics::Shader* basicShader = Resources::AssetDatabase::GetAsset<Graphics::Shader>("shaders/Basic.shader");
			Objects::Components::BoxRenderer* renderer = new Objects::Components::BoxRenderer(
				{10.0f, 10.0f},
				texture,
				basicShader
			); 
			mPlayer = new Objects::Player(
				vec3 {-180,0,0},
				renderer,
				400.0f
			);
			mGameObjects.push_back(mPlayer);
		}

		{
			Graphics::Texture* texture = Resources::AssetDatabase::GetAsset<Graphics::Texture>("textures/checker3.jpg");
			Graphics::Shader* basicShader = Resources::AssetDatabase::GetAsset<Graphics::Shader>("shaders/Basic.shader");
			Objects::Components::BoxRenderer* renderer = new Objects::Components::BoxRenderer(
				{600.0f, 100.0f},
				texture,
				basicShader
			);
			texture->Tiling = renderer->Size / 100.0f;
			Objects::Object* otherObject = new Objects::Object(
				{0, -130, 0},
				renderer
			);
			mGameObjects.push_back(otherObject);
		}
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
		for (auto &&go : mGameObjects)
		{
			go->GetRenderer()->Draw();
		}
	}

	void Game::StartFrame()
	{
		App::StartFrame();
		mRenderer->Clear(col4(0.2));

		mRenderer->ViewMatrix = mCameraTransform.GetInvertedTranslationMatrix();
	}
}