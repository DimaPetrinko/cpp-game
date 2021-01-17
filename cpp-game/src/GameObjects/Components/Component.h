#pragma once

#include <vector>

namespace GameObjects
{
	class GameObject;

	class Component
	{
	protected:
		GameObject* mGameObject;
		std::vector<size_t> mTypeHashes;
	public:
		Component(GameObject* gameObject);
		virtual ~Component() = 0;

		virtual void Update() = 0;
		
		virtual std::vector<size_t>&& GetTypeHashes() = 0;

		inline GameObject* GetGameObject() const { return mGameObject; };
	};
}