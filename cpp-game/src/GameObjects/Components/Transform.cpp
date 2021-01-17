#include "Transform.h"

namespace GameObjects
{
	Transform::Transform(GameObject* gameObject) : Component(gameObject), mPosition(), mSize{1,1} {}

	Transform::~Transform() {}

	void Transform::Update() {}

	std::vector<size_t>&& Transform::GetTypeHashes()
	{
		if (mTypeHashes.size() != 1) mTypeHashes.clear();
		if (mTypeHashes.size() == 0)
		{
			mTypeHashes.push_back(typeid(GameObjects::Transform).hash_code());
		}
		return std::move(mTypeHashes);
	}
}