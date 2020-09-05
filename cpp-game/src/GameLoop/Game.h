#pragma once

#include <vector>
#include "GameLoop/App.h"
#include "Utilities/Vectors.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"

namespace GameLoop
{
	class Game : public App
	{
	private:
		std::vector<GameObjects::GameObject*> mGameObjects;
		GameObjects::Player* mPlayer;
		vec2 mMousePosition;

	public:
		Game(vec2 size, const std::string&& title);
		~Game();

	protected:
		void Init() override;
		void UpdateGraphics() override;
		void UpdateLogic() override;
		void UpdateInput() override;
		void Deinit() override;
	};
}