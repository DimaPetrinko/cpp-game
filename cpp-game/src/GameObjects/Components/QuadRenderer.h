#pragma once

#include "Renderer.h"
#include "Utilities/Vectors.h"
#include "Graphics/Renderer.h"

namespace GameObjects
{
	class QuadRenderer : public Renderer
	{
	private:
		Color mColor;
	public:
		QuadRenderer(GameObject* gameObject, Color color);
		~QuadRenderer() override;
		
		void Update() override;

		void Render(Graphics::Renderer* renderer) override;

		std::vector<size_t>&& GetTypeHashes() override;

		inline vec2 GetColor() const { return mColor; };
		inline void SetColor(Color value) { mColor = value; };
	};
}