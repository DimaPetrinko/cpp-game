#pragma once

#include <string>
#include "Utilities/Vectors.h"

namespace GameObjects
{
	class GameObject
	{
	public:
		std::string Name;
		Color SpriteColor;
		vec2 Position;
		vec2 Size;

	public:
		GameObject(const std::string&& name, Color color);
		virtual ~GameObject();

		virtual void Update() = 0;
	};
}