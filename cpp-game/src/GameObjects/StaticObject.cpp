#include "StaticObject.h"

namespace GameObjects
{
	StaticObject::StaticObject(const std::string&& name, Color color) : GameObject(std::move(name), color) {}

	StaticObject::~StaticObject() {}

	void StaticObject::Update() {}
}