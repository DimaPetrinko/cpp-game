#include "BoxRenderer.h"

BoxRenderer::BoxRenderer(vec2 size, col4 color) : ObjectRenderer(size), Color(color) {}

void BoxRenderer::Draw() const
{
	Bounds bounds = GetBounds();
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(Color.r, Color.g, Color.b);
	glVertex2f(bounds.BottomLeft.x, bounds.BottomLeft.y);
	glVertex2f(bounds.BottomLeft.x, bounds.TopRight.y);
	glVertex2f(bounds.TopRight.x, bounds.BottomLeft.y);
	glVertex2f(bounds.TopRight.x, bounds.TopRight.y);
	glEnd();
}

Bounds BoxRenderer::GetBounds() const
{
	vec2 position = mOwner->Position;
	vec2 halfSize = Size / 2.0f;
	return Bounds(
		vec2(position.x - halfSize.x, position.y - halfSize.y),
		vec2(position.x + halfSize.x, position.y + halfSize.y));
}