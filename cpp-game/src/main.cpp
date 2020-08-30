#include <iostream>
#include <bits/stdc++.h> 
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GL.h"
#include "Shaders.hpp"

typedef glm::vec2 vec2;

GLFWwindow* mWindow;
GLuint mVa, mIb, mVb, mShader;
glm::mat4 mProjectionMatrix;
vec2 mMousePosition;
vec2 mPlayerPosition;
float mPlayerMovementRate = 3.0f;
float mShiftMultiplier = 3.0f;
double mDeltaTime = 0;

struct Layout
{
public:
	int Id;
	int ElementCount;
	int Type;
	int Normalize;
	int VertexSize;
	int Offset;

public:
	Layout(int id, int elementCount, int type, int normalize, int vertexSize, int offset)
		: Id(id), ElementCount(elementCount), Type(type), Normalize(normalize),
			VertexSize(vertexSize), Offset(offset) {}
	~Layout() {}
};

struct Vertex
{
public:
	vec2 Position;
	vec2 TextureCoordinates;
	const static Layout Layouts[];

public:
	Vertex(vec2 position, vec2 textureCoordinates)
		: Position(position), TextureCoordinates(textureCoordinates) {}
	Vertex(float positionX, float positionY, float textureCoordinateX, float textureCoordinateY)
		: Position({positionX, positionY}), TextureCoordinates({textureCoordinateX, textureCoordinateY}) {}
};

const Layout Vertex::Layouts[] = {Layout(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0),
		Layout(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2 * sizeof(float))};

class Mesh
{
public:
	Vertex* Vertices;
	int VerticesCount;
	int* Indices;
	int IndicesCount;

public:
	Mesh(Vertex* vertices, int verticesCount, int* indices, int indicesCount)
		: Vertices(vertices), VerticesCount(verticesCount),
			Indices(indices), IndicesCount(indicesCount) {}
	~Mesh()
	{
		delete[] Vertices;
		delete[] Indices;
	}
};

void DrawQuad(vec2 size, vec2 position)
{	
	GLCall(glUseProgram(mShader));
	GLCall(glBindVertexArray(mVa));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb));

	GLCall(glUniformMatrix4fv(GetUniformLocation(mShader, "uProjection"), 1, GL_FALSE, &mProjectionMatrix[0][0]));
	GLCall(glUniform2f(GetUniformLocation(mShader, "uPosition"), position.x, position.y));
	GLCall(glUniform2f(GetUniformLocation(mShader, "uSize"), size.x, size.y));

	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
}

void Render()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(0.3f, 0.3f, 0.4f, 1.0f));

	DrawQuad({100, 100}, mPlayerPosition);

	glfwSwapBuffers(mWindow);
}

void PollInput()
{
	glfwPollEvents();

	double mouseX, mouseY;
	glfwGetCursorPos(mWindow, &mouseX, &mouseY);
	mMousePosition = {mouseX, mouseY};

	float currentMultiplier = 1.0f;

	if (glfwGetKey(mWindow, GLFW_KEY_RIGHT_SHIFT) != GLFW_RELEASE
		|| glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) != GLFW_RELEASE) currentMultiplier = mShiftMultiplier;
	else currentMultiplier = 1.0f;
	if (glfwGetKey(mWindow, GLFW_KEY_W) != GLFW_RELEASE) mPlayerPosition.y += mPlayerMovementRate * currentMultiplier;
	if (glfwGetKey(mWindow, GLFW_KEY_S) != GLFW_RELEASE) mPlayerPosition.y -= mPlayerMovementRate * currentMultiplier;
	if (glfwGetKey(mWindow, GLFW_KEY_D) != GLFW_RELEASE) mPlayerPosition.x += mPlayerMovementRate * currentMultiplier;
	if (glfwGetKey(mWindow, GLFW_KEY_A) != GLFW_RELEASE) mPlayerPosition.x -= mPlayerMovementRate * currentMultiplier;
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_RELEASE) glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

void UpdateLogic()
{
	static double previousTime = 0;
	double currentTime = glfwGetTime(); 
	mDeltaTime = currentTime - previousTime;
	previousTime = currentTime;
}

void OnFramebufferChanged(GLFWwindow* window, int width, int height)
{
	mProjectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
	GLCall(glViewport(0, 0, width, height));
}

int InitializeGraphics()
{
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(1280, 720, "cpp-game", NULL, NULL);
	if (!mWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(mWindow);

	auto error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << glewGetErrorString(error) << std::endl;
		return - 1;
	}
	printf("GL version: %s\n", glGetString(GL_VERSION));

	int currentWidth, currentHeight;
	glfwGetFramebufferSize(mWindow, &currentWidth, &currentHeight);
	OnFramebufferChanged(mWindow, currentWidth, currentHeight);
	glfwSetFramebufferSizeCallback(mWindow, OnFramebufferChanged);

	// glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported()) glfwSetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSwapInterval(1);

	GLCall(glFrontFace(GL_CW));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_CULL_FACE));

	return 1;
}

void InitializeGraphicsObjects()
{
	GLCall(glUseProgram(mShader));
	GLCall(glBindVertexArray(mVa));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVb));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb));

	Vertex vertices[] = 
	{
		{-0.5f, -0.5f, 0.0f, 0.0f},
		{-0.5f, 0.5f, 0.0f, 1.0f},
		{0.5f, 0.5f, 1.0f, 1.0f},
		{0.5f, -0.5f, 1.0f, 0.0f},
	};
	const size_t verticesCount = 4;

	unsigned int indices[] = {0, 1, 2, 0, 2, 3};
	const size_t indicesCount = 6;

	GLCall(glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(Vertex), vertices, GL_STATIC_DRAW));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int),
		indices, GL_STATIC_DRAW));

	for (auto &&l : Vertex::Layouts)
	{
		GLCall(glEnableVertexAttribArray(l.Id));
		GLCall(glVertexAttribPointer(l.Id, l.ElementCount, l.Type,
			l.Normalize, l.VertexSize, (const void*)l.Offset));
	}

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glUseProgram(0));
}

void CreateGraphicsObjects()
{
	const std::string* data = LoadShaderFile("cpp-game/res/shaders/Basic.shader");

	if (data)
	{
		auto [vertexShaderSource, fragmentShaderSource] = ParseShader(data);
		mShader = CreateShader(vertexShaderSource, fragmentShaderSource);
		delete data;
	}

	GLCall(glGenBuffers(1, &mVb));
	GLCall(glGenBuffers(1, &mIb));
	GLCall(glGenVertexArrays(1, &mVa));
}

void DeinitializeGraphicsObjects()
{
	GLCall(glDeleteProgram(mShader));
	GLCall(glDeleteBuffers(1, &mVb));
	GLCall(glDeleteBuffers(1, &mIb));
	GLCall(glDeleteVertexArrays(1, &mVa));
}

void DeinitializeGraphics()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

int main()
{
	int successCode = InitializeGraphics();
	if (successCode != 1) return successCode;

	CreateGraphicsObjects();
	InitializeGraphicsObjects();

	while (!glfwWindowShouldClose(mWindow))
	{
		Render();
		PollInput();
		UpdateLogic();
	}

	DeinitializeGraphicsObjects();
	DeinitializeGraphics();
	return 0;
}