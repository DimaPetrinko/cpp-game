// #pragma once

// #include "Graphics/GL.h"

// namespace Graphics
// {
// 	struct Layout
// 	{
// 	public:
// 		int Id;
// 		int ElementCount;
// 		int Type;
// 		int Normalize;
// 		int VertexSize;
// 		int Offset;

// 	public:
// 		Layout(int id, int elementCount, int type, int normalize, int vertexSize, int offset);
// 		~Layout();
// 	};

// 	struct Vertex
// 	{
// 	public:
// 		vec2 Position;
// 		vec2 TextureCoordinates;
// 		const static Layout Layouts[2];

// 	public:
// 		Vertex(vec2 position, vec2 textureCoordinates);
// 		Vertex(float positionX, float positionY, float textureCoordinateX, float textureCoordinateY);
// 	};

// 	class Mesh
// 	{
// 	public:
// 		Vertex* Vertices;
// 		size_t VerticesCount;
// 		unsigned int* Indices;
// 		size_t IndicesCount;

// 	public:
// 		Mesh();
// 		Mesh(Vertex* vertices, size_t verticesCount, unsigned int* indices, size_t indicesCount);
// 		~Mesh();
// 	};
// }