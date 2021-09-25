#pragma once

#include <string>
#include "Resources/Asset.h"
#include "Graphics/Vertex.h"
#include "Graphics/Triangle.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/IndexBuffer.h"

namespace Graphics
{
	class Mesh : public Resources::Asset
	{
	private:
		std::string mName {""};
		VertexBuffer mVb; // maybe move to renderer for batching?
		IndexBuffer mIb;
		VertexArray mVa;
	public:
		Mesh(const std::string& filePath);
		~Mesh();

		VertexArray* GetVA() { return &mVa; }
		IndexBuffer* GetIB() { return &mIb; }
	};
}