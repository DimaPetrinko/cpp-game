#pragma once

#include "Component.h"
#include "Graphics/Renderer.h"

namespace GameObjects
{
	class Renderer : public Component
	{
	public:
		Renderer(GameObject* gameObject);
		virtual ~Renderer();
		
		virtual void Render(Graphics::Renderer* renderer) = 0;
	};
}