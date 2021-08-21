#pragma once

#include <iostream>
#include "Utils/Vector.h"

namespace Graphics
{
	struct WindowData
	{
		vec2 Size;
		std::string Title;

		WindowData(vec2 size, const std::string&& title);
		WindowData(WindowData&& other);
	};
}