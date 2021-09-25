#pragma once

#include "Utils/Vector.h"
#include "Objects/Components/TransformComponent.h"
#include "Objects/Components/ObjectRenderer.h"
#include "Graphics/GraphicsContext.h"

namespace Objects
{
	class Object
	{
	public:
		Components::TransformComponent Transform;
	protected:
		Components::ObjectRenderer* mRenderer; // TODO: maybe make this not a pointer?

	public:
		Object(Components::ObjectRenderer* renderer);
		Object(vec3 position, Components::ObjectRenderer* renderer);
		~Object();

		virtual void UpdateLogic(Graphics::GraphicsContext* context);
		virtual void UpdatePhysics();
		virtual void ResolveCollision(vec2 resolution);

		Components::ObjectRenderer* GetRenderer() const;
	};
}