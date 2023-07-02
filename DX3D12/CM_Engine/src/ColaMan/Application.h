#pragma once

#include <DirectXMath.h>
#include <wtypes.h>
#include "Core.h"
#include "ColaMan/LayerStack.h"
#include "Event/ApplicationEvent.h"
#include "ColaMan/ImGui/ImGuiLayer.h"
#include "Window.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"

namespace ColaMan {

	class CM_API Application
	{
	public:

		Application() = delete;
		Application(HINSTANCE hInstance);

		static Application* Instance;
		virtual ~Application();

		int Run(HINSTANCE hInstance);

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> VsShader;
		std::shared_ptr<Shader> PsShader;
		std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
		ComPtr<ID3D12PipelineState> mPSO = nullptr;
		ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
		ComPtr<ID3D12DescriptorHeap> descriptorHeap = nullptr;

		uint16_t descriptorIndex;
		uint16_t psoIndex;
		uint16_t rootSigIndex;
		std::shared_ptr<VertexBuffer> vb;
		std::shared_ptr<IndexBuffer> ib;
		std::vector<float> vertices;
		std::vector<uint16_t> indices;
	};

}
