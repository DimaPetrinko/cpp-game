#include "Player.h"

Player::Player(BoxRenderer* renderer, float movementSpeed) : Player({0,0}, renderer, movementSpeed) {}

Player::Player(vec2 position, BoxRenderer* renderer, float movementSpeed) : Object(position, renderer)
{
	if (movementSpeed <= 0) movementSpeed = 0.05f;
	MovementSpeed = movementSpeed;
}

void Player::Move(vec2 movement)
{
	Position += movement * MovementSpeed;
}