#include "hzpch.h"
#include "ImGuiLayer.h"
#include "ColaMan/DirectX12/ShapesApp.h"
#include"ColaMan/Platform/DirectX12/imGuiDX12Renderer.h"
#include "ColaMan/Platform/DirectX12/imGuiWin32Renderer.h"

namespace ColaMan {

	//static Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mSrvDescHeap = nullptr;

	ImGuiLayer::ImGuiLayer() :Layer("ImGuiLayer") {
		OnAttach();
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		static int counter = 0;
		//test1    控制旋转
		ImGui::Begin("WangMeifo!Test");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Drag the slider to rotate the Angle of the Box.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show);      // Edit bools storing our window open/close state

		//ImGui::SliderFloat("float", &mPhi, 0.1f, 1.0f);  //mPhi立方体的旋转角度
		// Edit 1 float using a slider from 0.0f to 1.0f

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Render();
		CMD3DApp::GetApp()->GetCommandList()->SetDescriptorHeaps(1, mSrvDescHeap.GetAddressOf());
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),CMD3DApp::GetApp()->GetCommandList());

		CMD3DApp::GetApp()->ExcuteCommand();
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

	}
	void ImGuiLayer::OnAttach()
	{
		

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); 
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//TEMPORY
		io.KeyMap[ImGuiKey_Tab] = VK_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
		io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
		io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
		io.KeyMap[ImGuiKey_Home] = VK_HOME;
		io.KeyMap[ImGuiKey_End] = VK_END;
		io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
		io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
		io.KeyMap[ImGuiKey_Space] = VK_SPACE;
		io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
		io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;
		io.KeyMap[ImGuiKey_A] = 'A';
		io.KeyMap[ImGuiKey_C] = 'C';
		io.KeyMap[ImGuiKey_V] = 'V';
		io.KeyMap[ImGuiKey_X] = 'X';
		io.KeyMap[ImGuiKey_Y] = 'Y';
		io.KeyMap[ImGuiKey_Z] = 'Z';

		D3D12_DESCRIPTOR_HEAP_DESC SrvHeapDesc;
		SrvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		SrvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		SrvHeapDesc.NodeMask = 0;
		SrvHeapDesc.NumDescriptors = 1;
		auto heap = CMD3DApp::GetApp()->GetImGuiDescHeap();
		//ThrowIfFailed((*CMD3DApp::GetApp()->GetDevice())->CreateDescriptorHeap(&SrvHeapDesc, IID_PPV_ARGS(mSrvDescHeap.GetAddressOf())));


		ImGui_ImplWin32_Init(CMD3DApp::GetApp()->GetWindow());
		ImGui_ImplDX12_Init((*CMD3DApp::GetApp()->GetDevice()), 2, DXGI_FORMAT_R8G8B8A8_UNORM, mSrvDescHeap.Get(),
			mSrvDescHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
			mSrvDescHeap.Get()->GetGPUDescriptorHandleForHeapStart());
		CM_CORE_TRACE("ImGui Attach!");
	}
	void ImGuiLayer::OnDetach()
	{
	}
}