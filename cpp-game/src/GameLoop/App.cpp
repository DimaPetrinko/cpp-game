#include "App.h"

namespace GameLoop
{
	App::App(Graphics::WindowData&& windowData) : mWindowData(std::move(windowData))
	{}

	App::~App()
	{
		if (mRendererCreated) delete mRenderer;
	}

	ReturnCode App::Initialize()
	{
		mRenderer = new Graphics::Renderer();
		mContext = mRenderer->Context();
		mRendererCreated = true;

		mReturnCode = mRenderer->InitializeGraphics(mWindowData.Size, std::move(mWindowData.Title));
		mGraphicsInitialized = true;
		CHECK_RETURN_CODE_AND_RETURN_CODE;

		InitializeData();
		mDataInitialized = true;

		return mReturnCode;
	}

	void App::Deinitialize()
	{
		if (mDataInitialized)
		{
			DeinitializeData();
			mDataInitialized = false;
		}
		if (mGraphicsInitialized)
		{
			mRenderer->DeinitializeGraphics();
			mGraphicsInitialized = false;
		}
		if (mRendererCreated)
		{
			delete mRenderer;
			mRendererCreated = false;
		}
	}

	ReturnCode App::Run()
	{
		mReturnCode = Initialize();

		while (mReturnCode == RETURN_CODE_RUNNING)
		{
			UpdateInput();
			UpdateLogic();
			UpdatePhysics();
			UpdateGraphics();

			if (mContext->ShouldWindowClose()) mReturnCode = RETURN_CODE_EXIT;
		}

		Deinitialize();

		return mReturnCode;
	}

	void App::Shutdown()
	{
		mContext->CloseWindow();
	}
}