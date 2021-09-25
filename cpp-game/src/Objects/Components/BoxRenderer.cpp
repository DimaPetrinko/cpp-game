#include "BoxRenderer.h"

#include "Graphics/Renderer.h"

namespace Objects::Components
{
	BoxRenderer::BoxRenderer(vec2 size, Graphics::Texture* texture, Graphics::Shader* shader)
		: ObjectRenderer(Graphics::Renderer::GetBasicQuad(), texture, shader),
		Size(size),
		Color(1,1,1,1) {}

	void BoxRenderer::Draw() const
	{
		Graphics::Renderer* renderer = Graphics::Renderer::Instance();
		glm::mat4 m = mOwner->Transform.GetMatrix();
		glm::mat4 mvp = renderer->ProjectionMatrix
			// * renderer->ViewMatrix
			* m;

		mShader->Bind();
		if (mTexture)
		{
			mTexture->BindSlot();
			mShader->SetUniform2f("u_TextureTiling", mTexture->Tiling.x, mTexture->Tiling.y);
			mShader->SetUniform1i("u_Texture", mTexture->Slot);
		}
		mShader->SetUniform4f("u_Color", Color.r, Color.g, Color.b, Color.a);
		mShader->SetUniformMatrix4fv("u_Mvp", &mvp[0][0]);
		// mShader->SetUniformMatrix4fv("u_M", &m[0][0]);

		renderer->Draw(*mMesh->GetIB(), *mMesh->GetVA(), mShader);
		
		if (mTexture) mTexture->Unbind();
	}

	Bounds BoxRenderer::GetBounds() const
	{
		return Bounds(mOwner->Transform.Position, mOwner->Transform.Scale);
	}

	void BoxRenderer::SetOwner(Object* owner)
	{
		ObjectRenderer::SetOwner(owner);
		mOwner->Transform.Scale = {Size, 1};
	}
}