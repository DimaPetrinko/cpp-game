#include "Player.h"

#include <iostream>
#include <algorithm>
#include "Utils/Physics.h"

namespace Objects
{
	Player::Player(BoxRenderer* renderer, float movementSpeed, const std::string& texturePath)
		: Player({0,0}, renderer, movementSpeed, texturePath) {}

	Player::Player(vec2 position, BoxRenderer* renderer, float movementSpeed, const std::string& texturePath)
		: Object(position, renderer), mDrag(Physics::DefaultDrag),
			mAcceleration(0,0), mVelocity(0,0)
	{
		if (movementSpeed <= 0) movementSpeed = 0.05f;
		MovementSpeed = movementSpeed;

		JumpsAllowed = 2;
		JumpForce = 250;
		MaxSpeed = 200;
		MidAirInputDampening = 0.4f;
		InactiveDrag = 0.1f;

		mJumpsLeft = 0;
		mInAir = false;
		mPreviousSpaceKeyState = 0;

		mTexture = new Graphics::Texture(texturePath);
		mRenderer->SetTexture(mTexture);
	}

	Player::~Player()
	{
		if (mTexture) delete mTexture;
	}

	void Player::Move(vec2 movement)
	{
		movement *= MovementSpeed * Physics::DeltaTime;
		AddVelocity(movement);
	}

	void Player::HandleJump(int key)
	{
		if (!mInAir) mJumpsLeft = JumpsAllowed;

		if (mJumpsLeft > 0)
		{
			if (key == GLFW_PRESS && mPreviousSpaceKeyState != GLFW_PRESS)
			{
				mJumpsLeft--;
				AddVelocity(vec2{0, JumpForce - mVelocity.y});
			}
			mPreviousSpaceKeyState = key;
		}
	}

	void Player::ResolveCollision(vec2 resolution)
	{
		Position += resolution;
		AddVelocity(resolution / Physics::DeltaTime);
		mInAir = resolution.x == 0 && resolution.y == 0;
	}

	void Player::UpdateLogic(Graphics::GraphicsContext* context)
	{
		vec2 movement = {0,0};
		if (context->GetKey(GLFW_KEY_D)) movement.x += 1.0f;
		if (context->GetKey(GLFW_KEY_A)) movement.x -= 1.0f;

		bool movementPresent = movement.x != 0;

		if (std::abs(mVelocity.x) > MaxSpeed) movement = {0,0};

		if (!movementPresent && !mInAir) AddVelocity(vec2(-mVelocity.x * InactiveDrag, 0)); // This is essentially friction

		HandleJump(context->GetKey(GLFW_KEY_SPACE));

		if (mInAir)
		{
			movement *= (1 - MidAirInputDampening);
		}

		Move(movement);
	}

	#define COUT_V(v) v.x << ", " << v.y

	void Player::UpdatePhysics()
	{
		mAcceleration += Physics::Gravity;
		mVelocity += mAcceleration;
		mVelocity.x = std::clamp(mVelocity.x, -Physics::TerminalVelocity, Physics::TerminalVelocity);
		mVelocity.y = std::clamp(mVelocity.y, -Physics::TerminalVelocity, Physics::TerminalVelocity);
		Position += mVelocity * Physics::DeltaTime;

		// std::cout << "Physics update:\n  Position: " << COUT_V(Position)
		// 	<< ";\n  Velocity: " << COUT_V(mVelocity)
		// 	<< ";\n  Acceleration: " << COUT_V(mAcceleration)
		// 	<< ";\n  Drag: " << mDrag << ";\n\n";

		mAcceleration = {0,0};
		mVelocity *= (1 - mDrag);
	}

	void Player::AddVelocity(vec2 amount)
	{
		mAcceleration += amount;
	}

	void Player::SetVelocity(vec2 newVelocity)
	{
		vec2 velocityDelta = newVelocity - mVelocity;
		AddVelocity(velocityDelta);
	}

	vec2 Player::GetVelocity() const
	{
		return mVelocity;
	}
}