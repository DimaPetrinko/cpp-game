#pragma once

#include "GameObjects/GameObject.h"

namespace GameObjects
{
	class StaticObject : public GameObject
	{
	public:
		StaticObject(const std::string&& name, Color color);
		~StaticObject();

		void Update() override;
	};
}