#include <iostream>
#include "OGL.h"

#include "application.h"

int main()
{
	// OGL ogl = OGL(640, 320);

	// while (!ogl.IsWindowClosed())
	// // while (ogl.IsWindowClosed())
	// {
	// 	/* code */
	// }
	
  Application app;
  app.Start();
  std::cout << "Yay, we are out." << std::endl;
}