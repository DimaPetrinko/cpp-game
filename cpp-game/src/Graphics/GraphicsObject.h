#pragma once

namespace Graphics
{
	class GraphicsObject
	{
	protected:
		unsigned int mRendererId = 0;
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}