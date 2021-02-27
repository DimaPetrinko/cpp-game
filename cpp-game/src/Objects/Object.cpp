#include "Object.h"

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

ObjectRenderer* Object::GetRenderer() const
{
	return mRenderer;
}