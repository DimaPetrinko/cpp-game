#pragma once

#include <string>
#include "Graphics/GL.h"
#include "Graphics/GraphicsObject.h"
#include "Resources/Asset.h"

namespace Graphics
{
	class Texture : public GraphicsObject, public Resources::Asset
	{
	public:
		unsigned int Slot;
		vec2 Tiling;
	private:
		int mWidth, mHeight, mBPP;
	
	public:
		Texture(const std::string& filePath);
		~Texture();

		void Bind() const override;
		void BindSlot() const;
		void Unbind() const override;
	};
}