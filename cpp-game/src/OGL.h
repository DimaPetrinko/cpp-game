#include "glm/glm.hpp"

typedef glm::vec2 vec2;

class OGL
{
	void DrawQuad(vec2 center, vec2 extents);

	void DrawQuad(vec2 bottomLeft, vec2 topRight);
};