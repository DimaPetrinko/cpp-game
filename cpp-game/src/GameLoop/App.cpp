#include "App.h"

namespace GameLoop
{
	App::App(vec2 size, const std::string&& title)
	{
		mRenderer = new Graphics::Renderer();
		mRendererCreated = true;
		mReturnCode = mRenderer->InitializeGraphics(size, std::move(title));
		mGraphicsInitialized = true;
		if (mReturnCode != RETURN_CODE_RUNNING) return;

		mContext = mRenderer->Context();
	}

	App::~App()
	{
		if (mRendererCreated) delete mRenderer;
	}

	void App::Shutdown()
	{
		if (mInitPerformed)
		{
			Deinitialize();
			mInitPerformed = false;
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
		if (mReturnCode != RETURN_CODE_RUNNING) return mReturnCode;

		Initialize();
		mInitPerformed = true;

		while (!mContext->ShouldWindowClose())
		{		
			UpdateInput();
			UpdateLogic();
			UpdatePhysics();
			UpdateGraphics();

			if (mReturnCode != RETURN_CODE_RUNNING) return mReturnCode;
		}
		mReturnCode = RETURN_CODE_EXIT;

		Deinitialize();
		mInitPerformed = false;

		mRenderer->DeinitializeGraphics();
		mGraphicsInitialized = false;
		return mReturnCode;
	}
}