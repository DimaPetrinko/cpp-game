#include "ObjectRenderer.h"

ObjectRenderer::ObjectRenderer(vec2 size) : Size(size) {}

ObjectRenderer::~ObjectRenderer()
{
	mOwner = nullptr;
}

void ObjectRenderer::SetOwner(const Object* owner)
{
	mOwner = owner;
}