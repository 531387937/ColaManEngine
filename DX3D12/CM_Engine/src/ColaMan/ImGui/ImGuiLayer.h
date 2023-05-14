#pragma once
#include "ColaMan/Layer.h"
#include <wrl/client.h>
#include "ColaMan/Event/MouseEvent.h"
#include "ColaMan/Event/KeyEvent.h"
#include "ColaMan/Event/ApplicationEvent.h"
#include <d3d12.h>
namespace ColaMan {
	class CM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);
		void OnAttach();
		void OnDetach();

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);
	private:
		Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mSrvDescHeap = nullptr;
		bool m_Resize = false;
		float m_Time = 0.0f;
	};
}