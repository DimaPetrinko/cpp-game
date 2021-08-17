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
		Game(Graphics::WindowData&& windowData);
		~Game();

	protected:
		void InitializeData() override;
		void DeinitializeData() override;

		void UpdateInput() override;
		void UpdateLogic() override;
		void UpdatePhysics() override;
		void UpdateGraphics() override;
	};
}