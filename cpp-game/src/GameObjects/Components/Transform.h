#pragma once

#include "Component.h"
#include "Utilities/Vectors.h"

namespace GameObjects
{
	class Transform : public Component
	{
	private:
		vec2 mPosition;
		vec2 mSize;
	public:
		Transform(GameObject* gameObject);
		~Transform();
		
		void Update() override;

		std::vector<size_t>&& GetTypeHashes() override;

		inline vec2 GetPosition() const { return mPosition; };
		inline void SetPosition(vec2 value) { mPosition = value; };

		inline vec2 GetSize() const { return mSize; };
		inline void SetSize(vec2 value) { mSize = value; };
	};
}