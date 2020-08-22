#include <iostream>
#include "OGL.h"

int main()
{
	std::cout << "Hello, cpp-game\n";
	OGL ogl = OGL(640, 320);

	while (!ogl.IsWindowClosed())
	// while (ogl.IsWindowClosed())
	{
		/* code */
	}
	
}