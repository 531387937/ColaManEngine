#include "hzpch.h"
//#include "DX12Core.h"
//using namespace Microsoft::WRL;
//namespace ColaMan {
//	CMDX12* CMDX12::dx12 = nullptr;
//	CMDX12::CMDX12(HWND window)
//	{
//		CM_ASSERT(dx12 == nullptr, "Already have a dx12");
//		dx12 = this;
//		mhMainWnd = window;
//		RECT* rect = new RECT();
//		GetClientRect(window, rect);
//		mClientWidth = rect->right - rect->left;
//		mClientHeight = rect->bottom - rect->top;
//	}
//	CMDX12::~CMDX12()
//	{
//	}
//	bool CMDX12::Initialize()
//	{
//		return false;
//	}
//	bool CMDX12::InitDirect3D()
//	{
//#if defined(DEBUG) || defined(_DEBUG) 
//		// Enable the D3D12 debug layer.
//		{
//			ComPtr<ID3D12Debug> debugController;
//			ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
//			debugController->EnableDebugLayer();
//		}
//#endif
//
//		ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory)));
//
//		// Try to create hardware device.
//		HRESULT hardwareResult = D3D12CreateDevice(
//			nullptr,             // default adapter
//			D3D_FEATURE_LEVEL_11_0,
//			IID_PPV_ARGS(&md3dDevice));
//
//		// Fallback to WARP device.
//		if (FAILED(hardwareResult))
//		{
//			ComPtr<IDXGIAdapter> pWarpAdapter;
//			ThrowIfFailed(mdxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));
//
//			ThrowIfFailed(D3D12CreateDevice(
//				pWarpAdapter.Get(),
//				D3D_FEATURE_LEVEL_11_0,
//				IID_PPV_ARGS(&md3dDevice)));
//		}
//
//		ThrowIfFailed(md3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE,
//			IID_PPV_ARGS(&mFence)));
//
//		mRtvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
//		mDsvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
//		mCbvSrvUavDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//
//		// Check 4X MSAA quality support for our back buffer format.
//		// All Direct3D 11 capable devices support 4X MSAA for all render 
//		// target formats, so we only need to check quality support.
//
//		D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
//		msQualityLevels.Format = mBackBufferFormat;
//		msQualityLevels.SampleCount = 4;
//		msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
//		msQualityLevels.NumQualityLevels = 0;
//		ThrowIfFailed(md3dDevice->CheckFeatureSupport(
//			D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
//			&msQualityLevels,
//			sizeof(msQualityLevels)));
//
//		m4xMsaaQuality = msQualityLevels.NumQualityLevels;
//		assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level.");
//
//		CreateCommandObjects();
//		CreateSwapChain();
//		CreateRtvAndDsvDescriptorHeaps();
//
//		return true;
//	}
//	void CMDX12::CreateCommandObjects()
//	{
//		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
//		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
//		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
//		ThrowIfFailed(md3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&mCommandQueue)));
//
//		ThrowIfFailed(md3dDevice->CreateCommandAllocator(
//			D3D12_COMMAND_LIST_TYPE_DIRECT,
//			IID_PPV_ARGS(mDirectCmdListAlloc.GetAddressOf())));
//
//		ThrowIfFailed(md3dDevice->CreateCommandList(
//			0,
//			D3D12_COMMAND_LIST_TYPE_DIRECT,
//			mDirectCmdListAlloc.Get(), // Associated command allocator
//			nullptr,                   // Initial PipelineStateObject
//			IID_PPV_ARGS(mCommandList.GetAddressOf())));
//
//		// Start off in a closed state.  This is because the first time we refer 
//		// to the command list we will Reset it, and it needs to be closed before
//		// calling Reset.
//		mCommandList->Close();
//	}
//	void CMDX12::CreateSwapChain()
//	{
//		// Release the previous swapchain we will be recreating.
//		mSwapChain.Reset();
//
//		DXGI_SWAP_CHAIN_DESC sd;
//		sd.BufferDesc.Width = mClientWidth;
//		sd.BufferDesc.Height = mClientHeight;
//		sd.BufferDesc.RefreshRate.Numerator = 60;
//		sd.BufferDesc.RefreshRate.Denominator = 1;
//		sd.BufferDesc.Format = mBackBufferFormat;
//		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//		sd.SampleDesc.Count = m4xMsaaState ? 4 : 1;
//		sd.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
//		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//		sd.BufferCount = SwapChainBufferCount;
//		sd.OutputWindow = mhMainWnd;
//		sd.Windowed = true;
//		sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
//		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//
//		// Note: Swap chain uses queue to perform flush.
//		ThrowIfFailed(mdxgiFactory->CreateSwapChain(
//			mCommandQueue.Get(),
//			&sd,
//			mSwapChain.GetAddressOf()));
//	}
//	void CMDX12::CreateRtvAndDsvDescriptorHeaps()
//	{
//		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
//		rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
//		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
//		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//		rtvHeapDesc.NodeMask = 0;
//		ThrowIfFailed(md3dDevice->CreateDescriptorHeap(
//			&rtvHeapDesc, IID_PPV_ARGS(mRtvHeap.GetAddressOf())));
//
//
//		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
//		dsvHeapDesc.NumDescriptors = 1;
//		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
//		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//		dsvHeapDesc.NodeMask = 0;
//		ThrowIfFailed(md3dDevice->CreateDescriptorHeap(
//			&dsvHeapDesc, IID_PPV_ARGS(mDsvHeap.GetAddressOf())));
//	}
//}
//
