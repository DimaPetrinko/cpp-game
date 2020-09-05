#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Utilities/Vectors.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Graphics
{
	#define GLCall(x) Graphics::GLClearError();\
	x;\
	Graphics::GLLogCall(#x, __FILE__, __LINE__)

	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
}