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
		std::vector<Objects::Object*> mGameObjects;
		Objects::Player* mPlayer;
		Objects::Components::TransformComponent mCameraTransform
		{
			glm::vec3(0.0f, 0.0f, -10.0f),
			glm::vec3(0.0f, 180.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f)
		};
		vec2 mMousePosition;
		// Systems::Components::TransformComponent mCameraTransform
		// {
		// 	glm::vec3(75.0f, 125.0f, 150.0f),
		// 	glm::vec3(30.0f, -30.0f, 0.0f),
		// 	glm::vec3(0.0f, 0.0f, 0.0f)
		// };

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

		void StartFrame() override;
	};
}