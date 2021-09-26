#pragma once

#include "Graphics/Renderer.h"
#include "Graphics/WindowData.h"
#include "Resources/AssetDatabase.h"
#include "GameLoop/ReturnCodes.h"

namespace GameLoop
{
	class App
	{
	protected:
		Graphics::Renderer* mRenderer;
		Graphics::GraphicsContext* mContext;
		Resources::AssetDatabase* mAssetDatabase;
		ReturnCode mReturnCode;
	private:
		Graphics::WindowData mWindowData;
		bool mRendererCreated;
		bool mAssetDatabaseCreated;
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

		virtual void StartFrame();
		virtual void FinishFrame();

	private:
		void Initialize();
		void Deinitialize();
	};
}