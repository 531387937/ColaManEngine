#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "d3dUtil.h"
#include "UploadBuffer.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")


namespace ColaMan
{
    extern class DirectX12Context;

    struct FrameResource
    {
    public:
        FrameResource(ID3D12Device* device)
        {
            ThrowIfFailed(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,IID_PPV_ARGS(&CmdListAlloc)));
        }
        //FrameResource(ID3D12Device* device, UINT passCount, UINT objectCount);
        FrameResource(const FrameResource& rhs) = delete;
        FrameResource& operator=(const FrameResource& rhs) = delete;
        ~FrameResource() = default;

        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CmdListAlloc;

        // std::unique_ptr<UploadBuffer<PassConstants>> PassCB = nullptr;
        // std::unique_ptr<UploadBuffer<ObjectConstants>> ObjectCB = nullptr;

        UINT64 Fence = 0;
    };
    
    class Dx12Core
    {
        friend class DirectX12Context;
    public:
        Dx12Core(HWND window);
        Dx12Core(const Dx12Core& rhs) = delete;
        Dx12Core& operator=(const Dx12Core& rhs) = delete;
        virtual ~Dx12Core();

        static Dx12Core* GetDX12() { return dx12; }

        bool Initialize();
        void NewFrame();
        void SwapChain();
        inline void dxClearColor(DirectX::XMFLOAT4 color) { 
            mClearColor.f[0] = color.x;
            mClearColor.f[1] = color.y;
            mClearColor.f[2] = color.z;
            mClearColor.f[3] = color.w;
         }
        void Clear();
        static ID3D12Device* GetDevice();
        static ID3D12GraphicsCommandList* GetCommandList();
        static ID3D12CommandAllocator* GetCommandAlloc();
        static ID3D12CommandQueue* GetCommandQueue();
        static void BeginCreateResource();
        static void EndCreateResource();
        

        float AspectRatio() const;
    private:
        bool InitDirect3D();
        void CreateCommandObjects();
        void CreateSwapChain();
        void CreateRtvAndDsvDescriptorHeaps();

        ID3D12Resource* CurrentBackBuffer() const;
        D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
        D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

        void OnResize();
        void FlushCommandQueue();
    protected:
        bool mAppPaused = false; // is the application paused?
        bool mMinimized = false; // is the application minimized?
        bool mMaximized = false; // is the application maximized?
        bool mResizing = false; // are the resize bars being dragged?
        bool mFullscreenState = false; // fullscreen enabled

        // Set true to use 4X MSAA (?.1.8).  The default is false.
        bool m4xMsaaState = false; // 4X MSAA enabled
        UINT m4xMsaaQuality = 0; // quality level of 4X MSAA

        // Used to keep track of the ?delta-time?and game time (?.4).
        //GameTimer mTimer;

        Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
        Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
        Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;

        Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
        UINT64 mCurrentFence = 0;

        Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;


        static const int SwapChainBufferCount = 2;
        int mCurrBackBuffer = 0;
        Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
        Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

        D3D12_VIEWPORT mScreenViewport;
        D3D12_RECT mScissorRect;

        UINT mRtvDescriptorSize = 0;
        UINT mDsvDescriptorSize = 0;
        UINT mCbvSrvUavDescriptorSize = 0;

        // Derived class should set these in derived constructor to customize starting values.

        D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
        DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
        DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
        int mClientWidth = 800;
        int mClientHeight = 600;
        HWND mhMainWnd = nullptr; // main window handle

    private:
        static Dx12Core* dx12;
        std::vector<std::unique_ptr<FrameResource>> mFrameResources;
        FrameResource* mCurrFrameResource = nullptr;
        int mCurrFrameResourceIndex = 0;

        DirectX::XMVECTORF32 mClearColor;
    };
}
