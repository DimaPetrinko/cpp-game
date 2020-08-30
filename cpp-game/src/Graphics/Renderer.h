#pragma once

#include "Graphics/GL.h"
#include "Graphics/GraphicsContext.h"

class Renderer
{
public:
	glm::mat4 ProjectionMatrix;
	double DeltaTime;
private:
	static Renderer* sInstance;
	GraphicsContext mContext;

public:
	Renderer();
	~Renderer();
	static Renderer* Instance();
	GraphicsContext* Context();
	bool InitializeGraphics(Vector2 size, const std::string&& title);
	void Clear(Color color);
	void FinishFrame();
	void DeinitializeGraphics();
private:
	bool InitializeContext();
	bool InitializeGraphicsLibrary();
	GLFWwindow* CreateWindow(Vector2 size, const std::string&& title);
	void ConfigureMiscelaneousParameters();
};