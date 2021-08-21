#pragma once

#include "GL.h"

namespace Graphics
{
	class Texture
	{
	public:
		unsigned int Slot;
		int Width;
		int Height;
	private:
		GLuint mRendererId;
		int mBPP;

	public:
		Texture(const std::string& filePath);
		~Texture();

		void Bind() const;
		void Bind(unsigned int slot) const;
		void Unbind() const;
	};
}