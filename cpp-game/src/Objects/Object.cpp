#include "Object.h"

namespace Objects
{
	Object::Object(ObjectRenderer* renderer) : Object({0,0}, renderer) {}

	Object::Object(vec2 position, ObjectRenderer* renderer) : Position(0,0), mRenderer(renderer)
	{
		Position = position;
		mRenderer->SetOwner(this);
	}

	Object::~Object()
	{
		delete mRenderer;
	}

	void Object::UpdateLogic(Graphics::GraphicsContext* context) {}

	void Object::UpdatePhysics() {}

	void Object::ResolveCollision(vec2 resolution) {}

	ObjectRenderer* Object::GetRenderer() const
	{
		return mRenderer;
	}
}