#include "BoxRenderer.h"

#include "Graphics/Renderer.h"

namespace Objects
{
	BoxRenderer::BoxRenderer(vec2 size, col4 color)
	 : ObjectRenderer(size), Color(color) {}

	void BoxRenderer::Draw() const
	{
		Graphics::Renderer::Instance()->DrawQuad(Size, mOwner->Position, Color, mTexture);
	}

	Bounds BoxRenderer::GetBounds() const
	{
		return Bounds(mOwner->Position, Size);
	}
}