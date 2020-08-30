#include "Renderer.h"

Renderer* Renderer::sInstance{};

Renderer::Renderer() : ProjectionMatrix(), mContext(nullptr)
{
	if (sInstance) delete sInstance;
	sInstance = this;
}

Renderer::~Renderer()
{
	DeinitializeGraphics();
}

Renderer* Renderer::Instance()
{
	return sInstance;
}

GraphicsContext* Renderer::Context()
{
	return &mContext;
}

bool Renderer::InitializeGraphics(Vector2 size, const std::string&& title)
{
	if (!InitializeContext()) return -1;
	
	GLFWwindow* window = CreateWindow(size, std::move(title));
	if (!window) return -1;
	
	mContext = GraphicsContext(window);

	if (InitializeGraphicsLibrary()) return -1;
	printf("GL version: %s\n", glGetString(GL_VERSION));

	ConfigureMiscelaneousParameters();

	mContext.InitializeWindowResizing();
	mContext.InitializeInput();

	return 1;
}

bool Renderer::InitializeContext()
{
	return glfwInit();
}

bool Renderer::InitializeGraphicsLibrary()
{
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << glewGetErrorString(error) << std::endl;
		return false;
	}
}

GLFWwindow* Renderer::CreateWindow(Vector2 size, const std::string&& title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
	if (!window) glfwTerminate();
	else
	{
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
	}

	return window;
}

void Renderer::ConfigureMiscelaneousParameters()
{
	GLCall(glFrontFace(GL_CW));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_CULL_FACE));
}

void Renderer::DeinitializeGraphics()
{
	glfwDestroyWindow(mContext.Window());
	glfwTerminate();
}

void Renderer::Clear(Color color)
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::FinishFrame()
{
	glfwSwapBuffers(mContext.Window());

	static double previousTime = 0;
	double currentTime = glfwGetTime(); 
	DeltaTime = currentTime - previousTime;
	previousTime = currentTime;
}