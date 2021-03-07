#pragma once

#include <vector>
#include "GameLoop/App.h"
#include "Utils/Vector.h"
#include "Objects/Player.h"

namespace GameLoop
{
	class Game : public App
	{
	private:
		std::vector<Object*> mGameObjects;
		Player* mPlayer;
		vec2 mMousePosition;

	public:
		Game(vec2 size, const std::string&& title);
		~Game();

	protected:
		void Initialize() override;
		void UpdateInput() override;
		void UpdateLogic() override;
		void UpdatePhysics() override;
		void UpdateGraphics() override;
		void Deinitialize() override;
	};
}