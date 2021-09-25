#include "App.h"

namespace GameLoop
{
	App::App(Graphics::WindowData&& windowData)
		: mWindowData(std::move(windowData)),
		mReturnCode(RETURN_CODE_NOT_INITIALIZED)
	{}

	App::~App()
	{
		if (mRendererCreated) delete mRenderer;
	}

	void App::Initialize()
	{
		mRenderer = new Graphics::Renderer();
		mContext = mRenderer->Context();
		mRendererCreated = true;

		mReturnCode = mRenderer->InitializeGraphics(mWindowData.Size, std::move(mWindowData.Title));
		mGraphicsInitialized = true;
		CheckAndReturn(mReturnCode);

		InitializeData();
		mDataInitialized = true;
		CheckAndReturn(mReturnCode);

		mReturnCode = RETURN_CODE_RUNNING;
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
			mContext = nullptr;
			mRendererCreated = false;
		}
	}

	void App::Shutdown()
	{
		mContext->CloseWindow();
	}

	ReturnCode App::Run()
	{
		Initialize();

		while (mReturnCode == RETURN_CODE_RUNNING)
		{
			CallAndBreak(UpdateInput(), mReturnCode);
			CallAndBreak(UpdateLogic(), mReturnCode);
			CallAndBreak(UpdatePhysics(), mReturnCode);

			CallAndBreak(StartFrame(), mReturnCode);
			CallAndBreak(UpdateGraphics(), mReturnCode);
			CallAndBreak(FinishFrame(), mReturnCode);
			
			if (mContext->ShouldWindowClose()) mReturnCode = RETURN_CODE_EXIT;
		}

		Deinitialize();

		return mReturnCode;
	}

	void App::StartFrame() {}

	void App::FinishFrame()
	{
		mRenderer->PostRender();
	}
}