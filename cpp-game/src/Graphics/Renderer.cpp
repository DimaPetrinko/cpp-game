#include "Renderer.h"
#include "Graphics/Shaders.hpp"
#include "Utilities/ReturnCodes.h"

namespace Graphics
{
	Renderer* Renderer::sInstance{};

	Renderer::Renderer() : ProjectionMatrix(), mContext(nullptr), mDefaultQuad()
	{
		if (sInstance) delete sInstance;
		sInstance = this;
	}

	Renderer::~Renderer()
	{
		if (mInitialized) DeinitializeGraphics();
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
		if (!InitializeContext()) return RETURN_CODE_ERROR;
		
		GLFWwindow* window = CreateWindow(size, std::move(title));
		if (!window) return RETURN_CODE_ERROR;
		
		mContext = GraphicsContext(window);

		if (InitializeGraphicsLibrary()) return RETURN_CODE_ERROR;
		printf("GL version: %s\n", glGetString(GL_VERSION));

		ConfigureMiscelaneousParameters();

		mContext.InitializeWindowResizing();
		mContext.InitializeInput();

		CreateGraphicsObjects();
		InitializeGraphicsObjects();

		mInitialized = true;
		return RETURN_CODE_RUNNING;
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
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}

	void Renderer::DeinitializeGraphics()
	{
		mInitialized = false;
		DestroyGraphicsObjects();

		glfwDestroyWindow(mContext.Window());
		glfwTerminate();
	}

	void Renderer::Clear(Color color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(color.r, color.g, color.b, color.a);
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

		glGenBuffers(1, &mVb);
		glGenBuffers(1, &mIb);
		glGenVertexArrays(1, &mVa);
	}

	Mesh* Renderer::CreateDefaultQuad()
	{
		const size_t verticesCount = 4;
		Vertex* vertices = new Vertex[verticesCount]
		{
			{-0.5f, -0.5f, 0.0f, 0.0f},
			{-0.5f, 0.5f, 0.0f, 1.0f},
			{0.5f, 0.5f, 1.0f, 1.0f},
			{0.5f, -0.5f, 1.0f, 0.0f},
		};

		const size_t indicesCount = 6;
		unsigned int* indices = new unsigned int[indicesCount] {0, 1, 2, 0, 2, 3};

		Mesh* mesh = new Mesh(vertices, verticesCount, indices, indicesCount);

		return mesh;
	}

	void Renderer::InitializeGraphicsObjects()
	{
		glUseProgram(mShader);
		glBindVertexArray(mVa);
		glBindBuffer(GL_ARRAY_BUFFER, mVb);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb);

		mDefaultQuad = CreateDefaultQuad();
		
		glBufferData(GL_ARRAY_BUFFER, mDefaultQuad->VerticesCount * sizeof(Vertex),
			mDefaultQuad->Vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mDefaultQuad->IndicesCount * sizeof(unsigned int),
			mDefaultQuad->Indices, GL_STATIC_DRAW);

		for (auto &&l : Vertex::Layouts)
		{
			glEnableVertexAttribArray(l.Id);
			glVertexAttribPointer(l.Id, l.ElementCount, l.Type,
				l.Normalize, l.VertexSize, (const void*)l.Offset);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	void Renderer::DestroyGraphicsObjects()
	{
		glDeleteProgram(mShader);
		glDeleteBuffers(1, &mVb);
		glDeleteBuffers(1, &mIb);
		glDeleteVertexArrays(1, &mVa);

		delete mDefaultQuad;
	}

	void Renderer::DrawQuad(vec2 size, vec2 position, Color color)
	{	
		glUseProgram(mShader);
		glBindVertexArray(mVa);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb);

		glm::mat4 transformation(1.0f);
		transformation *= glm::translate(transformation, Vector3(position, 0));
		transformation *= glm::toMat4(glm::quat(glm::radians(Vector3(0))));
		transformation *= glm::scale(transformation, Vector3(size, 1));
		glm::mat4 mp = ProjectionMatrix * transformation;

		glUniformMatrix4fv(Shaders::GetUniformLocation(mShader, "u_MP"), 1, GL_FALSE, &mp[0][0]);
		glUniform4f(Shaders::GetUniformLocation(mShader, "u_Color"), color.r, color.g, color.b, color.a);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}