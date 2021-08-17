#pragma once

#include "Graphics/Renderer.h"
#include "Graphics/WindowData.h"
#include "Utils/ReturnCodes.h"

#define CHECK_RETURN_CODE_RUNNING_CONDITION 	if (mReturnCode == RETURN_CODE_RUNNING)
#define CHECK_RETURN_CODE_CONDITION 			if (mReturnCode != RETURN_CODE_RUNNING)
#define CHECK_RETURN_CODE_AND_RETURN 			if (mReturnCode != RETURN_CODE_RUNNING) return
#define CHECK_RETURN_CODE_AND_RETURN_CODE 		if (mReturnCode != RETURN_CODE_RUNNING) return mReturnCode

namespace GameLoop
{
	class App
	{
	protected:
		Graphics::Renderer* mRenderer;
		Graphics::GraphicsContext* mContext;
		ReturnCode mReturnCode;
	private:
		Graphics::WindowData mWindowData;
		bool mRendererCreated;
		bool mGraphicsInitialized;
		bool mDataInitialized;

	public:
		App(Graphics::WindowData&& windowData);
		virtual ~App();

		ReturnCode Run();

	protected:
		void Shutdown();

		virtual void InitializeData() = 0;
		virtual void DeinitializeData() = 0;

		virtual void UpdateInput() = 0;
		virtual void UpdateLogic() = 0;
		virtual void UpdatePhysics() = 0;
		virtual void UpdateGraphics() = 0;

	private:
		ReturnCode Initialize();
		void Deinitialize();
	};
}