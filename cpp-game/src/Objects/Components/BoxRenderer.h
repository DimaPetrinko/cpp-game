#pragma once

#include "ObjectRenderer.h"
#include "Objects/Object.h"
#include "Utils/GL.h"

class BoxRenderer : public ObjectRenderer
{
public:
	col4 Color;

public:
	BoxRenderer(vec2 size, col4 color);

	void Draw() const override;
	Bounds GetBounds() const override;
};