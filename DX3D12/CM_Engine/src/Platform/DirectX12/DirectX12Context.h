#pragma once
#include "ColaMan/Renderer/GraphicsContext.h"

namespace ColaMan {
	class DirectX12Context :public GraphicsContext
	{
	public:
		DirectX12Context(HWND window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		HWND m_Window;
	};
}