#include "hzpch.h"
#include "Application.h"
#include "Platform/DirectX12/DirectX12Context.h"

#include "Platform/Windows/WindowsInput.h"

namespace ColaMan
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

    Application* Application::Instance = nullptr;

    Application::~Application()
    {
    }

    Application::Application(HINSTANCE hInstance)
    {
        if (!Instance)
            Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create(hInstance));
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
        Dx12Core::BeginCreateResource();
        vertices = {
            {-0.5f, -0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {0.0f, 0.5f, 0.0f}
        };
        indices=
        {
            0, 2, 1
        };
        vb.reset(VertexBuffer::Create(vertices.data(), sizeof(DirectX::XMFLOAT3) * vertices.size()));
        ib.reset(IndexBuffer::Create(indices.data(), indices.size()));
        

        VsShader = new Shader(L"Shaders\\color.hlsl", nullptr, "VS", "vs_5_0");
        PsShader = new Shader(L"Shaders\\color.hlsl", nullptr, "PS", "ps_5_0");
        mInputLayout =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        };


        D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
        descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;  // 描述符堆类型为常量缓冲区/着色器资源视图/非结构化资源视图
        descriptorHeapDesc.NumDescriptors = 1;  // 描述符数量为1，即空描述符堆
        descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;  // 描述符堆可见于着色器阶段
        
        DirectX12Context::GetInstance()->GetDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
        
        
        CD3DX12_ROOT_SIGNATURE_DESC sigDesc(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        ComPtr<ID3DBlob> serializedSig = nullptr;
        ComPtr<ID3DBlob> errorBlob = nullptr;

        HRESULT hr = D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, serializedSig.GetAddressOf(), errorBlob.GetAddressOf());
        if (errorBlob != nullptr)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
        }
        ThrowIfFailed(hr);

        ThrowIfFailed(DirectX12Context::GetInstance()->GetDevice()->CreateRootSignature(0, serializedSig->GetBufferPointer(), serializedSig->GetBufferSize(), IID_PPV_ARGS(mRootSignature.GetAddressOf())));

        D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;

        ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

        opaquePsoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
        opaquePsoDesc.pRootSignature = mRootSignature.Get();
        opaquePsoDesc.VS = VsShader->Bound();
        opaquePsoDesc.PS = PsShader->Bound();
        opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        
        opaquePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
        opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
        opaquePsoDesc.SampleMask = UINT_MAX;
        opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        opaquePsoDesc.NumRenderTargets = 1;
        opaquePsoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        opaquePsoDesc.SampleDesc.Count = 4;
        opaquePsoDesc.SampleDesc.Quality = 0;
        opaquePsoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

        ThrowIfFailed(DirectX12Context::GetInstance()->GetDevice()->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&mPSO)));

        Dx12Core::EndCreateResource();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        //CM_CORE_INFO("{0}",e);
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.m_Handled)
                break;
        }
    }

    int Application::Run(HINSTANCE hInstance)
    {
        try
        {
            while (m_Running)
            {
                m_Window->NewFrame();
                ID3D12DescriptorHeap* descriptorHeaps[] = { descriptorHeap.Get() };
                DirectX12Context::GetInstance()->GetCmdList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
                DirectX12Context::GetInstance()->GetCmdList()->SetGraphicsRootSignature(mRootSignature.Get());
                DirectX12Context::GetInstance()->GetCmdList()->SetPipelineState(mPSO.Get());

                ib->Bind();
                DirectX12Context::GetInstance()->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                vb->Bind();

                DirectX12Context::GetInstance()->GetCmdList()->DrawIndexedInstanced(ib->GetCount(), 1, 0, 0, 0);
                
                for (Layer* layer : m_LayerStack)
                {
                    layer->OnUpdate();
                }
                m_ImGuiLayer->Begin();
                for (Layer* layer : m_LayerStack)
                {
                    layer->OnImGuiRender();
                }
                //Vertex Array
                //Vertex Buffer
                //Index Buffer
                
                m_ImGuiLayer->End();
                m_Window->OnUpdate();
            }
            return 0;
        }
        catch (DxException& e)
        {
            MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
            return 0;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }
}
