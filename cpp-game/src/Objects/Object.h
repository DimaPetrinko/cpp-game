#pragma once

#include "Utils/Vector.h"
#include "Components/ObjectRenderer.h"

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

	ObjectRenderer* GetRenderer() const;
};