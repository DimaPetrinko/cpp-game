#include "VertexBuffer.h"

#include "Graphics/GL.h"

namespace Graphics
{
	VertexBuffer::VertexBuffer(bool glInitialized)
	{
		if (!glInitialized) return;
		glGenBuffers(1, &mRendererId);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (mRendererId == 0) return;
		glDeleteBuffers(1, &mRendererId);
	}

	void VertexBuffer::SetData(const void* data, const unsigned int size)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, size of data we're pushing, the data itself, can be static, dynamic.. see documentation);
		Unbind();
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
