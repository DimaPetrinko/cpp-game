#pragma once

#include "Objects/Components/BoxRenderer.h"

namespace RendererFarm
{
	// This method returns a new instance of BoxRenderer with given parameters.
	// It is created on heap. The user is responsible for its lifecycle
	BoxRenderer* CreateBoxRenderer(vec2 size, col4 color)
	{
		return new BoxRenderer(size, color);
	}
}