#include "IndexBuffer.h"

#include "Graphics/GL.h"

namespace Graphics
{
	IndexBuffer::IndexBuffer(bool glInitialized)
	{
		if (!glInitialized) return;
		glGenBuffers(1, &mRendererId);
	}

	IndexBuffer::~IndexBuffer()
	{
		if (mRendererId == 0) return;
		glDeleteBuffers(1, &mRendererId);
	}

	void IndexBuffer::SetData(const unsigned int* data, const unsigned int count)
	{
		Bind();
		this->mCount = count;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, size of data we're pushing, the data itself, can be static, dynamic.. see documentation);
		Unbind();
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
