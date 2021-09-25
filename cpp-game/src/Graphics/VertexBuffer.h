#pragma once

#include "Graphics/GraphicsObject.h"

namespace Graphics
{
	class VertexBuffer final : public GraphicsObject
	{
	public:
		VertexBuffer() {};
		VertexBuffer(bool glInitialized);
		~VertexBuffer();

		void SetData(const void* data, const unsigned int size);
		void Bind() const override;
		void Unbind() const override;
	};
}
