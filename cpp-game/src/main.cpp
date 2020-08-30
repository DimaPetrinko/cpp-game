#include <iostream>
#include "Graphics/GL.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shaders.hpp"

Renderer* mRenderer;
GraphicsContext* mContext;
GLuint mVa, mIb, mVb, mShader;
Vector2 mMousePosition;
Vector2 mPlayerPosition;
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
	Vector2 Position;
	Vector2 TextureCoordinates;
	const static Layout Layouts[];

public:
	Vertex(Vector2 position, Vector2 textureCoordinates)
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

void DrawQuad(Vector2 size, Vector2 position, Color color)
{	
	GLCall(glUseProgram(mShader));
	GLCall(glBindVertexArray(mVa));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIb));

	glm::mat4 transformation(1.0f);
	transformation *= glm::translate(transformation, Vector3(position, 0));
	transformation *= glm::toMat4(glm::quat(glm::radians(Vector3(0))));
	transformation *= glm::scale(transformation, Vector3(size, 1));
	glm::mat4 mp = mRenderer->ProjectionMatrix * transformation;

	GLCall(glUniformMatrix4fv(GetUniformLocation(mShader, "u_MP"), 1, GL_FALSE, &mp[0][0]));
	GLCall(glUniform4f(GetUniformLocation(mShader, "u_Color"), color.r, color.g, color.b, color.a));

	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
}

void Render()
{
	mRenderer->Clear(Color(0.3f, 0.3f, 0.4f, 1.0f));

	DrawQuad({100, 100}, Vector2(1280.0f / 2, 720.0f / 2), Color(0.5f, 0.2f, 0.2f, 0.0f));
	DrawQuad({100, 100}, mPlayerPosition, Color(0.2f, 0.2f, 0.5f, 0.0f));

	mRenderer->FinishFrame();
}

void PollInput()
{
	mContext->UpdateInput();

	mMousePosition = mContext->GetMousePosition();

	float currentMultiplier = 1.0f;

	if (mContext->GetKeyDown(GLFW_KEY_RIGHT_SHIFT) || mContext->GetKeyDown(GLFW_KEY_LEFT_SHIFT))
		currentMultiplier = mShiftMultiplier;
	else currentMultiplier = 1.0f;
	if (mContext->GetKeyDown(GLFW_KEY_W)) mPlayerPosition.y += mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKeyDown(GLFW_KEY_S)) mPlayerPosition.y -= mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKeyDown(GLFW_KEY_D)) mPlayerPosition.x += mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKeyDown(GLFW_KEY_A)) mPlayerPosition.x -= mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKey(GLFW_KEY_ESCAPE)) mContext->CloseWindow();
}

void UpdateLogic()
{
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

int main()
{
	mRenderer = new Renderer();
	int successCode = mRenderer->InitializeGraphics(Vector2(1280, 720), "cpp-game");
	if (successCode != 1) return successCode;

	mContext = mRenderer->Context();

	CreateGraphicsObjects();
	InitializeGraphicsObjects();

	while (!mContext->ShouldWindowClose())
	{
		Render();
		PollInput();
		UpdateLogic();
	}

	DeinitializeGraphicsObjects();
	mRenderer->DeinitializeGraphics();
	
	delete mRenderer;
	return 0;
}