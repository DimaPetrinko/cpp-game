#include "Object.h"

namespace Objects
{
	Object::Object(Components::ObjectRenderer* renderer) : Object({0,0,0}, renderer) {}

	Object::Object(vec3 position, Components::ObjectRenderer* renderer) : mRenderer(renderer)
	{
		Transform.Position = position;
		mRenderer->SetOwner(this);
	}

	Object::~Object()
	{
		delete mRenderer;
	}

	void Object::UpdateLogic(Graphics::GraphicsContext* context) {}

	void Object::UpdatePhysics() {}

	void Object::ResolveCollision(vec2 resolution) {}

	Components::ObjectRenderer* Object::GetRenderer() const
	{
		return mRenderer;
	}
}