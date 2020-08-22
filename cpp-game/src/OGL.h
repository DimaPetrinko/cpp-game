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
	static void SetWindowWidthAndHeight(OGL* instance, const int width, const int height);
	bool IsWindowClosed() const;
	void DrawQuad(vec2 center, vec2 extents);
	// void DrawQuad(vec2 bottomLeft, vec2 topRight);
private:
	void UpdateProjectionMatrix();
	bool CreateWindow(GLFWwindow*& window, const char* title, int width, int height);
};

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

void FramebuferSizeCallback(GLFWwindow* window, int width, int height)
{
	OGL::SetWindowWidthAndHeight(nullptr, width, height);
}

OGL::OGL(float windowWidth, float windowHeight) : mWindowWidth(windowWidth),
	mWindowHeight(windowHeight), mWindow(nullptr)
{
	if (!CreateWindow(mWindow, "OGL-Engine-2.5", mWindowWidth, mWindowHeight))
	{
		return;
	}
	auto error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << glewGetErrorString(error) << std::endl;
		return;
	}
	printf("GL version: %s\n", glGetString(GL_VERSION));

	UpdateProjectionMatrix();

	glClearColor(0.05f, 0.05f, 0.15f, 1.0f);

	glfwSetFramebufferSizeCallback(mWindow, &FramebuferSizeCallback);
	int currentWidth, currentHeight;
	glfwGetFramebufferSize(mWindow, &currentWidth, &currentHeight);
	SetWindowWidthAndHeight(this, currentWidth, currentHeight);

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));

	// GLCall(glEnable(GL_BLEND));
	// GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GLCall(glFrontFace(GL_CCW));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_CULL_FACE));
}

bool OGL::CreateWindow(GLFWwindow*& window, const char* title, int width, int height)
{
	static bool glfwInitialized;
	if (!glfwInitialized)
	{
		auto success = glfwInit();
		// TODO: make a macro
		if (!success)
		{
			printf("Could not initialize GLFW!\n");
			return false;
		}
		glfwInitialized = true;
		printf("Initialized GLFW. Version: %s\n", glfwGetVersionString());
	}

	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	std::cout << "Created new window " << title << " (" << width << ", " << height << ")\n";
	return true;
}

void OGL::SetWindowWidthAndHeight(OGL* instance, const int width, const int height)
{
	static OGL* renderer;
	if (instance) renderer = instance;
	renderer->mWindowWidth = width;
	renderer->mWindowHeight = height;
	renderer->UpdateProjectionMatrix();
	GLCall(glViewport(0, 0, width - 350.0f, height));
}

void OGL::UpdateProjectionMatrix()
{
	ProjectionMatrix = glm::perspectiveFov(20.0f, mWindowWidth - 350.0f, mWindowHeight, 0.01f, 1000.0f);
		// glm::ortho(0.0f, _windowWidth, 0.0f, _windowHeight, -100.0f, 100.0f);
}

bool OGL::IsWindowClosed() const
{
	return glfwWindowShouldClose(mWindow);
}

void OGL::DrawQuad(vec2 center, vec2 extents)
{

}