#pragma once

#include <string>
#include <unordered_map>
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Components/Renderer.h"

namespace GameObjects
{
	class GameObject
	{
	protected:
		std::string mName;
		Renderer* mRenderer = nullptr;
		Transform* mTransform;
		std::unordered_map<size_t, Component*> mComponents;
		std::vector<Component*> mComponentList;

	public:
		GameObject(const std::string&& name);
		~GameObject();

		virtual void Update() {}; // remove this. the components should have updates

		void UpdateComponents();

		inline const std::string& GetName() const { return mName; };
		inline void SetName(const std::string& value) { mName = value; };

		inline Transform* GetTransform() const { return mTransform; };

		inline Renderer* GetRenderer() const { return mRenderer; };

		void AddComponent(Component* component);
		Component* GetComponent(size_t typeHash);
	};
}