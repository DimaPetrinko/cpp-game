#include "ObjectRenderer.h"

namespace Objects
{
	ObjectRenderer::ObjectRenderer(vec2 size) : Size(size) {}

	ObjectRenderer::~ObjectRenderer()
	{
		mOwner = nullptr;
	}

	void ObjectRenderer::SetOwner(const Object* owner)
	{
		mOwner = owner;
	}

	void ObjectRenderer::SetTexture(const Graphics::Texture* texture)
	{
		mTexture = texture;
	}
}