// #include "GrahicsStructs.h"

// namespace Graphics
// {
// 	Layout::Layout(int id, int elementCount, int type, int normalize, int vertexSize, int offset)
// 		: Id(id), ElementCount(elementCount), Type(type), Normalize(normalize),
// 			VertexSize(vertexSize), Offset(offset) {}
// 	Layout::~Layout() {}

// 	Vertex::Vertex(vec2 position, vec2 textureCoordinates)
// 		: Position(position), TextureCoordinates(textureCoordinates) {}
// 	Vertex::Vertex(float positionX, float positionY, float textureCoordinateX, float textureCoordinateY)
// 		: Position({positionX, positionY}), TextureCoordinates({textureCoordinateX, textureCoordinateY}) {}

// 	const Layout Vertex::Layouts[2] = {Layout(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0),
// 			Layout(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 2 * sizeof(float))};

// 	Mesh::Mesh() : Vertices(), Indices() {}
// 	Mesh::Mesh(Vertex* vertices, size_t verticesCount, unsigned int* indices, size_t indicesCount)
// 		: Vertices(vertices), VerticesCount(verticesCount), Indices(indices), IndicesCount(indicesCount) {}
// 	Mesh::~Mesh()
// 	{
// 		delete[] Vertices;
// 		delete[] Indices;
// 	}
// }