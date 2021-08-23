#pragma once

#include "Object.h"
#include "Components/BoxRenderer.h"
#include "Graphics/Texture.h"

namespace Objects
{
	class Player : public Object
	{
	public:
		float MovementSpeed;
		float MaxSpeed;
		float MidAirInputDampening;
		float InactiveDrag;
		
		float JumpForce;
		float JumpsAllowed;

	private:
		Graphics::Texture* mTexture;
		vec2 mAcceleration;
		vec2 mVelocity;
		float mDrag;

		int mPreviousSpaceKeyState;
		float mJumpsLeft;
		bool mInAir;

	public:
		Player(BoxRenderer* renderer, float movementSpeed, const std::string& texturePath);
		Player(vec2 position, BoxRenderer* renderer, float movementSpeed, const std::string& texturePath);
		~Player();

		void Move(vec2 movement);
		void UpdateLogic(Graphics::GraphicsContext* context) override;
	
		void UpdatePhysics() override;
		void ResolveCollision(vec2 resolution) override;

		void AddVelocity(vec2 amount);
		void SetVelocity(vec2 newVelocity);
		vec2 GetVelocity() const;

	private:
		void HandleJump(int key);
	};
}