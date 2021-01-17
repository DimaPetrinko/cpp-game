#include "Player.h"

namespace GameObjects
{
	Player::Player() : Player("Player") {}

	Player::Player(const std::string&& name) : DynamicObject(std::move(name)) {}
	
	Player::~Player() {}

	void Player::Update()
	{
		DynamicObject::Update();
	}

	void Player::Move(vec2 delta)
	{
		DynamicObject::Move(delta * (mIsShifting ? ShiftSpeed : Speed));
		if(delta.y > 0) Velocity = vec2(0,0);
	}

	void Player::Shift(bool value)
	{
		mIsShifting = value;
	}
}