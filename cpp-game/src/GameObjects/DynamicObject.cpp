#include "DynamicObject.h"

namespace GameObjects
{
	DynamicObject::DynamicObject(const std::string&& name) : GameObject(std::move(name)), Velocity(0,0) {}
	
	DynamicObject::~DynamicObject() {}

	void DynamicObject::Update()
	{
		Velocity += Gravity;
		DynamicObject::Move(Velocity);
	}

	void DynamicObject::Move(vec2 delta)
	{
		vec2 pos = mTransform->GetPosition();
		pos += delta;
		mTransform->SetPosition(pos);
	}

	const vec2 DynamicObject::Gravity = vec2(0,-0.1f);
}