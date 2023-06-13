#include "hzpch.h"
#include "DirectX12Context.h"
#include <ColaMan/DirectX12/ShapesApp.h>

namespace ColaMan {
	DirectX12Context::DirectX12Context(HWND window):m_Window(window)
	{
		mDX12Core = new Dx12Core(window);
	}

	void DirectX12Context::newFrame()
	{
		mDX12Core->NewFrame();
	}

	void DirectX12Context::Init() 
	{
		CM_ASSERT(mDX12Core->Initialize(),"DirectX initialized failed!");
	}
	void DirectX12Context::SwapBuffers()
	{
		mDX12Core->SwapChain();
	}
} 