#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GL.h"
#include "Shaders.hpp"

GLFWwindow* mWindow;
GLuint mVa, mIb, mVb, mShader;
glm::mat4 mProjectionMatrix;
double mMouseX = 0, mMouseY = 0;
float mPlayerX = 0, mPlayerY = 0;
float mPlayerMovementRate = 3.0f;
float mShiftMultiplier = 3.0f;
double mDeltaTime = 0;

void DrawQuad(float width, float height, float x, float y)
{	
	GLCall(glUseProgram(mShader));
	GLCall(glBindVertexArray(mVa));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb));

	GLCall(glUniformMatrix4fv(GetUniformLocation(mShader, "uProjection"), 1, GL_FALSE, &mProjectionMatrix[0][0]));
	GLCall(glUniform2f(GetUniformLocation(mShader, "uPosition"), x, y));
	GLCall(glUniform2f(GetUniformLocation(mShader, "uSize"), width, height));

	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
}

void Render()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	DrawQuad(100, 100, mPlayerX, mPlayerY);

	glfwSwapBuffers(mWindow);
}

void PollInput()
{
	glfwPollEvents();

	glfwGetCursorPos(mWindow, &mMouseX, &mMouseY);

	float currentMultiplier = 1.0f;

	if (glfwGetKey(mWindow, GLFW_KEY_RIGHT_SHIFT) != GLFW_RELEASE
		|| glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) != GLFW_RELEASE) currentMultiplier = mShiftMultiplier;
	else currentMultiplier = 1.0f;
	if (glfwGetKey(mWindow, GLFW_KEY_W) != GLFW_RELEASE) mPlayerY += mPlayerMovementRate * currentMultiplier;
	if (glfwGetKey(mWindow, GLFW_KEY_S) != GLFW_RELEASE) mPlayerY -= mPlayerMovementRate * currentMultiplier;
	if (glfwGetKey(mWindow, GLFW_KEY_D) != GLFW_RELEASE) mPlayerX += mPlayerMovementRate * currentMultiplier;
	if (glfwGetKey(mWindow, GLFW_KEY_A) != GLFW_RELEASE) mPlayerX -= mPlayerMovementRate * currentMultiplier;
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

	float vertices[] = 
	{
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};
	const size_t verticesCount = 4;
	const size_t elementsPerVertex = 2;
	unsigned int indices[] = {0, 1, 3, 3, 1, 2};
	const size_t indicesCount = 6;

	GLCall(glBufferData(GL_ARRAY_BUFFER, verticesCount * elementsPerVertex * sizeof(float),
		vertices, GL_DYNAMIC_DRAW));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int),
		indices, GL_DYNAMIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, elementsPerVertex, GL_FLOAT, GL_FALSE,
		elementsPerVertex * sizeof(float), 0));

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