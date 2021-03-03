#include "Player.h"

#include <iostream>
#include <algorithm>
#include "Utils/Physics.h"

Player::Player(BoxRenderer* renderer, float movementSpeed) : Player({0,0}, renderer, movementSpeed) {}

Player::Player(vec2 position, BoxRenderer* renderer, float movementSpeed)
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

void Player::UpdateLogic(GLFWwindow* window)
{
	vec2 movement = {0,0};
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movement.x += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movement.x -= 1.0f;

	bool movementPresent = movement.x != 0;

	if (std::abs(mVelocity.x) > MaxSpeed) movement = {0,0};

	if (!movementPresent && !mInAir) AddVelocity(vec2(-mVelocity.x * InactiveDrag, 0)); // This is essentially friction

	HandleJump(glfwGetKey(window, GLFW_KEY_SPACE));

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

	std::cout << "Physics update:\n  Position: " << COUT_V(Position)
		<< ";\n  Velocity: " << COUT_V(mVelocity)
		<< ";\n  Acceleration: " << COUT_V(mAcceleration)
		<< ";\n  Drag: " << mDrag << ";\n\n";

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