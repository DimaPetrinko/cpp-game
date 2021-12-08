#pragma once

#include "Utils/Bounds.h"
#include "Graphics/Texture.h"

namespace Objects
{
	class Object;

	class ObjectRenderer
	{
	public:
		vec2 Size;

	protected:
		const Object* mOwner;
		const Graphics::Texture* mTexture = nullptr;

	public:
		ObjectRenderer(vec2 size);
		~ObjectRenderer();

		void SetOwner(const Object* owner);
		void SetTexture(const Graphics::Texture* texture);
		virtual void Draw() const = 0;
		virtual Bounds GetBounds() const = 0;
	};
}