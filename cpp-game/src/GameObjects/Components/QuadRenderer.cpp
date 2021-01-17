#include "QuadRenderer.h"
#include "GameObjects/GameObject.h"

namespace GameObjects
{
	QuadRenderer::QuadRenderer(GameObject* gameObject, Color color) : Renderer(gameObject), mColor(color) {}

	QuadRenderer::~QuadRenderer() {}

	void QuadRenderer::Update() {}

	void QuadRenderer::Render(Graphics::Renderer* renderer)
	{
		vec2 size = mGameObject->GetTransform()->GetSize();
		vec2 position = mGameObject->GetTransform()->GetPosition();
		renderer->DrawQuad(size, position, mColor);
	}

	std::vector<size_t>&& QuadRenderer::GetTypeHashes()
	{
		if (mTypeHashes.size() != 2) mTypeHashes.clear();
		if (mTypeHashes.size() == 0)
		{
			mTypeHashes.push_back(typeid(GameObjects::QuadRenderer).hash_code());
			mTypeHashes.push_back(typeid(GameObjects::Renderer).hash_code());
		}
		return std::move(mTypeHashes);
	}
}