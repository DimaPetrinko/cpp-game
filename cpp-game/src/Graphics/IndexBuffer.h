#pragma once

#include "Graphics/GraphicsObject.h"

namespace Graphics
{
	class IndexBuffer final : public GraphicsObject
	{
	private:
		unsigned int mCount{};
	public:
		IndexBuffer() {};
		IndexBuffer(bool glInitialized);
		~IndexBuffer();

		void SetData(const unsigned int* data, const unsigned int count);
		void Bind() const override;
		void Unbind() const override;

		inline unsigned int GetCount() const { return mCount; }
	};
}