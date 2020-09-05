#pragma once

#include "GameObjects/DynamicObject.h"

namespace GameObjects
{
	class Player : public DynamicObject
	{
	public:
		float Speed = 3.0f;
		float ShiftSpeed = 9.0f;
	private:
		bool mIsShifting;

	public:
		Player();
		Player(const std::string&& name, Color color);
		~Player();

		void Update() override;
		void Move(vec2 delta) override;

		void Shift(bool value);
	};
}