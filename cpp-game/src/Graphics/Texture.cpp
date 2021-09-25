#include "Texture.h"

#include "Graphics/Renderer.h"
#include "stb_image/stb_image.h"

namespace Graphics
{
	Texture::Texture(const std::string& filePath)
	{
		Slot = Renderer::Instance()->GetTextureSlot();
		Tiling = vec2(1, 1);
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mBPP, 4);

		if (!data)
		{
			std::cout << "Could not load texture at " << filePath << std::endl;
			return;
		}

		glGenTextures(1, &mRendererId);

		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		Unbind();

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		if (mRendererId == 0) return;
		glDeleteTextures(1, &mRendererId);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mRendererId);
	}

	void Texture::BindSlot() const
	{
		glActiveTexture(GL_TEXTURE0 + Slot);
		Bind();
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}