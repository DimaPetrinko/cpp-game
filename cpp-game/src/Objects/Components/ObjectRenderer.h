#pragma once

#include "Utils/Bounds.h"

class Object;

class ObjectRenderer
{
public:
	vec2 Size;

protected:
	const Object* mOwner;

public:
	ObjectRenderer(vec2 size);
	~ObjectRenderer();

	void SetOwner(const Object* owner);
	virtual void Draw() const = 0;
	virtual Bounds GetBounds() const = 0;
};