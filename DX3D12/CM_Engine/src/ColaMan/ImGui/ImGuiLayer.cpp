#include "hzpch.h"
#include "ImGuiLayer.h"
#include "examples/imgui_impl_dx12.h"
#include "examples/imgui_impl_win32.h"
#include "ColaMan/DirectX12/ShapesApp.h"
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

		//ImGui_ImplDX12_NewFrame();
		//ImGui_ImplWin32_NewFrame();
		//ImGui::NewFrame();
		//ImGuiIO& io = ImGui::GetIO();

		//auto& time = CMD3DApp::GetApp()->DX12GetTime();
		//io.DeltaTime = time.DeltaTime();
		////m_Time = time;
		//io.DisplaySize = ImVec2(Application::Instance->GetWindow().GetWidth(), Application::Instance->GetWindow().GetHeight());

		//static bool show = true;
		//if(show)
		//	ImGui::ShowDemoWindow(&show);

		//ImGui::Render();
		//CMD3DApp::GetApp()->GetCommandList()->SetDescriptorHeaps(1, mSrvDescHeap.GetAddressOf());
		//
		//ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),CMD3DApp::GetApp()->GetCommandList());

		//CMD3DApp::GetApp()->ExcuteCommand();
		//if (m_Resize)
		//{
		//	CMD3DApp::GetApp()->Resize(io.DisplaySize.x, io.DisplaySize.y);
		//}
		//m_Resize = false;
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application* app = Application::Instance;

		io.DisplaySize = ImVec2(app->GetWindow().GetWidth(), app->GetWindow().GetHeight());
		ImGui::Render();

		CMD3DApp::GetApp()->GetCommandList()->SetDescriptorHeaps(1, mSrvDescHeap.GetAddressOf());
		
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),CMD3DApp::GetApp()->GetCommandList());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault(NULL, (void*)CMD3DApp::GetApp()->GetCommandList());
		}
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
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		Application* app = Application::Instance;
		HWND hwnd = static_cast<HWND>(app->GetWindow().GetNativeWindow());
		ImGui_ImplWin32_Init(hwnd);

		D3D12_DESCRIPTOR_HEAP_DESC SrvHeapDesc;

		SrvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		SrvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		SrvHeapDesc.NodeMask = 0;
		SrvHeapDesc.NumDescriptors = 1;
		auto device = (CMD3DApp::GetApp())->GetDevice();
		ThrowIfFailed(device->CreateDescriptorHeap(&SrvHeapDesc, IID_PPV_ARGS(mSrvDescHeap.GetAddressOf())));


		ImGui_ImplDX12_Init(device, 2, DXGI_FORMAT_R8G8B8A8_UNORM, mSrvDescHeap.Get(),
			mSrvDescHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
			mSrvDescHeap.Get()->GetGPUDescriptorHandleForHeapStart());
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