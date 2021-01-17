#include "GraphicsContext.h"
#include "Graphics/Renderer.h"

namespace Graphics
{
	void OnFramebufferChanged(GLFWwindow* window, int width, int height)
	{
		if (!Renderer::Instance()) return;
		Renderer::Instance()->ProjectionMatrix = glm::ortho(0.0f, (float)width * 2, 0.0f, (float)height * 2);
		glViewport(0, 0, width, height);
	}

	GraphicsContext::GraphicsContext(GLFWwindow* window) : mWindow(window) {}

	GraphicsContext::~GraphicsContext() {}

	GLFWwindow* GraphicsContext::Window()
	{
		return mWindow;
	}

	bool GraphicsContext::ShouldWindowClose()
	{
		glfwWindowShouldClose(mWindow);
	}

	void GraphicsContext::CloseWindow()
	{
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
	}

	void GraphicsContext::CancelCloseWindow()
	{
		glfwSetWindowShouldClose(mWindow, GLFW_FALSE);
	}

	void GraphicsContext::InitializeWindowResizing()
	{
		int currentWidth, currentHeight;
		glfwGetFramebufferSize(mWindow, &currentWidth, &currentHeight);
		OnFramebufferChanged(mWindow, currentWidth, currentHeight);
		glfwSetFramebufferSizeCallback(mWindow, OnFramebufferChanged);

	}

	void GraphicsContext::InitializeInput()
	{
		// glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (glfwRawMouseMotionSupported()) glfwSetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	void GraphicsContext::UpdateInput()
	{
		glfwPollEvents();
	}

	bool GraphicsContext::GetKey(int key)
	{
		return glfwGetKey(mWindow, key) == GLFW_PRESS;
	}

	bool GraphicsContext::GetKeyDown(int key)
	{
		return glfwGetKey(mWindow, key) != GLFW_RELEASE;
	}

	int GraphicsContext::GetKeyState(int key)
	{
		return glfwGetKey(mWindow, key);
	}

	vec2 GraphicsContext::GetMousePosition()
	{
		double mouseX, mouseY;
		glfwGetCursorPos(mWindow, &mouseX, &mouseY);
		return {mouseX, mouseY};
	}
}