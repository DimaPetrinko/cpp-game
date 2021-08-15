#pragma once

#include "Graphics/GL.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/GrahicsStructs.h"

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
		Mesh* mDefaultQuad;
		GLuint mVa, mIb, mVb, mShader;
		bool mInitialized;

	public:
		Renderer();
		~Renderer();

		static Renderer* Instance();
		GraphicsContext* Context();

		bool InitializeGraphics(vec2 size, const std::string&& title);
		void DeinitializeGraphics();
		
		void Clear(col4 color);
		void FinishFrame();

		void CreateGraphicsObjects();
		Mesh* CreateDefaultQuad();
		void InitializeGraphicsObjects();
		void DestroyGraphicsObjects();
		void DrawQuad(vec2 size, vec2 position, col4 color);

	private:
		bool InitializeContext();
		bool InitializeGraphicsLibrary();
		GLFWwindow* CreateWindow(vec2 size, const std::string&& title);
		void ConfigureMiscelaneousParameters();
	};
}