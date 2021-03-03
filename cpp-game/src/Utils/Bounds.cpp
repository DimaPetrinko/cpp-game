#include "Bounds.h"

Bounds::Bounds(vec2 bottomLeft,	vec2 topRight)
{
	BottomLeft = bottomLeft;
	TopRight = topRight;
	BottomRight = {TopRight.x, BottomLeft.y};
	TopLeft = {BottomLeft.x, TopRight.y};
	Size = TopRight - BottomLeft;
	Extent = Size / 2.0f;
	Center = BottomLeft + Extent;
}

Bounds::~Bounds() {}

const vec2 Bounds::Intersects(const Bounds& other) const
{
	vec2 resolution = vec2(0,0);

	vec2 centerDelta = Center - other.Center;
	vec2 centerDeltaSign = centerDelta;
	centerDelta.x = std::abs(centerDelta.x);
	centerDelta.y = std::abs(centerDelta.y);
	if (centerDeltaSign.x != 0) centerDeltaSign.x /= centerDelta.x;
	if (centerDeltaSign.y != 0) centerDeltaSign.y /= centerDelta.y;
	vec2 idealDelta = Extent + other.Extent;
	vec2 overlap = idealDelta - centerDelta;

	if (overlap.x > 0 && overlap.y > 0)
	{
		if (overlap.x == overlap.y) resolution = overlap;
		else if (overlap.x > overlap.y) resolution.y = overlap.y;
		else resolution.x = overlap.x;
	}

	resolution *= centerDeltaSign;
	return resolution;
}