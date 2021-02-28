#pragma once

#include "Object.h"
#include "Components/BoxRenderer.h"

struct Player : public Object
{
public:
	vec2 Acceleration;
	vec2 Velocity;
	float Drag;
	float MovementSpeed;
	float JumpForce;
	float JumpsAllowed;
	float MaxSpeed;
	float MidAirInputDampening;
	float InactiveDrag;
	bool InAir;

private:
	float mPreviousSpaceKeyState;
	float mJumpsLeft;

public:
	Player(BoxRenderer* renderer, float movementSpeed);
	Player(vec2 position, BoxRenderer* renderer, float movementSpeed);

	void ChangeVelocity(vec2 amount);
	void Move(vec2 movement);
	void UpdateLogic(GLFWwindow* window);
	void UpdatePhysics();

private:
	void HandleJump(int key);
};