#include "App.h"

namespace GameLoop
{
	App::App(vec2 size, const std::string&& title)
	{
		mRenderer = new Graphics::Renderer();
		mReturnCode = mRenderer->InitializeGraphics(size, std::move(title));
		if (mReturnCode != RETURN_CODE_RUNNING) return;

		mContext = mRenderer->Context();
	}

	App::~App()
	{
		delete mRenderer;
	}

	ReturnCode App::Run()
	{
		if (mReturnCode != RETURN_CODE_RUNNING) return mReturnCode;

		Init();

		while (!mContext->ShouldWindowClose())
		{		
			UpdateInput();
			UpdateLogic();
			UpdateGraphics();

			if (mReturnCode != RETURN_CODE_RUNNING) return mReturnCode;
		}
		mReturnCode = RETURN_CODE_EXIT;

		Deinit();

		mRenderer->DeinitializeGraphics();
		return mReturnCode;
	}
}