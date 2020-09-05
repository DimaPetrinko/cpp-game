#include "DynamicObject.h"

namespace GameObjects
{
	DynamicObject::DynamicObject(const std::string&& name, Color color) : GameObject(std::move(name), color) {}
	
	DynamicObject::~DynamicObject() {}

	void DynamicObject::Update()
	{
		Velocity += Gravity;
		DynamicObject::Move(Velocity);
	}

	void DynamicObject::Move(vec2 delta)
	{
		Position += delta;
	}

	const vec2 DynamicObject::Gravity = vec2(0,-0.1f);
}