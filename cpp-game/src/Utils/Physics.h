#pragma once

#include "Utils/Vector.h"

namespace Physics
{
	const vec2 Gravity = {0, -9.81f};
	const float DefaultDrag = 0.01f;
	const float FrictionCoefficient = 0.9f;
	const float DeltaTime = 1/60.0f;
	const float TerminalVelocity = 1000.0f;
}