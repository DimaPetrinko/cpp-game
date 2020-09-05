#pragma once

#include "GameLoop/App.h"
#include "Utilities/Vectors.h"

namespace GameLoop
{
	class Game : public App
	{
	private:
		vec2 mMousePosition;
		vec2 mPlayerPosition;
		float mPlayerMovementRate = 3.0f;
		float mShiftMultiplier = 3.0f;

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