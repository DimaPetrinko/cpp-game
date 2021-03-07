#pragma once

#include "Utils/Vector.h"
#include "Components/ObjectRenderer.h"
#include "Graphics/GraphicsContext.h"

class Object
{
public:
	vec2 Position;

protected:
	ObjectRenderer* mRenderer;

public:
	Object(ObjectRenderer* renderer);
	Object(vec2 position, ObjectRenderer* renderer);
	~Object();

	virtual void UpdateLogic(Graphics::GraphicsContext* context);
	virtual void UpdatePhysics();
	virtual void ResolveCollision(vec2 resolution);

	ObjectRenderer* GetRenderer() const;
};