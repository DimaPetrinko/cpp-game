#include "Player.h"

#include <iostream>
#include <algorithm>
#include "Utils/Physics.h"

Player::Player(BoxRenderer* renderer, float movementSpeed) : Player({0,0}, renderer, movementSpeed) {}

Player::Player(vec2 position, BoxRenderer* renderer, float movementSpeed)
	: Object(position, renderer), Drag(Physics::DefaultDrag),
		Acceleration(0,0), Velocity(0,0)
{
	if (movementSpeed <= 0) movementSpeed = 0.05f;
	MovementSpeed = movementSpeed;

	JumpsAllowed = 2;
	JumpForce = 250;
	MaxSpeed = 200;
	MidAirInputDampening = 0.4f;
	InactiveDrag = 0.1f;
}

void Player::ChangeVelocity(vec2 amount)
{
	Acceleration += amount;
}

void Player::Move(vec2 movement)
{
	movement *= MovementSpeed * Physics::DeltaTime;
	ChangeVelocity(movement);
}

void Player::UpdateLogic(GLFWwindow* window)
{
	vec2 movement = {0,0};
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movement.x += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movement.x -= 1.0f;

	bool movementPresent = movement.x != 0;

	if (std::abs(Velocity.x) > MaxSpeed) movement = {0,0};

	if (!movementPresent && !InAir) ChangeVelocity(vec2(-Velocity.x * InactiveDrag, 0));

	HandleJump(glfwGetKey(window, GLFW_KEY_SPACE));

	if (InAir)
	{
		movement *= (1 - MidAirInputDampening);
	}

	Move(movement);
}

#define COUT_V(v) v.x << ", " << v.y

void Player::UpdatePhysics()
{
	Acceleration += Physics::Gravity;
	Velocity += Acceleration;
	Velocity.x = std::clamp(Velocity.x, -Physics::TerminalVelocity, Physics::TerminalVelocity);
	Velocity.y = std::clamp(Velocity.y, -Physics::TerminalVelocity, Physics::TerminalVelocity);
	Position += Velocity * Physics::DeltaTime;

	std::cout << "Physics update:\n  Position: " << COUT_V(Position)
		<< ";\n  Velocity: " << COUT_V(Velocity)
		<< ";\n  Acceleration: " << COUT_V(Acceleration)
		<< ";\n  Drag: " << Drag << ";\n\n";

	Acceleration = {0,0};
	Velocity *= (1 - Drag);
}

void Player::HandleJump(int key)
{
	if (!InAir) mJumpsLeft = JumpsAllowed;

	if (mJumpsLeft > 0)
	{
		if (key == GLFW_PRESS && mPreviousSpaceKeyState != GLFW_PRESS)
		{
			mJumpsLeft--;
			Velocity += vec2{0, JumpForce};
		}
		mPreviousSpaceKeyState = key;
	}
}