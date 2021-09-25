// #include "Texture.h"

// #include "Graphics/Renderer.h"

// #include "stb_image/stb_image.h"

// namespace Graphics
// {
// 	Texture::Texture(const std::string& filePath)
// 	{
// 		Slot = Renderer::Instance()->GetTextureSlot();
// 		stbi_set_flip_vertically_on_load(1);
// 		unsigned char* data = stbi_load(filePath.c_str(), &Width, &Height, &mBPP, 4);

// 		if (!data)
// 		{
// 			std::cout << "Could not load texture at " << filePath << std::endl;
// 			return;
// 		}

// 		glGenTextures(1, &mRendererId);

// 		glEnable(GL_BLEND);
// 		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 		Bind();
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
// 		Unbind();

// 		stbi_image_free(data);
// 	}

// 	Texture::~Texture()
// 	{
// 		if (mRendererId == 0) return;
// 		glDeleteTextures(1, &mRendererId);
// 	}

// 	void Texture::Bind() const
// 	{
// 		glBindTexture(GL_TEXTURE_2D, mRendererId);
// 	}

// 	void Texture::Bind(unsigned int slot) const
// 	{
// 		glActiveTexture(GL_TEXTURE0 + slot);
// 		Bind();
// 	}

// 	void Texture::Unbind() const
// 	{
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 	}
// }