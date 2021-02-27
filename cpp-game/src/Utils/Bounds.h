#pragma once

#include "Utils/Vector.h"

struct Bounds
{
	vec2 BottomLeft;
	vec2 TopRight;
	vec2 BottomRight;
	vec2 TopLeft;
	vec2 Size;
	vec2 Extent;
	vec2 Center;

	Bounds(vec2 bottomLeft,	vec2 topRight);
	~Bounds();

	// Returns the resolution vector
	const vec2 Intersects(const Bounds& other) const;
};