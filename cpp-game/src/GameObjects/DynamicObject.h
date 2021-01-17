#pragma once

#include "GameObjects/GameObject.h"

namespace GameObjects
{
	class DynamicObject : public GameObject
	{
	public:
		static const vec2 Gravity;
		vec2 Velocity;

	public:	
		DynamicObject(const std::string&& name);
		~DynamicObject();

		void Update() override;

		virtual void Move(vec2 delta);
	};
}