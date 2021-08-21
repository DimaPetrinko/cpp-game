#include "WindowData.h"

namespace Graphics
{
	WindowData::WindowData(vec2 size, const std::string&& title)
	{
		Size = size;
		Title = std::move(title);
	}

	WindowData::WindowData(WindowData&& other)
	{
		Size = std::move(other.Size);
		other.Size = vec2(0,0);
		Title = std::move(other.Title);
		other.Title = "";
	}
}