#include "hzpch.h"
#include "ImGuiLayer.h"
#include "ColaMan/DirectX12/ShapesApp.h"
#include"ColaMan/Platform/DirectX12/imGuiDX12Renderer.h"
#include "ColaMan/Platform/DirectX12/imGuiWin32Renderer.h"
#include "ColaMan/Application.h"

namespace ColaMan {

	//static Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mSrvDescHeap = nullptr;

	ImGuiLayer::ImGuiLayer() :Layer("ImGuiLayer") {
		
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		

		

		

		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGuiIO& io = ImGui::GetIO();

		auto& time = CMD3DApp::GetApp()->DX12GetTime();
		io.DeltaTime = time.DeltaTime();
		//m_Time = time;
		io.DisplaySize = ImVec2(Application::Instance->GetWindow().GetWidth(), Application::Instance->GetWindow().GetHeight());

		static bool show = true;
		if(show)
			ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		CMD3DApp::GetApp()->GetCommandList()->SetDescriptorHeaps(1, mSrvDescHeap.GetAddressOf());
		
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),CMD3DApp::GetApp()->GetCommandList());

		CMD3DApp::GetApp()->ExcuteCommand();
		if (m_Resize)
		{
			CMD3DApp::GetApp()->Resize(io.DisplaySize.x, io.DisplaySize.y);
		}
		m_Resize = false;
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch <MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch <MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch <MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch <MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScrolledEvent, this, std::placeholders::_1));
		dispatcher.Dispatch <KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch <KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch <KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTypedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch <WindowResizeEvent>(std::bind(&ImGuiLayer::OnWindowResizedEvent, this, std::placeholders::_1));
	}
	void ImGuiLayer::OnAttach()
	{
		

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); 
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
		//io.ConfigFlags |= ImGuiConfigFlags_
		//TEMPORY

		ImGui_ImplWin32_Init(CMD3DApp::GetApp()->GetWindow());
		D3D12_DESCRIPTOR_HEAP_DESC SrvHeapDesc;
		SrvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		SrvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		SrvHeapDesc.NodeMask = 0;
		SrvHeapDesc.NumDescriptors = 1;
		auto app = (CMD3DApp::GetApp())->GetDevice();
		ThrowIfFailed(app->CreateDescriptorHeap(&SrvHeapDesc, IID_PPV_ARGS(mSrvDescHeap.GetAddressOf())));


		ImGui_ImplDX12_Init(app, 2, DXGI_FORMAT_R8G8B8A8_UNORM, mSrvDescHeap.Get(),
			mSrvDescHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
			mSrvDescHeap.Get()->GetGPUDescriptorHandleForHeapStart());
		CM_CORE_TRACE("ImGui Attach!");
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int a = e.GetMouseButton();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[VK_LCONTROL] || io.KeysDown[VK_RCONTROL];
		io.KeyShift = io.KeysDown[VK_LSHIFT] || io.KeysDown[VK_RSHIFT];
		io.KeyAlt = io.KeysDown[VK_LMENU] || io.KeysDown[VK_RMENU];
		io.KeySuper = io.KeysDown[VK_LWIN] || io.KeysDown[VK_RWIN];
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto c = e.GetKeyCode();
		if (c > 0 && c < 0x10000)
		{
			io.AddInputCharacter((unsigned short)c);
		}
		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		m_Resize = true;
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		return false;
	}

}