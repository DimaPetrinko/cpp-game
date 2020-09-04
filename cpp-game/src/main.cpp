#include <iostream>
#include "Graphics/GL.h"
#include "Graphics/Renderer.h"

Graphics::Renderer* mRenderer;
Graphics::GraphicsContext* mContext;
vec2 mMousePosition;
vec2 mPlayerPosition;
float mPlayerMovementRate = 3.0f;
float mShiftMultiplier = 3.0f;
double mDeltaTime = 0;


void Render()
{
	mRenderer->Clear(Color(0.3f, 0.3f, 0.4f, 1.0f));

	mRenderer->DrawQuad({100, 100}, vec2(1280.0f / 2, 720.0f / 2), Color(0.5f, 0.2f, 0.2f, 0.0f));
	mRenderer->DrawQuad({100, 100}, mPlayerPosition, Color(0.2f, 0.2f, 0.5f, 0.0f));

	mRenderer->FinishFrame();
}

void PollInput()
{
	mContext->UpdateInput();

	mMousePosition = mContext->GetMousePosition();

	float currentMultiplier = 1.0f;

	if (mContext->GetKeyDown(GLFW_KEY_RIGHT_SHIFT) || mContext->GetKeyDown(GLFW_KEY_LEFT_SHIFT))
		currentMultiplier = mShiftMultiplier;
	else currentMultiplier = 1.0f;
	if (mContext->GetKeyDown(GLFW_KEY_W)) mPlayerPosition.y += mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKeyDown(GLFW_KEY_S)) mPlayerPosition.y -= mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKeyDown(GLFW_KEY_D)) mPlayerPosition.x += mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKeyDown(GLFW_KEY_A)) mPlayerPosition.x -= mPlayerMovementRate * currentMultiplier;
	if (mContext->GetKey(GLFW_KEY_ESCAPE)) mContext->CloseWindow();
}

void UpdateLogic()
{
}

int main()
{
	mRenderer = new Graphics::Renderer();
	int successCode = mRenderer->InitializeGraphics(vec2(1280, 720), "cpp-game");
	if (successCode != 1) return successCode;

	mContext = mRenderer->Context();

	while (!mContext->ShouldWindowClose())
	{
		Render();
		PollInput();
		UpdateLogic();
	}

	mRenderer->DeinitializeGraphics();
	
	delete mRenderer;
	return 0;
}