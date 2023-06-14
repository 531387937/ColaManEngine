#include "hzpch.h"
#include "DirectX12Context.h"
#include <ColaMan/DirectX12/ShapesApp.h>

namespace ColaMan {
	DirectX12Context* DirectX12Context::instance = nullptr;
	DirectX12Context::DirectX12Context(HWND window):m_Window(window)
	{
		CM_ASSERT(instance==nullptr,"Already have Dx12Context!");
		if(instance==nullptr)
		{
			instance = this;
			mDX12Core = new Dx12Core(window);
		}
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
		if(shouleResize)
			mDX12Core->OnResize();
		shouleResize = false;
	}

	DirectX12Context* DirectX12Context::GetInstance()
	{
		return instance;
	}

	ID3D12Device* DirectX12Context::GetDevice()
	{
		return  mDX12Core->md3dDevice.Get();
	}

	ID3D12GraphicsCommandList* DirectX12Context::GetCmdList()
	{
		return mDX12Core->mCommandList.Get();
	}

	void DirectX12Context::Resize(float width,float height)
	{
		mDX12Core->mClientWidth = width;
		mDX12Core->mClientHeight = height;
		shouleResize = true;
	}
} 