#include "Renderer.h"

#include "Resources/AssetDatabase.h"

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
		if (mInitialized) DeinitializeGraphics();
	}

	ReturnCode Renderer::InitializeGraphics(vec2 size, const std::string&& title)
	{
		if (!InitializeContext()) return RETURN_CODE_ERROR;
		
		GLFWwindow* window = CreateWindow(size, std::move(title));
		if (!window) return RETURN_CODE_ERROR;
		
		mContext = GraphicsContext(window);

		if (!InitializeGraphicsLibrary()) return RETURN_CODE_ERROR;
		printf("GL version: %s\n", glGetString(GL_VERSION));

		ConfigureMiscelaneousParameters();

		mContext.InitializeWindowResizing();
		mContext.InitializeInput();

		// CreateGraphicsObjects();
		// InitializeGraphicsObjects();

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
		return true;
	}

	void Renderer::UpdateProjectionMatrix(int width, int height)
	{
		// TODO: Move world zoom to camera object
		float worldZoom = 400.0f;
		float halfZoom = worldZoom / 2;
		float aspect = ((float)height) / ((float)width);
		float halfScaledAspect = aspect * halfZoom;

		ProjectionMatrix = glm::ortho(-halfZoom, halfZoom, -halfScaledAspect, halfScaledAspect);
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
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		// glEnable(GL_DEPTH_TEST); // TODO: for some reason it doesn't work
		// glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::DeinitializeGraphics()
	{
		mInitialized = false;

		glfwDestroyWindow(mContext.Window());
		glfwTerminate();
	}

	// void Renderer::CreateGraphicsObjects()
	// {
	// 	const std::string* data = Shaders::LoadShaderFile("res/shaders/Basic.shader");
//
	// 	if (data && data->length() > 0)
	// 	{
	// 		auto [vertexShaderSource, fragmentShaderSource] = Shaders::ParseShader(data);
	// 		mShader = Shaders::CreateShader(vertexShaderSource, fragmentShaderSource);
	// 		delete data;
	// 	}
//
	// 	glGenBuffers(1, &mVb);
	// 	glGenBuffers(1, &mIb);
	// 	glGenVertexArrays(1, &mVa);
	// }
//
	// Mesh* Renderer::CreateDefaultQuad()
	// {
	// 	const size_t verticesCount = 4;
	// 	Vertex* vertices = new Vertex[verticesCount]
	// 	{
	// 		{-0.5f, -0.5f, 0.0f, 0.0f},
	// 		{-0.5f, 0.5f, 0.0f, 1.0f},
	// 		{0.5f, 0.5f, 1.0f, 1.0f},
	// 		{0.5f, -0.5f, 1.0f, 0.0f},
	// 	};
//
	// 	const size_t indicesCount = 6;
	// 	unsigned int* indices = new unsigned int[indicesCount] {0, 1, 2, 0, 2, 3};
//
	// 	Mesh* mesh = new Mesh(vertices, verticesCount, indices, indicesCount);
//
	// 	return mesh;
	// }
//
	// void Renderer::InitializeGraphicsObjects()
	// {
	// 	glUseProgram(mShader);
	// 	glBindVertexArray(mVa);
	// 	glBindBuffer(GL_ARRAY_BUFFER, mVb);
	// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb);
//
	// 	mDefaultQuad = CreateDefaultQuad();
//		
	// 	glBufferData(GL_ARRAY_BUFFER, mDefaultQuad->VerticesCount * sizeof(Vertex),
	// 		mDefaultQuad->Vertices, GL_STATIC_DRAW);
	// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mDefaultQuad->IndicesCount * sizeof(unsigned int),
	// 		mDefaultQuad->Indices, GL_STATIC_DRAW);
//
	// 	for (auto &&l : Vertex::Layouts)
	// 	{
	// 		glEnableVertexAttribArray(l.Id);
	// 		glVertexAttribPointer(l.Id, l.ElementCount, l.Type,
	// 			l.Normalize, l.VertexSize, (const void*)l.Offset);
	// 	}
//
	// 	glBindVertexArray(0);
	// 	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// 	glUseProgram(0);
	// }
//
	// void Renderer::DestroyGraphicsObjects()
	// {
	// 	glDeleteProgram(mShader);
	// 	glDeleteBuffers(1, &mVb);
	// 	glDeleteBuffers(1, &mIb);
	// 	glDeleteVertexArrays(1, &mVa);
//
	// 	delete mDefaultQuad;
	// }
//
	// void Renderer::DrawQuad(vec2 size, vec2 position, col4 color, const Texture* texture)
	// {	
	// 	glUseProgram(mShader);
	// 	glBindVertexArray(mVa);
	// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb);
//
	// 	glm::mat4 transformation(1.0f);
	// 	transformation *= glm::translate(vec3(position, 0));
	// 	transformation *= glm::toMat4(glm::quat(glm::radians(vec3(0))));
	// 	transformation *= glm::scale(vec3(size, 1));
//
	// 	glm::mat4 mp = ProjectionMatrix * transformation;
//
	// 	if (texture) 
	// 	{
	// 		texture->Bind(texture->Slot);
	// 		glUniform1i(Shaders::GetUniformLocation(mShader, "u_Texture"), texture->Slot);
	// 	}
	// 	else
	// 	{
	// 		glBindTexture(GL_TEXTURE_2D, 0);
	// 	}
//
	// 	glUniformMatrix4fv(Shaders::GetUniformLocation(mShader, "u_MP"), 1, GL_FALSE, &mp[0][0]);
	// 	glUniform4f(Shaders::GetUniformLocation(mShader, "u_Color"), color.r, color.g, color.b, color.a);
//
	// 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//
	// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// 	glBindVertexArray(0);
	// 	glUseProgram(0);
	// }

	unsigned int Renderer::GetTextureSlot()
	{
		return mLastTextureSlot++;
	}

	Mesh* Renderer::GetBasicQuad()
	{
		// TODO: load default quad mesh
		Mesh* mesh = Resources::AssetDatabase::GetAsset<Mesh>("models/quad.obj");

		return mesh;
	}

	void Renderer::Clear(col4 color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Draw(const IndexBuffer& ib, const VertexArray& va, const Shader* sh) const
	{
		sh->Bind();
		va.Bind();
		ib.Bind();
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
		ib.Unbind();
		va.Unbind();
		sh->Unbind();
	}

	void Renderer::PostRender()
	{
		glfwSwapBuffers(mContext.Window());

		static double previousTime = 0;
		double currentTime = glfwGetTime(); 
		DeltaTime = currentTime - previousTime;
		previousTime = currentTime;
	}
}