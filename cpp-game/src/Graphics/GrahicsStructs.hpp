#pragma once

#include "GL.h"

namespace Graphics
{
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
}