#pragma once

#include "Graphics/Renderer.h"
#include "Utilities/Vectors.h"
#include "Utilities/ReturnCodes.h"

namespace GameLoop
{
	class App
	{
	protected:
		Graphics::Renderer* mRenderer;
		Graphics::GraphicsContext* mContext;
		ReturnCode mReturnCode;
	private:
		bool mRendererCreated;
		bool mGraphicsInitialized;
		bool mInitPerformed;

	public:
		App(vec2 size, const std::string&& title);
		virtual ~App();

		ReturnCode Run();
		void Shutdown();

	protected:
		virtual void Init() = 0;
		virtual void UpdateGraphics() = 0;
		virtual void UpdateLogic() = 0;
		virtual void UpdateInput() = 0;
		virtual void Deinit() = 0;
	};
}