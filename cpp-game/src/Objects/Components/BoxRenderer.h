#pragma once

#include "ObjectRenderer.h"
#include "Objects/Object.h"
#include "Graphics/GL.h"
#include "Graphics/Texture.h"

namespace Objects
{
	class BoxRenderer : public ObjectRenderer
	{
	public:
		col4 Color;

	public:
		BoxRenderer(vec2 size, col4 color);

		void Draw() const override;
		Bounds GetBounds() const override;
	};
}