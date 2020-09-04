#include "Renderer.h"
#include "GrahicsStructs.hpp"
#include "Shaders.hpp"

namespace Graphics
{
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

	bool Renderer::InitializeGraphics(vec2 size, const std::string&& title)
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

		CreateGraphicsObjects();
		InitializeGraphicsObjects();

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

	GLFWwindow* Renderer::CreateWindow(vec2 size, const std::string&& title)
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
		DestroyGraphicsObjects();

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

	void Renderer::CreateGraphicsObjects()
	{
		const std::string* data = Shaders::LoadShaderFile("cpp-game/res/shaders/Basic.shader");

		if (data)
		{
			auto [vertexShaderSource, fragmentShaderSource] = Shaders::ParseShader(data);
			mShader = Shaders::CreateShader(vertexShaderSource, fragmentShaderSource);
			delete data;
		}

		GLCall(glGenBuffers(1, &mVb));
		GLCall(glGenBuffers(1, &mIb));
		GLCall(glGenVertexArrays(1, &mVa));
	}

	void Renderer::InitializeGraphicsObjects()
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

	void Renderer::DestroyGraphicsObjects()
	{
		GLCall(glDeleteProgram(mShader));
		GLCall(glDeleteBuffers(1, &mVb));
		GLCall(glDeleteBuffers(1, &mIb));
		GLCall(glDeleteVertexArrays(1, &mVa));
	}

	void Renderer::DrawQuad(vec2 size, vec2 position, Color color)
	{	
		GLCall(glUseProgram(mShader));
		GLCall(glBindVertexArray(mVa));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb));

		glm::mat4 transformation(1.0f);
		transformation *= glm::translate(transformation, Vector3(position, 0));
		transformation *= glm::toMat4(glm::quat(glm::radians(Vector3(0))));
		transformation *= glm::scale(transformation, Vector3(size, 1));
		glm::mat4 mp = ProjectionMatrix * transformation;

		GLCall(glUniformMatrix4fv(Shaders::GetUniformLocation(mShader, "u_MP"), 1, GL_FALSE, &mp[0][0]));
		GLCall(glUniform4f(Shaders::GetUniformLocation(mShader, "u_Color"), color.r, color.g, color.b, color.a));

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
	}
}