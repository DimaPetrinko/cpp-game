#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLCall(x) GLClearError();\
	x;\
	GLLogCall(#x, __FILE__, __LINE__)

typedef glm::vec2 vec2;

class OGL
{
public:
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
private:
	float mWindowWidth;
	float mWindowHeight;
	GLFWwindow* mWindow;

public:
	OGL(float windowWidth, float windowHeight);
	~OGL();
	void Init();
	void PostRender() const;
	static void SetWindowWidthAndHeight(OGL* instance, const int width, const int height);
	bool IsWindowClosed() const;
	void DrawQuad(vec2 center, vec2 extents);
	// void DrawQuad(vec2 bottomLeft, vec2 topRight);
private:
	void UpdateProjectionMatrix();
	bool CreateWindow(GLFWwindow*& window, const char* title, int width, int height);
};