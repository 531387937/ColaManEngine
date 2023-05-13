#pragma once
#include "ColaMan/Layer.h"
#include <wrl/client.h>
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

	public:
		Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mSrvDescHeap = nullptr;
		
	};
}