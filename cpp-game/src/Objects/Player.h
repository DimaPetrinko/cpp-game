#pragma once

#include "Object.h"
#include "Components/BoxRenderer.h"

struct Player : public Object
{
public:
	float MovementSpeed;

public:
	Player(BoxRenderer* renderer, float movementSpeed);
	Player(vec2 position, BoxRenderer* renderer, float movementSpeed);

	void Move(vec2 movement);
};