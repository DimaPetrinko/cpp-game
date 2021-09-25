#pragma once

#include "Utils/Bounds.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"

namespace Objects
{
	class Object;
}

namespace Objects::Components
{

	class ObjectRenderer
	{
	protected:
		Object* mOwner;
		Graphics::Mesh* mMesh = nullptr;
		Graphics::Texture* mTexture = nullptr;
		Graphics::Shader* mShader = nullptr;

	public:
		ObjectRenderer(Graphics::Mesh* mesh, Graphics::Texture* texture, Graphics::Shader* shader);
		~ObjectRenderer();

		virtual void SetOwner(Object* owner);
		virtual void Draw() const = 0;
		virtual Bounds GetBounds() const = 0;
	};
}