#pragma once

#include <iostream>
#include "GL/glew.h"

#define GLCall(x) GLClearError();\
	x;\
	GLLogCall(#x, __FILE__, __LINE__)

void GLClearError() { while (glGetError() != GL_NO_ERROR); }

bool GLLogCall(const char* function, const char* file, int line)
{
	while (auto error = glGetError())
	{
		std::cout << "[OpenGL] " << error << " in " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
