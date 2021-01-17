#include "Component.h"
#include <iostream>

namespace GameObjects
{
	Component::Component(GameObject* gameObject) : mGameObject(gameObject) {}

	Component::~Component()
	{
		mGameObject = nullptr;
	}
}