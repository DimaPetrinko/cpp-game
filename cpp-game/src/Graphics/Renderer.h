#pragma once

#include "Graphics/GL.h"
#include "Graphics/GraphicsContext.h"

namespace Graphics
{
	class Renderer
	{
	public:
		glm::mat4 ProjectionMatrix;
		double DeltaTime;

	private:
		static Renderer* sInstance;
		GraphicsContext mContext;
		GLuint mVa, mIb, mVb, mShader;

	public:
		Renderer();
		~Renderer();

		static Renderer* Instance();
		GraphicsContext* Context();

		bool InitializeGraphics(vec2 size, const std::string&& title);
		void DeinitializeGraphics();
		
		void Clear(Color color);
		void FinishFrame();

		void CreateGraphicsObjects();
		void InitializeGraphicsObjects();
		void DestroyGraphicsObjects();
		void DrawQuad(vec2 size, vec2 position, Color color);

	private:
		bool InitializeContext();
		bool InitializeGraphicsLibrary();
		GLFWwindow* CreateWindow(vec2 size, const std::string&& title);
		void ConfigureMiscelaneousParameters();
	};
}