#include "GameObject.h"
#include <typeinfo>

namespace GameObjects
{
	GameObject::GameObject(const std::string&& name) : mName(std::move(name))
	{
		mTransform = new Transform(this);
		AddComponent(mTransform);
	}
		
	GameObject::~GameObject()
	{
		mComponents.clear();

		for (int i = 0; i < mComponentList.size(); i++)
		{
			delete mComponentList[i];
		}
		mComponentList.clear();
	}

	void GameObject::UpdateComponents() {}

	void GameObject::AddComponent(Component* component)
	{
		for (auto &&t : component->GetTypeHashes())
		{
			if (mTransform == nullptr && t == typeid(GameObjects::Transform).hash_code())
			{
				std::cout << "[Error] Adding another Transform is not allowed!\n";
				return;
			}

			auto search = mComponents.find(t);
			if (search != mComponents.end())
			{
				std::cout << "[Error] This component has already been added!\n";
				return;
			}

			if (t == typeid(GameObjects::Renderer).hash_code())
			{
				mRenderer = (GameObjects::Renderer*)component;
			}

			mComponents[t] = component;
		}
		mComponentList.push_back(component);
	}

	Component* GameObject::GetComponent(size_t typeHash)
	{
		auto result = mComponents.find(typeHash);
		if (result == mComponents.end()) return nullptr;
		return result->second;
	}
}