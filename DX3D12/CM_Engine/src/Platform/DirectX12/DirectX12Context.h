#pragma once
#include "ColaMan/DirectX12/DX12Core.h"
#include "ColaMan/Renderer/GraphicsContext.h"

namespace ColaMan {
	class DirectX12Context :public GraphicsContext
	{
	public:
		DirectX12Context(HWND window);
		virtual void newFrame() override;
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		HWND m_Window;
		Dx12Core* mDX12Core;
	};
}