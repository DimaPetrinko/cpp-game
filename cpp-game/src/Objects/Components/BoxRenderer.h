#pragma once

#include "Objects/Components/ObjectRenderer.h"
#include "Objects/Object.h"
#include "Graphics/GL.h"
#include "Graphics/Texture.h"

namespace Objects::Components
{
	class BoxRenderer : public ObjectRenderer
	{
	public:
		vec2 Size;
		col4 Color;

	public:
		BoxRenderer(vec2 size, Graphics::Texture* texture, Graphics::Shader* shader);

		void Draw() const override;
		Bounds GetBounds() const override;
		void SetOwner(Object* owner) override;
	};
}