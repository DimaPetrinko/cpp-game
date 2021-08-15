#pragma once

#include "Graphics/GL.h"

namespace Graphics
{
	class GraphicsContext
	{
	private:
		GLFWwindow* mWindow;
	public:
		GraphicsContext(GLFWwindow* window);
		~GraphicsContext();
		GLFWwindow* Window();
		bool ShouldWindowClose();
		void CloseWindow();
		void CancelCloseWindow();
		void InitializeWindowResizing();
		void InitializeInput();
		void UpdateInput();
		bool GetKey(int key);
		bool GetKeyDown(int key);
		int GetKeyState(int key);
		vec2 GetMousePosition();
	};
}