#pragma once

#include "Object.h"
#include "Components/BoxRenderer.h"

struct Player : public Object
{
public:
	float MovementSpeed;
	float MaxSpeed;
	float MidAirInputDampening;
	float InactiveDrag;
	
	float JumpForce;
	float JumpsAllowed;

private:
	vec2 mAcceleration;
	vec2 mVelocity;
	float mDrag;

	float mPreviousSpaceKeyState;
	float mJumpsLeft;
	bool mInAir;

public:
	Player(BoxRenderer* renderer, float movementSpeed);
	Player(vec2 position, BoxRenderer* renderer, float movementSpeed);

	void Move(vec2 movement);
	void UpdateLogic(GLFWwindow* window);
	
	void UpdatePhysics();
	void ResolveCollision(vec2 resolution);

	void AddVelocity(vec2 amount);
	void SetVelocity(vec2 newVelocity);
	vec2 GetVelocity() const;

private:
	void HandleJump(int key);
};