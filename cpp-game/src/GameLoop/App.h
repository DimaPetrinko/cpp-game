#pragma once

#include "Graphics/Renderer.h"
#include "Utils/Vector.h"
#include "Utils/ReturnCodes.h"

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
		virtual void Initialize() = 0;
		virtual void UpdateInput() = 0;
		virtual void UpdateLogic() = 0;
		virtual void UpdatePhysics() = 0;
		virtual void UpdateGraphics() = 0;
		virtual void Deinitialize() = 0;
	};
}