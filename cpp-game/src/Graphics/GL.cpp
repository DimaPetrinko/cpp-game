#include "GL.h"
namespace Graphics
{
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
}