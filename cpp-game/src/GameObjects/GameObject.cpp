#include "GameObject.h"

namespace GameObjects
{
	GameObject::GameObject(const std::string&& name, Color color)
		: Name(name), SpriteColor(color), Position(0, 0), Size(1,1) {}
		
	GameObject::~GameObject() {}
}