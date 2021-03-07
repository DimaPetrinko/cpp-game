#pragma once

#include "Utils/Vector.h"

struct Bounds
{
	vec2 Center;
	vec2 Size;
	vec2 Extent;

	Bounds(vec2 center,	vec2 size);
	~Bounds();

	// Returns the resolution vector
	const vec2 Intersects(const Bounds& other) const;
};